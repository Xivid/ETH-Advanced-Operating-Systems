/**
 * \file
 * \brief Interface declaration for AOS rpc-like messaging
 */

/*
 * Copyright (c) 2013, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef _LIB_BARRELFISH_AOS_MESSAGES_H
#define _LIB_BARRELFISH_AOS_MESSAGES_H

#include <aos/aos.h>

#define AOS_RPC_ATTEMPTS            4 // how many attempts do we want for sending/receiving before throwing an error

// IDs for different transmission types
// 1 << 0 is reserved for acknowleding that the message arrived successfully
enum enum_rpc_msgtype {
    AOS_RPC_ID_ACK = 1,
    AOS_RPC_ID_INIT,
    AOS_RPC_ID_RAM,
    AOS_RPC_ID_NUM,
    AOS_RPC_ID_CHAR,
    AOS_RPC_ID_STR,
    AOS_RPC_ID_PROCESS,
    AOS_RPC_ID_LIST_PROCESS,
};

struct domaininfo {
    char *domain_name;
    coreid_t core_id;
    domainid_t pid;
    struct domaininfo *next;
};

struct aos_rpc {
    struct lmp_chan lmp;
    struct waitset* ws;
    char* buffer;

    struct domaininfo* head;
    domainid_t current_pid;
    // TODO: add state for your implementation
};
errval_t aos_rpc_send_handler_for_init (void* v_args);
errval_t aos_rpc_send_handler_for_num (void* v_args);
errval_t aos_rpc_send_handler_for_char (void* v_args);
errval_t aos_rpc_send_handler_for_string (void* v_args);
errval_t aos_rpc_send_handler_for_ram (void* v_args);
errval_t aos_rpc_send_handler_for_process(void* v_args);

errval_t aos_rpc_rcv_handler_general (void* v_args);
errval_t aos_rpc_rcv_handler_for_ram (void* v_args);
errval_t aos_rpc_rcv_handler_for_process(void *v_args);

errval_t aos_rpc_send_and_receive (void* send_handler, void* rcv_handler, uintptr_t* args);

/**
 * \brief send a number over the given channel
 */
errval_t aos_rpc_send_number(struct aos_rpc *chan, uintptr_t val);

/**
 * \brief send a string over the given channel
 */
errval_t aos_rpc_send_string(struct aos_rpc *chan, const char *string);

/**
 * \brief request a RAM capability with >= request_bits of size over the given
 * channel.
 */
errval_t aos_rpc_get_ram_cap(struct aos_rpc *chan, size_t bytes, size_t align,
                             struct capref *retcap, size_t *ret_bytes);

/**
 * \brief get one character from the serial port
 */
errval_t aos_rpc_serial_getchar(struct aos_rpc *chan, char *retc);

/**
 * \brief send one character to the serial port
 */
errval_t aos_rpc_serial_putchar(struct aos_rpc *chan, char c);

/**
 * \brief Request process manager to start a new process
 * \arg name the name of the process that needs to be spawned (without a
 *           path prefix)
 * \arg newpid the process id of the newly spawned process
 */
errval_t aos_rpc_process_spawn(struct aos_rpc *chan, char *name,
                               coreid_t core, domainid_t *newpid);

/**
 * \brief Get name of process with id pid.
 * \arg pid the process id to lookup
 * \arg name A null-terminated character array with the name of the process
 * that is allocated by the rpc implementation. Freeing is the caller's
 * responsibility.
 */
errval_t aos_rpc_process_get_name(struct aos_rpc *chan, domainid_t pid,
                                  char **name);

/**
 * \brief Get process ids of all running processes
 * \arg pids An array containing the process ids of all currently active
 * processes. Will be allocated by the rpc implementation. Freeing is the
 * caller's  responsibility.
 * \arg pid_count The number of entries in `pids' if the call was successful
 */
errval_t aos_rpc_process_get_all_pids(struct aos_rpc *chan,
                                      domainid_t **pids, size_t *pid_count);

/**
 * \brief Gets a capability to device registers
 * \param rpc  the rpc channel
 * \param paddr physical address of the device
 * \param bytes number of bytes of the device memory
 * \param frame returned devframe
 */
errval_t aos_rpc_get_device_cap(struct aos_rpc *rpc, lpaddr_t paddr, size_t bytes,
                                struct capref *frame);
/**
 * \brief Initialize given rpc channel.
 * TODO: you may want to change the inteface of your init function, depending
 * on how you design your message passing code.
 */
errval_t aos_rpc_init(struct waitset* ws, struct aos_rpc *rpc);


/**
 * \brief Returns the RPC channel to init.
 */
struct aos_rpc *aos_rpc_get_init_channel(void);

/**
 * \brief Returns the channel to the memory server
 */
struct aos_rpc *aos_rpc_get_memory_channel(void);

/**
 * \brief Returns the channel to the process manager
 */
struct aos_rpc *aos_rpc_get_process_channel(void);

/**
 * \brief Returns the channel to the serial console
 */
struct aos_rpc *aos_rpc_get_serial_channel(void);

void add_new_process(struct aos_rpc *rpc, char *name, coreid_t core, domainid_t id);

void print_process_table(struct aos_rpc *rpc);
#endif // _LIB_BARRELFISH_AOS_MESSAGES_H
