/**
 * \file
 * \brief create child process library
 */

/*
 * Copyright (c) 2016, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Universitaetsstrasse 6, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef _INIT_SPAWN_H_
#define _INIT_SPAWN_H_

#include "aos/paging.h"
#include "aos/slot_alloc.h"

struct spawninfo {

    // Information about the binary
    char* binary_name; // Name of the binary

    struct capref l1_cnode_cap;

    struct cnoderef l2_cnodes[ROOTCN_SLOTS_USER];

    struct paging_state process_paging_state;

    dispatcher_handle_t handle;

    struct capref l1pagetable;

    arch_registers_state_t* enabled_area;

    domainid_t domain_id;
    // TODO: Use this structure to keep track
    // of information you need for building/starting
    // your new process!
};

// Start a child process by binary name. Fills in si
errval_t spawn_load_by_name(void* binary_name, struct spawninfo* si);
errval_t spawn_load_by_name_with_arguments(void* binary_name, struct spawninfo* si, int argc, const char* argv[]);
errval_t elf_allocate(void* state, genvaddr_t base, size_t size, uint32_t flags, void** ret);
errval_t init_child_cspace(struct spawninfo* si);
errval_t init_child_vspace(struct spawninfo* si);
errval_t setup_dispatcher(struct spawninfo* si, lvaddr_t elf_base, size_t elf_bytes, const char* name);
errval_t add_args(struct spawninfo* si, struct mem_region* module, int argc, const char* argv[]);

#endif /* _INIT_SPAWN_H_ */
