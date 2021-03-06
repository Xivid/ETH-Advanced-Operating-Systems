/**
 * \file
 * \brief Memory manager header
 */

/*
 * Copyright (c) 2008, 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef AOS_MM_H
#define AOS_MM_H

#include <sys/cdefs.h>
#include <errors/errno.h>
#include <aos/types.h>
#include <aos/capabilities.h>
#include <aos/slab.h>
#include "slot_alloc.h"

__BEGIN_DECLS

/**
 * \brief Type of the Memory Node
 *
 * A node of type `keep` maps to a memory region that is larger than described by
 * `size` and `base`. It's capability will not be handed out directly.
 */
enum nodetype {
    NodeType_Handout,   ///< Nodes of this type can be handed out by libmm
    NodeType_Keep       ///< Nodes of this type have to be split before handout
};

/**
 * \brief Node in Memory manager
 *
 * Prev points to a node which is smaller while next points to a node which is
 * larger than the current node.
 */
struct mmnode {
    enum nodetype type;    ///< Type of `this` node.
    struct capref cap;     ///< Cap in which this region exists
    struct mmnode *prev;   ///< Previous node in the list.
    struct mmnode *next;   ///< Next node in the list.
    genpaddr_t base;       ///< Base address of this region
    gensize_t size;        ///< Size of this free region in cap
};

/**
 * \brief Memory manager instance data
 *
 * This should be opaque from the perspective of the client, but to allow
 * them to allocate its memory, we declare it in the public header.
 *
 * The node list is a circular linked list sorted by size. Head points to
 * the smallest node.
 */
struct mm {
    struct slab_allocator slabs;    ///< Slab allocator for allocating nodes
    slot_alloc_t slot_alloc;        ///< Slot allocator for allocating cspace
    slot_refill_t slot_refill;      ///< Slot allocator refill function
    void *slot_alloc_inst;          ///< Instance pointer for slot allocator
    int allocating_ram;             ///< Flag indicating an in-process refill
    enum objtype objtype;           ///< Type of capabilities stored
    struct mmnode *head;            ///< Smallest node in doubly-linked list
    struct thread_mutex mm_mutex;   ///< Mutex protecting mm_alloc and mm_free
};

errval_t mm_init(struct mm *mm, enum objtype objtype,
                 slab_refill_func_t slab_refill_func,
                 slot_alloc_t slot_alloc_func,
                 slot_refill_t slot_refill_func,
                 void *slot_alloc_inst);
errval_t mm_add(struct mm *mm, struct capref cap, genpaddr_t base, size_t size);
errval_t mm_do_initial_split(struct mm *mm);
errval_t mm_alloc_aligned(struct mm *mm, size_t size, size_t alignment,
                          struct capref *retcap);
errval_t mm_alloc(struct mm *mm, size_t size, struct capref *retcap);
errval_t mm_free(struct mm *mm, struct capref cap, genpaddr_t base,
                 gensize_t size);
void mm_destroy(struct mm *mm);

// Debugging functions

void mm_print_node(struct mmnode *node);
void mm_traverse_list(struct mmnode *head);

__END_DECLS

#endif /* AOS_MM_H */
