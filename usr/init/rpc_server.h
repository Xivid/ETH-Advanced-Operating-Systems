/**
 * \file
 * \brief RPC server in the init process
 */

/*
 * Created by zhiyang on 11/22/17.
 */

#ifndef _INIT_RPC_SERVER_H_
#define _INIT_RPC_SERVER_H_

#include <spawn/spawn.h>

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

// macros copied from kernel/include/arch/arm/startup_arm.h
#define INIT_BOOTINFO_VBASE     ((lvaddr_t) 0x200000)
#define INIT_ARGS_VBASE         (INIT_BOOTINFO_VBASE + BOOTINFO_SIZE)
#define INIT_DISPATCHER_VBASE   (INIT_ARGS_VBASE + ARGS_SIZE)
#define MON_URPC_VBASE          (INIT_DISPATCHER_VBASE + DISPATCHER_SIZE)

#define N_LINES                 (MON_URPC_SIZE / 2 / 64)
#define LINE_WORDS              (16)
#define URPC_PAYLOAD_LEN        (10)

/* rpc declarations */
struct client {
    struct EndPoint end;  // TODO: store the capref directly? (can avoid ugly comparison in whois())
    struct client* prev;
    struct client* next;

    struct lmp_chan lmp;
} *client_list = NULL;

errval_t init_rpc(void);
errval_t recv_handler(void* arg);
errval_t whois(struct capref cap, struct client **he_is);
void* answer_number(struct capref cap, struct lmp_recv_msg *msg);
void* answer_char(struct capref cap, struct lmp_recv_msg* msg);
void* answer_str(struct capref cap, struct lmp_recv_msg* msg);
void* answer_process(struct capref cap, struct lmp_recv_msg* msg);
void* answer_init(struct capref cap);
void* answer_ram(struct capref cap, struct lmp_recv_msg* msg);
errval_t send_received(void* arg);
errval_t send_ram(void* args);
errval_t send_process(void* args);

/* urpc declarations */
void urpc_write(const uint32_t message[URPC_PAYLOAD_LEN], coreid_t core);
void urpc_read_until_ack(uint32_t *ack_response, coreid_t core);
static inline void dmb(void) { __asm volatile ("dmb"); }

/* RPC implementations */
/* Message format:
 * There are at most 9 uintptr_t-length words in msg, namely msg[0] ... msg[8]
 *
 * msg[0] is used to indicate the type of message (see enum_rpc_msgtype)
 * msg[1] ... msg[8] is the actual message
 */
errval_t init_rpc(void)
{
    errval_t err;
    err = cap_retype(cap_selfep, cap_dispatcher, 0, ObjType_EndPoint, 0, 1);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c: cap retype of dispatcher to selfep failed");
        return EXIT_FAILURE;
    }
    // TODO: make lmp a global variable, give it a more meaningful name (lmp_serv/open_lmp?)
    struct lmp_chan* lmp = (struct lmp_chan*) malloc(sizeof(struct lmp_chan));
    // by setting NULL_CAP as endpoint, we make this lmp an "open-receive" channel
    err = lmp_chan_accept(lmp, DEFAULT_LMP_BUF_WORDS, NULL_CAP);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c: lmp chan accept failed");
        return EXIT_FAILURE;
    }
    err = lmp_chan_alloc_recv_slot(lmp);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c: lmp chan alloc recv slot failed");
        return EXIT_FAILURE;
    }
    err = cap_copy(cap_initep, lmp->local_cap);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c: lmp cap copy of lmp->local_cap to cap_initep failed");
        return EXIT_FAILURE;
    }
    // the "reply-wait" operation
    err = lmp_chan_register_recv(lmp, get_default_waitset(), MKCLOSURE((void*) recv_handler, lmp));
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c: lmp chan register recv failed");
        return EXIT_FAILURE;
    }
    return SYS_ERR_OK;
}

// see also book page 98
errval_t recv_handler(void* arg)
{
    struct lmp_chan* lmp = (struct lmp_chan*) arg;
    struct lmp_recv_msg msg = LMP_RECV_MSG_INIT;
    struct capref cap;
    errval_t err = lmp_chan_recv(lmp, &msg, &cap);
    if (err_is_fail(err)) {
        if (lmp_err_is_transient(err)) {
            err = lmp_chan_recv(lmp, &msg, &cap);
        }
        if (err_is_fail(err)) {  // non-transient error, or transient but still fail after retry
            DEBUG_ERR(err, "usr/init/main.c recv_handler: lmp chan recv, non transient error");
            return err;
        }
    }

    // register again for receiving
    err = lmp_chan_alloc_recv_slot(lmp);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c recv_handler: lmp chan alloc recv slot failed");
        return err;
    }
    err = lmp_chan_register_recv(lmp, get_default_waitset(), MKCLOSURE((void*) recv_handler, arg));
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c recv_handler: lmp chan register recv failed");
        return err;
    }

    // no message content received?
    if (msg.buf.msglen <= 0)
        return err;
    void* answer;
    void* answer_args;
    switch (msg.words[0]) {
        case AOS_RPC_ID_NUM:
            answer_args = answer_number(cap, &msg);
            answer = (void*) send_received;
            break;
        case AOS_RPC_ID_INIT:
            answer_args = answer_init(cap);
            answer = (void*) send_received;
            break;
        case AOS_RPC_ID_RAM:
            answer_args = answer_ram(cap, &msg);
            answer = (void*) send_ram;
            break;
        case AOS_RPC_ID_CHAR:
            answer_args = answer_char(cap, &msg);
            answer = (void*) send_received;
            break;
        case AOS_RPC_ID_STR:
            answer_args = answer_str(cap, &msg);
            answer = (void*) send_received;
            break;
        case AOS_RPC_ID_PROCESS:
            answer_args = answer_process(cap, &msg);
            answer = (void*) send_process;
            break;
        default:
            DEBUG_ERR(LIB_ERR_NOT_IMPLEMENTED, "rpc_server.h switch: default case\n");
            return LIB_ERR_NOT_IMPLEMENTED;
    }
    struct lmp_chan* ret_chan = (struct lmp_chan*) answer_args;
    err = lmp_chan_register_send(ret_chan, get_default_waitset(), MKCLOSURE(answer, answer_args));
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c recv_handler: lmp chan register send failed");
        return err;
    }
    return SYS_ERR_OK;
}

// TODO: rewrite this with cap_compare()
errval_t whois(struct capref cap, struct client **he_is) {
    struct client *cur = client_list;
    struct capability return_cap;
    errval_t err = debug_cap_identify(cap, &return_cap);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c whois: debug identify cap failed");
        return err;
    }
    while (cur != NULL) {
        if (return_cap.u.endpoint.listener == cur->end.listener
            && return_cap.u.endpoint.epoffset == cur->end.epoffset) {
            *he_is = cur;
            break;
        }
        cur = cur->next;
    }
    return err;
}


void* answer_number(struct capref cap, struct lmp_recv_msg *msg) {
    debug_printf("server received number: %u\n", (uint32_t) msg->words[1]);

    // create answer
    struct client* he_is = NULL;
    errval_t err = whois(cap, &he_is);
    if (err_is_fail(err) || he_is == NULL) {
        DEBUG_ERR(err, "usr/init/main.c answer number: could not identify client");
        return NULL;
    }

    // lmp channel for the response handler
    return (void*) &(he_is->lmp);
}

void* answer_char(struct capref cap, struct lmp_recv_msg* msg)
{
    errval_t err = sys_print((const char *)&msg->words[1], 1);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c answer char: could not sys_print");
        return NULL;
    }

    // create answer
    struct client* he_is = NULL;
    err = whois(cap, &he_is);
    if (err_is_fail(err) || he_is == NULL) {
        DEBUG_ERR(err, "usr/init/main.c answer char: could not identify client");
        return NULL;
    }

    // lmp channel for the response handler
    return (void*) &(he_is->lmp);
}

void* answer_str(struct capref cap, struct lmp_recv_msg* msg)
{
    int len = strnlen((const char*) &msg->words[1], 32);
    //debug_printf("Got packet len(%i) %lx!\n", len, &msg->words[3]);
    errval_t err = sys_print((const char *)&msg->words[1], len);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c answer char: could not sys_print");
        return NULL;
    }

    // create answer
    struct client* he_is = NULL;
    err = whois(cap, &he_is);
    if (err_is_fail(err) || he_is == NULL) {
        DEBUG_ERR(err, "usr/init/main.c answer char: could not identify client");
        return NULL;
    }

    // lmp channel for the response handler
    return (void*) &(he_is->lmp);
}

void* answer_process(struct capref cap, struct lmp_recv_msg* msg)
{
    errval_t err, spawn_err = SYS_ERR_OK;
    domainid_t domainid;

    debug_printf("got coreid: %d, process name: %s\n", (int)msg->words[1], (char *)&msg->words[3]);
    coreid_t target_core_id = *(coreid_t *) &msg->words[1];

    if (disp_get_core_id() != target_core_id) {
        uint32_t message[URPC_PAYLOAD_LEN];
        message[0] = 1;
        message[1] = AOS_RPC_ID_PROCESS;
        strncpy((char *)(message + 2), (const char*)&msg->words[3], (URPC_PAYLOAD_LEN - 2)* 4 - 1);
        ((char *)(message + 2))[(URPC_PAYLOAD_LEN - 2)* 4] = 0;

        debug_printf("AOS_RPC_ID_PROCESS %d, msg[1] = %x\n", AOS_RPC_ID_PROCESS, message[1]);

        urpc_write(message, target_core_id);

        urpc_read_until_ack(message, disp_get_core_id());
        debug_printf("urpc_read_until_ack returned\n");
        if (err_is_fail((errval_t)message[1])) {
            debug_printf("Remote spawning failed\n");
            return NULL;
        }
        domainid = message[0];
    }
    else {
        struct spawninfo *si = malloc(sizeof(struct spawninfo));
        spawn_err = spawn_load_by_name(&msg->words[3], si);
        if (err_is_fail(spawn_err)) {
            DEBUG_ERR(spawn_err, "usr/init/main.c could not start a process\n");
            return NULL;
        }
        domainid = si->domain_id;
    }

    debug_printf("domain id is %d\n", domainid);

    // create answer
    struct client* he_is = NULL;
    err = whois(cap, &he_is);
    if (err_is_fail(err) || he_is == NULL) {
        DEBUG_ERR(err, "usr/init/main.c answer char: could not identify client");
        return NULL;
    }


    size_t size_of_args = sizeof(domainid_t) +
                          ROUND_UP(sizeof(struct lmp_chan),4) +
                          ROUND_UP(sizeof(errval_t),4);
    void* args_ptr = malloc(size_of_args);
    void* args = args_ptr;


    // add channel to args
    *((struct lmp_chan*) args) = he_is->lmp;
    // cast to void* and move pointer to after the lmp channel
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct lmp_chan), 4);
    // add error to args
    *((errval_t*) args) = spawn_err;
    // cast to void* and move pointer to after the error
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(errval_t), 4);
    *((domainid_t*) args) = domainid;

    return (void*) args_ptr;
}

// sets up the client struct for new processes
void* answer_init(struct capref cap) {
    struct client *potential = NULL;
    errval_t err = whois(cap, &potential);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c answer init: could not identify client");
        return NULL;
    }
    // already have a channel to this client
    if (potential != NULL) {
        return (void*) &(potential->lmp);
    }

    // new client, allocate a channel (it's only used for sending, receiving is always done by open-receiving)
    potential = (struct client*) malloc(sizeof(struct client));

    struct capability return_cap;
    debug_cap_identify(cap, &return_cap);
    potential->end = return_cap.u.endpoint;
    potential->prev = NULL;
    if (client_list == NULL) {
        potential->next = NULL;
    }
    else {
        potential->next = client_list;
        client_list->prev = potential;
    }
    client_list = potential;

    err = lmp_chan_accept(&potential->lmp, DEFAULT_LMP_BUF_WORDS, cap);
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c answer init: could not do lmp chan accept");
        return NULL;
    }
    return (void*) &(potential->lmp);
}

void* answer_ram(struct capref cap, struct lmp_recv_msg* msg) {
    struct client *sender = NULL;
    errval_t err = whois(cap, &sender);
    if (err_is_fail(err) || sender == NULL) {
        DEBUG_ERR(err, "usr/init/main.c answer init: could not identify client");
        return NULL;
    }
    struct capref return_cap;
    size_t alignment = ROUND_UP((size_t) msg->words[2], BASE_PAGE_SIZE);
    alignment = max(alignment, BASE_PAGE_SIZE); // in case alignment is 0
    size_t allocated_size = ROUND_UP(msg->words[1], alignment);
    err = ram_alloc_aligned(&return_cap, (size_t) msg->words[1], (size_t) msg->words[2]);


    size_t size_of_args = sizeof(size_t) + ROUND_UP(sizeof(struct lmp_chan),4) + ROUND_UP(sizeof(errval_t),4) + ROUND_UP(sizeof(struct capref),4);
    void* args_ptr = malloc(size_of_args);
    void* args = args_ptr;


    // add channel to args
    *((struct lmp_chan*) args) = sender->lmp;
    // cast to void* and move pointer to after the lmp channel
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct lmp_chan), 4);
    // add error to args
    *((errval_t*) args) = err;
    // cast to void* and move pointer to after the error
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(errval_t), 4);
    // add cap to args
    *((struct capref*) args) = return_cap;
    // cast t void* and move pointer
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct capref), 4);
    *((size_t*) args) = allocated_size;

    return (void*) args_ptr;
}

// handler to send a signal that the message was received
errval_t send_received(void* arg) {
    struct lmp_chan* lmp = (struct lmp_chan*) arg;
    errval_t err = lmp_chan_send1(lmp, LMP_FLAG_SYNC, NULL_CAP, 1); // send a 1 to signal that the message arrived
    if (err_is_fail(err)) {
        DEBUG_ERR(err, "usr/init/main.c send received: could not do lmp chan send1");
        return err;
    }
    return SYS_ERR_OK;
}

errval_t send_ram(void* args) {
    // get channel
    struct lmp_chan* lmp = (struct lmp_chan*) args;
    // cast to void* and move pointer to after the lmp channel
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct lmp_chan), 4);
    // get error
    errval_t* err = (errval_t*) args;
    // cast to void* and move pointer to after the error
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(errval_t), 4);
    // get cap
    struct capref* cap = (struct capref*) args;
    // cast t void* and move pointer
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct capref), 4);
    size_t* allocated_size = (size_t*) args;

    errval_t err_send = lmp_chan_send3(lmp, LMP_FLAG_SYNC, *cap, (size_t)(err_is_fail(*err)? 0:1), *allocated_size, (uintptr_t) *err);
    if (err_is_fail(err_send)) {
        DEBUG_ERR(err_send, "usr/init/main.c send ram: could not do lmp chan send3");
        return err_send;
    }

    return SYS_ERR_OK;
}

errval_t send_process(void *args) {
    // get channel
    struct lmp_chan* lmp = (struct lmp_chan*) args;
    // cast to void* and move pointer to after the lmp channel
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(struct lmp_chan), 4);
    // get error
    errval_t* err = (errval_t*) args;
    // cast to void* and move pointer to after the error
    args = (void*) ROUND_UP((uintptr_t) args + sizeof(errval_t), 4);
    domainid_t *domain_id = (domainid_t*) args;

    errval_t err_send = lmp_chan_send3(lmp, LMP_FLAG_SYNC, NULL_CAP, (size_t)(err_is_fail(*err)? 0:1), *domain_id, (uintptr_t) *err);
    if (err_is_fail(err_send)) {
        DEBUG_ERR(err_send, "usr/init/main.c send ram: could not do lmp chan send3");
        return err_send;
    }

    return SYS_ERR_OK;
}

/* urpc implementations */
void *urpc_shared_base;
uint32_t current_write_offset = 0;
uint32_t current_read_offset = 0;

void urpc_write(const uint32_t message[URPC_PAYLOAD_LEN], coreid_t core)
{
    volatile uint32_t *tx = (uint32_t *)urpc_shared_base + core * N_LINES * LINE_WORDS + current_write_offset*LINE_WORDS;
    while (*(tx + LINE_WORDS -1));

    for (int i = 0; i < URPC_PAYLOAD_LEN; i++) {
        tx[i] = message[i];
    }

    dmb();

    tx[LINE_WORDS - 1] = 1;

    current_write_offset++;
    current_write_offset %= N_LINES;
}

void urpc_read_until_ack(uint32_t *ack_response, coreid_t core)
{
    while (true) {
        volatile uint32_t *rx = (uint32_t *)urpc_shared_base + core * N_LINES * LINE_WORDS + current_read_offset * LINE_WORDS;
        while (!*(rx + LINE_WORDS - 1));

        dmb();

        debug_printf("rx[0] = %x, rx[1] = %x, rx[2] = %x, rx[3] = %x\n", rx[0], rx[1], rx[2], rx[3]);
        if (rx[0] == 1) {
            if (rx[1] == 1) {
                for (int i = 0; i < URPC_PAYLOAD_LEN - 1; i++) {
                    ack_response[i] = rx[i+2];
                }
                return;
            }

            struct spawninfo *si;
            void *name = (uint32_t *) rx + 2;
            debug_printf("rx[1] = %x\n", rx[1]);
            switch (rx[1]) {
                case AOS_RPC_ID_PROCESS:
                    si = malloc(sizeof(struct spawninfo));
                    errval_t err = spawn_load_by_name(name, si);
                    debug_printf("spawn returned\n");
                    uint32_t process_ack[URPC_PAYLOAD_LEN];
                    process_ack[0] = 1;
                    process_ack[1] = 1;
                    process_ack[2] = si->domain_id;
                    process_ack[3] = err;
                    urpc_write(process_ack, core ? 0 : 1);
                    break;
                default:
                    debug_printf("Message type not supported by init\n");
                    return;
            }
        } else {
            debug_printf("Forwarding not implemented!\n");
        }

        current_read_offset++;
        current_read_offset %= N_LINES;
    }
}

#endif /* _INIT_RPC_SERVER_H_ */
