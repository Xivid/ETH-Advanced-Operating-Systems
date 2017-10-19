#include <aos/aos.h>
#include <spawn/spawn.h>

#include <elf/elf.h>
#include <aos/dispatcher_arch.h>
#include <barrelfish_kpi/paging_arm_v7.h>
#include <barrelfish_kpi/domain_params.h>
#include <spawn/multiboot.h>

extern struct bootinfo *bi;

errval_t elf_allocate(void *state, genvaddr_t base, size_t size, uint32_t flags, void **ret);
errval_t init_child_vspace(struct spawninfo* si);
errval_t create_dispatcher(struct spawninfo* si, lvaddr_t elf_base, size_t elf_bytes);

errval_t init_child_cspace(struct spawninfo* si) {

    // create l1Cnode
    struct cnoderef l1_cnode;
    errval_t err = cnode_create_l1(&si->l1_cnode_cap, &l1_cnode);
    if (err_is_fail(err)) {
        debug_printf("Error during child cspace initialization, creating l1_cnode: %s", err_getstring(err));
        return err;
    }

    // create the L2Cnodes
    for (size_t i = 0; i < ROOTCN_SLOTS_USER; ++i) {
        err = cnode_create_foreign_l2(si->l1_cnode_cap, i, &si->l2_cnodes[i]);
        if (err_is_fail(err)) {
            debug_printf("Error during paging_map_frame: %s", err_getstring(err));
            return err;
        }
    }

    // setup taskn slot rootcn on l1Cnode
    struct capref taskn_slot_rootcn = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN],
        .slot = TASKCN_SLOT_ROOTCN
    };
    err = cap_copy(taskn_slot_rootcn, si->l1_cnode_cap);
    if (err_is_fail(err)) {
        debug_printf("Error during copy of L1Cnode cap to taskcn: %s", err_getstring(err));
        return err;
    }

    // allocate BASE_PAGE_CN slots in ram
    struct capref cap = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_BASE_PAGE_CN]
    };
    for (cap.slot = 0; cap.slot < L2_CNODE_SLOTS; ++cap.slot) {
        struct capref ram_for_base_page;
        err = ram_alloc(&ram_for_base_page, BASE_PAGE_SIZE);
        if (err_is_fail(err)) {
            debug_printf("Error during BASE_PAGE_CN ram_alloc: %s", err_getstring(err));
            return err;
        }
        err = cap_copy(cap, ram_for_base_page);
        if (err_is_fail(err)) {
            debug_printf("Error during cap copy in BASE_PAGE_CN slot filling: %s", err_getstring(err));
            return err;
            cap_destroy(ram_for_base_page);
        }
    }
    return SYS_ERR_OK;
}

errval_t init_child_vspace(struct spawninfo* si) {
    errval_t err;

    struct capref l1pagetable = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_PAGECN],
        .slot = 0
    };
    err = vnode_create(l1pagetable, ObjType_VNode_ARM_l1);
    if (err_is_fail(err)) {
        debug_printf("Error creating vnode\n");
        return err;
    }

    struct slot_allocator *default_sa = get_default_slot_allocator();
    err = paging_init_state(&si->process_paging_state, VADDR_OFFSET, l1pagetable, default_sa);
    if (err_is_fail(err)) {
        debug_printf("Error initing the paging state\n");
        return err;
    }

    return SYS_ERR_OK;
}

errval_t create_dispatcher(struct spawninfo* si, lvaddr_t elf_base, size_t elf_bytes) {

    errval_t err;

    struct capref dispatcher_cap = {
        .cnode = si->l2_cnodes[ROOTCN_SLOT_TASKCN],
        .slot = TASKCN_SLOT_DISPATCHER
    };
    err = dispatcher_create(dispatcher_cap);
    if (err_is_fail(err)) {
        debug_printf("Failed to create the dispatcher\n");
        return err;
    }

    dispatcher_handle_t dispatcher_in_child;
    err = paging_map_frame_attr(get_current_paging_state(), (void **)&dispatcher_in_child,
                                1 << DISPATCHER_FRAME_BITS, dispatcher_cap,
                                VREGION_FLAGS_READ, NULL, NULL);
    if (err_is_fail(err)) {
        debug_printf("Failed to map dispatcher to the child process\n");
        return err;
    }
    dispatcher_handle_t handle;
    err = paging_map_frame_attr(get_current_paging_state(), (void **)&handle, 1 << DISPATCHER_FRAME_BITS,
                                dispatcher_cap, VREGION_FLAGS_READ | VREGION_FLAGS_WRITE, NULL, NULL);
    if (err_is_fail(err)) {
        debug_printf("Failed to map dispatcher to the parent process\n");
        return err;
    }
    disp_init_disabled(handle);

    struct dispatcher_shared_generic *disp = get_dispatcher_shared_generic(handle);
    struct dispatcher_generic *disp_gen = get_dispatcher_generic(handle);
    struct dispatcher_shared_arm *disp_arm = get_dispatcher_shared_arm(handle);
    arch_registers_state_t *enabled_area = dispatcher_get_enabled_save_area(handle);
    arch_registers_state_t *disabled_area = dispatcher_get_disabled_save_area(handle);

    disp_gen->core_id = disp_get_core_id(); // run child on the same core
    disp->udisp = dispatcher_in_child;
    disp->disabled = 1;
    disp->fpu_trap = 1;
    strncpy(disp->name, "Child process!!\0", DISP_NAME_LEN);

    disabled_area->named.pc = ((struct Elf32_Ehdr *)elf_base)->e_entry;

    // Initialize offset registers
    struct Elf32_Shdr *got_addr = elf32_find_section_header_name(elf_base, elf_bytes, ".got");
    if (got_addr == NULL) {
        debug_printf("Error finding global offset table\n");
        return SPAWN_ERR_ELF_MAP;
    }
    disp_arm->got_base = (lvaddr_t) got_addr;
    enabled_area->regs[REG_OFFSET(PIC_REGISTER)] = (lvaddr_t) got_addr;
    disabled_area->regs[REG_OFFSET(PIC_REGISTER)] = (lvaddr_t) got_addr;
    enabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
    disabled_area->named.cpsr = CPSR_F_MASK | ARM_MODE_USR;
    disp_gen->eh_frame = 0;
    disp_gen->eh_frame_size = 0;
    disp_gen->eh_frame_hdr = 0;
    disp_gen->eh_frame_hdr_size = 0;

    si->handle = handle;

    return SYS_ERR_OK;
}

// TODO(M2): Implement this function such that it starts a new process
// TODO(M4): Build and pass a messaging channel to your child process
errval_t spawn_load_by_name(void * binary_name, struct spawninfo * si) {
    printf("spawn start_child: starting: %s\n", binary_name);
    errval_t err;
    // - Get the binary from multiboot image
    struct mem_region *module = multiboot_find_module(bi, binary_name);
    if (!module) {
        debug_printf("The module %s was not found\n", binary_name);
        return SPAWN_ERR_FIND_MODULE;
    }

    // child capref
    struct capref child_frame = {
        .cnode = cnode_module,
        .slot = module->mrmod_slot,
    };

    // Initialize spawninfo
    memset(si, 0, sizeof(*si));
    si->binary_name = binary_name;


    // - Map multiboot module in your address space
    struct frame_identity id_child_frame;
    frame_identify(child_frame, &id_child_frame);

    lvaddr_t map_elf;
    err = paging_map_frame(get_current_paging_state(), (void**)&map_elf, id_child_frame.bytes, child_frame, NULL, NULL);
    if (err_is_fail(err)) {
        debug_printf("Error during paging_map_frame: %s\n", err_getstring(err));
        return err;
    }

    printf("ELF header: %0x %c %c %c\n", ((char*)map_elf)[0], ((char*)map_elf)[1], ((char*)map_elf)[2], ((char*)map_elf)[3]);

    struct Elf32_Ehdr *elf_head = (void*)map_elf;
    if (!IS_ELF(*elf_head)) {
        debug_printf("Module is not a correct ELF binary\n");
        return ELF_ERR_HEADER;
    }

    err = init_child_cspace(si);
    if (err_is_fail(err)) {
        debug_printf("Error during init_child_cspace: %s \n", err_getstring(err));
        return err;
    }

    err = init_child_vspace(si);
    if (err_is_fail(err)) {
        debug_printf("Error during init_child_vspace: %s \n", err_getstring(err));
        return err;
    }

    genvaddr_t child_entry;
    err = elf_load(EM_ARM, elf_allocate, &si->process_paging_state, map_elf, id_child_frame.bytes, &child_entry);
    if (err_is_fail(err)) {
        debug_printf("Error: unable to load elf\n");
        return err;
    }

    err = create_dispatcher(si, map_elf, id_child_frame.bytes);
    if (err_is_fail(err)) {
        debug_printf("Error during dispatcher creation\n");
        return err;
    }

    printf("reached end of stuff which is implemented so far\n");

    // TODO: Implement me
    // - Setup childs cspace
    // - Setup childs vspace
    // - Load the ELF binary
    // - Setup dispatcher
    // - Setup environment
    // - Make dispatcher runnable

    return SYS_ERR_OK;
}

errval_t elf_allocate(void *state, genvaddr_t base, size_t size, uint32_t flags, void **ret) {
    printf("Call elf allocate with state:%p, base:%llu, size:%lu, flags:%lu \n", state, base, size, flags);

    struct capref region_cap;
    size_t actual_bytes;
    errval_t err = frame_alloc(&region_cap, size, &actual_bytes);
    if (err_is_fail(err)) {
        debug_printf("Error failed to allocate the needed ram\n");
        return err;
    }

    // map frame into our vtable with write permissions
    err = paging_map_frame_attr(get_current_paging_state(), ret, actual_bytes,
                                region_cap, VREGION_FLAGS_WRITE, NULL, NULL);

    // map frame into the processes vtable with the requested permissions
    uint32_t permission = 0;
    if (flags & PF_X) {
        permission |= VREGION_FLAGS_EXECUTE;
    } else if (flags & PF_W) {
        permission |= VREGION_FLAGS_WRITE;
    } else if (flags & PF_R) {
        permission |= VREGION_FLAGS_READ;
    }
    void *child_addr;
    err = paging_map_frame_attr(state, &child_addr, actual_bytes, region_cap,
                                permission, NULL, NULL);

    return SYS_ERR_OK;
}
