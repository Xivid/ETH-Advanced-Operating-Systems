#ifndef __ERRNO_BARRELFISH__
#define __ERRNO_BARRELFISH__
/* Includes: */
 
#include <stdint.h>
#include <stdbool.h>
 
/* Type Declarations: */
 
typedef uintptr_t errval_t;
enum err_code {
    SYS_ERR_OK = 0,
    SYS_ERR_NOT_IMPLEMENTED = 5,
    SYS_ERR_ILLEGAL_SYSCALL = 6,
    SYS_ERR_INVARGS_SYSCALL = 7,
    SYS_ERR_CALLER_ENABLED = 8,
    SYS_ERR_CALLER_DISABLED = 9,
    SYS_ERR_ILLEGAL_INVOCATION = 10,
    SYS_ERR_INVALID_USER_BUFFER = 11,
    SYS_ERR_LMP_NO_TARGET = 12,
    SYS_ERR_LMP_TARGET_DISABLED = 13,
    SYS_ERR_LMP_BUF_OVERFLOW = 14,
    SYS_ERR_LMP_EP_STATE_INVALID = 15,
    SYS_ERR_LMP_CAPTRANSFER_SRC_LOOKUP = 16,
    SYS_ERR_LMP_CAPTRANSFER_DST_CNODE_LOOKUP = 17,
    SYS_ERR_LMP_CAPTRANSFER_DST_CNODE_INVALID = 18,
    SYS_ERR_LMP_CAPTRANSFER_DST_SLOT_OCCUPIED = 19,
    SYS_ERR_LRPC_SLOT_INVALID = 20,
    SYS_ERR_LRPC_NOT_L1 = 21,
    SYS_ERR_LRPC_NOT_L2 = 22,
    SYS_ERR_LRPC_NOT_ENDPOINT = 23,
    SYS_ERR_INVALID_EPLEN = 24,
    SYS_ERR_IDC_MSG_BOUNDS = 25,
    SYS_ERR_CNODE_NOT_FOUND = 26,
    SYS_ERR_CNODE_TYPE = 27,
    SYS_ERR_CNODE_RIGHTS = 28,
    SYS_ERR_DEPTH_EXCEEDED = 29,
    SYS_ERR_GUARD_MISMATCH = 30,
    SYS_ERR_CAP_NOT_FOUND = 31,
    SYS_ERR_IDENTIFY_LOOKUP = 32,
    SYS_ERR_L1_CNODE_INDEX = 33,
    SYS_ERR_CAP_LOOKUP_DEPTH = 34,
    SYS_ERR_RESIZE_NOT_L1 = 35,
    SYS_ERR_SLOT_IN_USE = 36,
    SYS_ERR_SLOT_LOOKUP_FAIL = 37,
    SYS_ERR_CNODE_NOT_ROOT = 38,
    SYS_ERR_GUARD_SIZE_OVERFLOW = 39,
    SYS_ERR_INVALID_SOURCE_TYPE = 40,
    SYS_ERR_ILLEGAL_DEST_TYPE = 41,
    SYS_ERR_SOURCE_CAP_LOOKUP = 42,
    SYS_ERR_SOURCE_ROOTCN_LOOKUP = 43,
    SYS_ERR_DEST_CNODE_LOOKUP = 44,
    SYS_ERR_DEST_ROOTCN_LOOKUP = 45,
    SYS_ERR_DEST_CNODE_INVALID = 46,
    SYS_ERR_ROOT_CAP_LOOKUP = 47,
    SYS_ERR_DEST_TYPE_INVALID = 48,
    SYS_ERR_INVALID_RETYPE = 49,
    SYS_ERR_RETYPE_MAPPING_EXPLICIT = 50,
    SYS_ERR_RETYPE_INVALID_COUNT = 51,
    SYS_ERR_REVOKE_FIRST = 52,
    SYS_ERR_INVALID_SIZE_BITS = 53,
    SYS_ERR_INVALID_SIZE = 54,
    SYS_ERR_SLOTS_INVALID = 55,
    SYS_ERR_SLOTS_IN_USE = 56,
    SYS_ERR_RETYPE_CREATE = 57,
    SYS_ERR_RETYPE_INVALID_OFFSET = 58,
    SYS_ERR_RETYPE_INVALID_OBJSIZE = 59,
    SYS_ERR_NO_LOCAL_COPIES = 60,
    SYS_ERR_RETRY_THROUGH_MONITOR = 61,
    SYS_ERR_TYPE_NOT_CREATABLE = 62,
    SYS_ERR_DELETE_LAST_OWNED = 63,
    SYS_ERR_DELETE_REMOTE_LOCAL = 64,
    SYS_ERR_CAP_LOCKED = 65,
    SYS_ERR_RAM_CAP_CREATED = 1,
    SYS_ERR_VNODE_SLOT_INVALID = 66,
    SYS_ERR_WRONG_MAPPING = 67,
    SYS_ERR_FRAME_OFFSET_INVALID = 68,
    SYS_ERR_VNODE_SLOT_RESERVED = 69,
    SYS_ERR_VNODE_SLOT_INUSE = 70,
    SYS_ERR_VNODE_TYPE = 71,
    SYS_ERR_VNODE_LOOKUP_NEXT = 72,
    SYS_ERR_VNODE_NOT_INSTALLED = 73,
    SYS_ERR_VM_ALREADY_MAPPED = 74,
    SYS_ERR_VM_MAP_SIZE = 75,
    SYS_ERR_VM_MAP_OFFSET = 76,
    SYS_ERR_VM_RETRY_SINGLE = 77,
    SYS_ERR_VM_FRAME_UNALIGNED = 78,
    SYS_ERR_VM_FRAME_TOO_SMALL = 79,
    SYS_ERR_IRQ_LOOKUP = 80,
    SYS_ERR_IRQ_NOT_ENDPOINT = 81,
    SYS_ERR_IRQ_NO_LISTENER = 82,
    SYS_ERR_IRQ_INVALID = 83,
    SYS_ERR_IRQ_NO_FREE_VECTOR = 84,
    SYS_ERR_IRQ_LOOKUP_DEST = 85,
    SYS_ERR_IRQ_LOOKUP_EP = 86,
    SYS_ERR_IRQ_NOT_IRQ_TYPE = 87,
    SYS_ERR_IRQ_WRONG_CONTROLLER = 88,
    SYS_ERR_IO_PORT_INVALID = 89,
    SYS_ERR_DISP_CSPACE_ROOT = 90,
    SYS_ERR_DISP_CSPACE_INVALID = 91,
    SYS_ERR_DISP_VSPACE_ROOT = 92,
    SYS_ERR_DISP_VSPACE_INVALID = 93,
    SYS_ERR_DISP_FRAME = 94,
    SYS_ERR_DISP_FRAME_INVALID = 95,
    SYS_ERR_DISP_FRAME_SIZE = 96,
    SYS_ERR_DISP_NOT_RUNNABLE = 97,
    SYS_ERR_DISP_CAP_LOOKUP = 98,
    SYS_ERR_DISP_CAP_INVALID = 99,
    SYS_ERR_KERNEL_MEM_LOOKUP = 100,
    SYS_ERR_KERNEL_MEM_INVALID = 101,
    SYS_ERR_CORE_NOT_FOUND = 102,
    SYS_ERR_ARCHITECTURE_NOT_SUPPORTED = 103,
    SYS_ERR_INVALID_YIELD_TARGET = 104,
    SYS_ERR_DISP_OCAP_LOOKUP = 105,
    SYS_ERR_DISP_OCAP_TYPE = 106,
    SYS_ERR_VMKIT_UNAVAIL = 107,
    SYS_ERR_VMKIT_VMCB = 108,
    SYS_ERR_VMKIT_VMCB_INVALID = 109,
    SYS_ERR_VMKIT_CTRL = 110,
    SYS_ERR_VMKIT_CTRL_INVALID = 111,
    SYS_ERR_VMKIT_ENDPOINT = 112,
    SYS_ERR_VMKIT_ENDPOINT_INVALID = 113,
    SYS_ERR_VMKIT_VMX_VMFAIL_INVALID = 114,
    SYS_ERR_VMKIT_VMX_VMFAIL_VALID = 115,
    SYS_ERR_SERIAL_PORT_INVALID = 116,
    SYS_ERR_SERIAL_PORT_UNAVAILABLE = 117,
    SYS_ERR_PERFMON_NOT_AVAILABLE = 118,
    SYS_ERR_SYNC_MISS = 119,
    SYS_ERR_ID_SPACE_EXHAUSTED = 120,
    SYS_ERR_I2C_UNINITIALIZED = 121,
    SYS_ERR_I2C_ZERO_LENGTH_MSG = 122,
    SYS_ERR_I2C_WAIT_FOR_BUS = 123,
    SYS_ERR_I2C_FAILURE = 124,
    SYS_ERR_KCB_NOT_FOUND = 125,
    CAPS_ERR_INVALID_ARGS = 126,
    CAPS_ERR_MDB_ALREADY_INITIALIZED = 127,
    CAPS_ERR_MDB_INVALID_STATE = 128,
    CAPS_ERR_MDB_INVARIANT_VIOLATION = 129,
    CAPS_ERR_MDB_DUPLICATE_ENTRY = 130,
    CAPS_ERR_MDB_ENTRY_NOTFOUND = 131,
    CAPS_ERR_CAP_NOT_FOUND = 132,
    LIB_ERR_WHILE_DELETING = 133,
    LIB_ERR_WHILE_FREEING_SLOT = 134,
    LIB_ERR_MALLOC_FAIL = 135,
    LIB_ERR_SLAB_ALLOC_FAIL = 136,
    LIB_ERR_SLAB_REFILL = 137,
    LIB_ERR_NOT_IMPLEMENTED = 138,
    LIB_ERR_SHOULD_NOT_GET_HERE = 139,
    LIB_ERR_NOT_CNODE = 140,
    LIB_ERR_CNODE_TYPE = 141,
    LIB_ERR_CNODE_SLOTS = 142,
    LIB_ERR_CROOT_NULL = 143,
    LIB_ERR_FRAME_ALLOC = 144,
    LIB_ERR_FRAME_CREATE = 145,
    LIB_ERR_FRAME_CREATE_MS_CONSTRAINTS = 146,
    LIB_ERR_VNODE_CREATE = 147,
    LIB_ERR_CNODE_CREATE = 148,
    LIB_ERR_CNODE_CREATE_FROM_MEM = 149,
    LIB_ERR_CNODE_CREATE_FOREIGN_L2 = 150,
    LIB_ERR_RAM_ALLOC = 151,
    LIB_ERR_RAM_ALLOC_WRONG_SIZE = 152,
    LIB_ERR_RAM_ALLOC_MS_CONSTRAINTS = 153,
    LIB_ERR_CAP_MINT = 154,
    LIB_ERR_CAP_COPY = 155,
    LIB_ERR_CAP_RETYPE = 156,
    LIB_ERR_DEVFRAME_TYPE = 157,
    LIB_ERR_CAP_DELETE = 158,
    LIB_ERR_CAP_DESTROY = 159,
    LIB_ERR_CAP_INVOKE = 160,
    LIB_ERR_ENDPOINT_CREATE = 161,
    LIB_ERR_FRAME_IDENTIFY = 162,
    LIB_ERR_VNODE_MAP = 163,
    LIB_ERR_VNODE_UNMAP = 164,
    LIB_ERR_IDC_ENDPOINT_ALLOC = 165,
    LIB_ERR_SLOT_ALLOC_INIT = 166,
    LIB_ERR_SLOT_ALLOC_NO_SPACE = 167,
    LIB_ERR_SLOT_ALLOC_WRONG_CNODE = 168,
    LIB_ERR_SINGLE_SLOT_ALLOC_INIT_RAW = 169,
    LIB_ERR_SINGLE_SLOT_ALLOC_INIT = 170,
    LIB_ERR_MULTI_SLOT_ALLOC_INIT = 171,
    LIB_ERR_MULTI_SLOT_ALLOC_INIT_RAW = 172,
    LIB_ERR_SINGLE_SLOT_ALLOC = 173,
    LIB_ERR_RANGE_ALLOC_NOT_HEAD = 174,
    LIB_ERR_SLOT_ALLOC = 175,
    LIB_ERR_SLOT_FREE = 176,
    LIB_ERR_SLOT_UNALLOCATED = 177,
    LIB_ERR_ROOTSA_RESIZE = 178,
    LIB_ERR_VSPACE_CURRENT_INIT = 179,
    LIB_ERR_VSPACE_INIT = 180,
    LIB_ERR_VSPACE_LAYOUT_INIT = 181,
    LIB_ERR_VSPACE_DESTROY = 182,
    LIB_ERR_VSPACE_REGION_OVERLAP = 183,
    LIB_ERR_VSPACE_ADD_REGION = 184,
    LIB_ERR_VSPACE_REMOVE_REGION = 185,
    LIB_ERR_VSPACE_PAGEFAULT_HANDER = 186,
    LIB_ERR_VSPACE_VREGION_NOT_FOUND = 187,
    LIB_ERR_VSPACE_PAGEFAULT_ADDR_NOT_FOUND = 188,
    LIB_ERR_VSPACE_PINNED_INIT = 189,
    LIB_ERR_VSPACE_PINNED_ALLOC = 190,
    LIB_ERR_VSPACE_PINNED_INVALID_TYPE = 191,
    LIB_ERR_VREGION_MAP = 192,
    LIB_ERR_VREGION_MAP_FIXED = 193,
    LIB_ERR_VREGION_NOT_FOUND = 194,
    LIB_ERR_VREGION_DESTROY = 195,
    LIB_ERR_VREGION_PAGEFAULT_HANDLER = 196,
    LIB_ERR_VREGION_BAD_ALIGNMENT = 197,
    LIB_ERR_MEMOBJ_CREATE_ANON = 198,
    LIB_ERR_MEMOBJ_CREATE_ONE_FRAME = 199,
    LIB_ERR_MEMOBJ_CREATE_ONE_FRAME_ONE_MAP = 200,
    LIB_ERR_MEMOBJ_CREATE_PINNED = 201,
    LIB_ERR_MEMOBJ_CREATE_VFS = 202,
    LIB_ERR_MEMOBJ_MAP_REGION = 203,
    LIB_ERR_MEMOBJ_UNMAP_REGION = 204,
    LIB_ERR_MEMOBJ_PIN_REGION = 205,
    LIB_ERR_MEMOBJ_UNPIN_REGION = 206,
    LIB_ERR_MEMOBJ_FILL = 207,
    LIB_ERR_MEMOBJ_PAGEFAULT_HANDLER = 208,
    LIB_ERR_MEMOBJ_PAGER_FREE = 209,
    LIB_ERR_MEMOBJ_WRONG_OFFSET = 210,
    LIB_ERR_MEMOBJ_FRAME_ALLOC = 211,
    LIB_ERR_MEMOBJ_VREGION_ALREADY_MAPPED = 212,
    LIB_ERR_MEMOBJ_UNFILL_TOO_HIGH_OFFSET = 213,
    LIB_ERR_MEMOBJ_PROTECT = 214,
    LIB_ERR_MEMOBJ_DUPLICATE_FILL = 215,
    LIB_ERR_PMAP_INIT = 216,
    LIB_ERR_PMAP_CURRENT_INIT = 217,
    LIB_ERR_PMAP_DETERMINE_ADDR = 218,
    LIB_ERR_PMAP_DO_MAP = 219,
    LIB_ERR_PMAP_MAP = 220,
    LIB_ERR_PMAP_DO_SINGLE_MAP = 221,
    LIB_ERR_PMAP_UNMAP = 222,
    LIB_ERR_PMAP_DO_SINGLE_UNMAP = 223,
    LIB_ERR_PMAP_MODIFY_FLAGS = 224,
    LIB_ERR_PMAP_GET_PTABLE = 225,
    LIB_ERR_PMAP_ALLOC_VNODE = 226,
    LIB_ERR_PMAP_ADDR_NOT_FREE = 227,
    LIB_ERR_PMAP_FIND_VNODE = 228,
    LIB_ERR_PMAP_EXISTING_MAPPING = 229,
    LIB_ERR_PMAP_FRAME_SIZE = 230,
    LIB_ERR_PMAP_FRAME_IDENTIFY = 231,
    LIB_ERR_PMAP_NOT_MAPPED = 232,
    LIB_ERR_OUT_OF_VIRTUAL_ADDR = 233,
    LIB_ERR_SERIALISE_BUFOVERFLOW = 234,
    LIB_ERR_VSPACE_MAP = 235,
    LIB_ERR_VSPACE_MMU_AWARE_INIT = 236,
    LIB_ERR_VSPACE_MMU_AWARE_MAP = 237,
    LIB_ERR_VSPACE_MMU_AWARE_NO_SPACE = 238,
    LIB_ERR_INVOKE_PERFMON_SETUP = 239,
    LIB_ERR_INVOKE_PERFMON_WRITE = 240,
    LIB_ERR_CORESET_NEW = 241,
    LIB_ERR_CORESET_GET_NEXT_DONE = 242,
    LIB_ERR_NO_LMP_MSG = 243,
    LIB_ERR_LMP_RECV_BUF_OVERFLOW = 244,
    LIB_ERR_NO_UMP_MSG = 245,
    LIB_ERR_UMP_CHAN_FULL = 246,
    LIB_ERR_LMP_BUFLEN_INVALID = 247,
    LIB_ERR_NO_ENDPOINT_SPACE = 248,
    LIB_ERR_UMP_BUFSIZE_INVALID = 249,
    LIB_ERR_UMP_BUFADDR_INVALID = 250,
    LIB_ERR_UMP_FRAME_OVERFLOW = 251,
    LIB_ERR_LMP_ENDPOINT_REGISTER = 252,
    LIB_ERR_CHAN_REGISTER_SEND = 253,
    LIB_ERR_CHAN_DEREGISTER_SEND = 254,
    LIB_ERR_CHAN_REGISTER_RECV = 255,
    LIB_ERR_CHAN_DEREGISTER_RECV = 256,
    LIB_ERR_LMP_CHAN_INIT = 257,
    LIB_ERR_UMP_CHAN_INIT = 258,
    LIB_ERR_LMP_CHAN_RECV = 259,
    LIB_ERR_UMP_CHAN_RECV = 260,
    LIB_ERR_LMP_CHAN_SEND = 261,
    LIB_ERR_LMP_CHAN_BIND = 262,
    LIB_ERR_UMP_CHAN_BIND = 263,
    LIB_ERR_LMP_CHAN_ACCEPT = 264,
    LIB_ERR_UMP_CHAN_ACCEPT = 265,
    LIB_ERR_LMP_ALLOC_RECV_SLOT = 266,
    LIB_ERR_LMP_NOT_CONNECTED = 267,
    LIB_ERR_MSGBUF_OVERFLOW = 268,
    LIB_ERR_MSGBUF_CANNOT_GROW = 269,
    LIB_ERR_RCK_NOTIFY = 270,
    LIB_ERR_IPI_NOTIFY = 271,
    LIB_ERR_MONITOR_CLIENT_BIND = 272,
    LIB_ERR_MONITOR_CLIENT_ACCEPT = 273,
    LIB_ERR_NAMESERVICE_NOT_BOUND = 274,
    LIB_ERR_NAMESERVICE_UNKNOWN_NAME = 275,
    LIB_ERR_NAMESERVICE_INVALID_NAME = 276,
    LIB_ERR_BIND_LMP_REQ = 277,
    LIB_ERR_BIND_UMP_REQ = 278,
    LIB_ERR_BIND_LMP_REPLY = 279,
    LIB_ERR_BIND_UMP_REPLY = 280,
    LIB_ERR_NO_LMP_BIND_HANDLER = 281,
    LIB_ERR_NO_UMP_BIND_HANDLER = 282,
    LIB_ERR_MONITOR_CAP_SEND = 283,
    LIB_ERR_MONITOR_RPC_BIND = 284,
    LIB_ERR_MONITOR_RPC_NULL = 285,
    LIB_ERR_BIND_MULTIHOP_REQ = 286,
    LIB_ERR_NO_MULTIHOP_BIND_HANDLER = 287,
    LIB_ERR_BIND_MULTIHOP_SAME_CORE = 288,
    LIB_ERR_BULK_UNKNOWN_ID = 289,
    LIB_ERR_NO_SPANNED_DISP = 290,
    LIB_ERR_SEND_RUN_FUNC_REQUEST = 291,
    LIB_ERR_SEND_CAP_REQUEST = 292,
    LIB_ERR_CAP_COPY_FAIL = 293,
    LIB_ERR_CAP_DELETE_FAIL = 294,
    LIB_ERR_RAM_ALLOC_SET = 295,
    LIB_ERR_MORECORE_INIT = 296,
    LIB_ERR_MONITOR_CLIENT_INIT = 297,
    LIB_ERR_MONITOR_CLIENT_CONNECT = 298,
    LIB_ERR_TERMINAL_INIT = 299,
    LIB_ERR_DOMAIN_INIT = 300,
    LIB_ERR_GET_MON_BLOCKING_IREF = 301,
    LIB_ERR_GET_MEM_IREF = 302,
    LIB_ERR_GET_NAME_IREF = 303,
    LIB_ERR_GET_RAMFS_IREF = 304,
    LIB_ERR_NAMESERVICE_CLIENT_INIT = 305,
    LIB_ERR_THREAD_CREATE = 306,
    LIB_ERR_THREAD_JOIN = 307,
    LIB_ERR_THREAD_JOIN_DETACHED = 308,
    LIB_ERR_THREAD_DETACHED = 309,
    LIB_ERR_CHAN_ALREADY_REGISTERED = 310,
    LIB_ERR_CHAN_NOT_REGISTERED = 311,
    LIB_ERR_WAITSET_IN_USE = 312,
    LIB_ERR_WAITSET_CHAN_CANCEL = 313,
    LIB_ERR_NO_EVENT = 314,
    LIB_ERR_EVENT_DISPATCH = 315,
    LIB_ERR_EVENT_ALREADY_RUN = 316,
    LIB_ERR_EVENT_QUEUE_EMPTY = 317,
    LIB_ERR_SEGBASE_OVER_4G_LIMIT = 318,
    LIB_ERR_LDT_FULL = 319,
    LIB_ERR_LDT_SELECTOR_INVALID = 320,
    FLOUNDER_ERR_INVALID_STATE = 321,
    FLOUNDER_ERR_TX_BUSY = 322,
    FLOUNDER_ERR_TX_MSG_SIZE = 323,
    FLOUNDER_ERR_RX_EMPTY_MSG = 324,
    FLOUNDER_ERR_RX_INVALID_MSGNUM = 325,
    FLOUNDER_ERR_RX_INVALID_LENGTH = 326,
    FLOUNDER_ERR_BUF_RECV_MORE = 327,
    FLOUNDER_ERR_BUF_SEND_MORE = 328,
    FLOUNDER_ERR_GENERIC_BIND_NO_MORE_DRIVERS = 329,
    FLOUNDER_ERR_CHANGE_WAITSET = 330,
    FLOUNDER_ERR_CHANGE_MONITOR_WAITSET = 331,
    FLOUNDER_ERR_UMP_ALLOC_NOTIFY = 332,
    FLOUNDER_ERR_UMP_STORE_NOTIFY = 333,
    FLOUNDER_ERR_BIND = 334,
    FLOUNDER_ERR_CREATE_MSG = 335,
    FLOUNDER_ERR_MARSHALLING = 336,
    FLOUNDER_ERR_DEMARSHALLING = 337,
    FLOUNDER_ERR_RPC_MISMATCH = 338,
    CHIPS_ERR_GET_SERVICE_REFERENCE = 339,
    CHIPS_ERR_GET_SERVICE_IREF = 340,
    CHIPS_ERR_UNKNOWN_NAME = 341,
    CHIPS_ERR_EXISTS = 342,
    CHIPS_ERR_GET_CAP = 343,
    CHIPS_ERR_PUT_CAP = 344,
    CHIPS_ERR_REMOVE_CAP = 345,
    CHIPS_ERR_OUT_OF_SEMAPHORES = 346,
    BCAST_ERR_SEND = 347,
    BCAST_ERR_SEND_SSF = 348,
    MON_CLIENT_ERR_SPAN_DOMAIN_REQUEST = 349,
    MON_CLIENT_ERR_URPC_BLOCK = 350,
    MON_ERR_IDC_BIND_NOT_SAME_CORE = 351,
    MON_ERR_IDC_BIND_LOCAL = 352,
    MON_ERR_INVALID_CORE_ID = 353,
    MON_ERR_INVALID_IREF = 354,
    MON_ERR_IREF_ALLOC = 355,
    MON_ERR_SPAN_STATE_ALLOC = 356,
    MON_ERR_SEND_REMOTE_MSG = 357,
    MON_ERR_INVALID_MON_ID = 358,
    MON_ERR_NO_MONITOR_FOR_CORE = 359,
    MON_ERR_CAP_IDENTIFY = 360,
    MON_ERR_CAP_CREATE = 361,
    MON_ERR_CAP_REMOTE = 362,
    MON_ERR_CAP_FOREIGN = 363,
    MON_ERR_CAP_MOVE = 364,
    MON_ERR_RCAP_DB_NOT_FOUND = 365,
    MON_ERR_RCAP_DB_LOCK = 366,
    MON_ERR_RCAP_DB_UNLOCK = 367,
    MON_ERR_RCAP_DB_ADD = 368,
    MON_ERR_SAME_CORE = 369,
    MON_ERR_REMOTE_CAP_NEED_REVOKE = 370,
    MON_ERR_REMOTE_CAP_RETRY = 371,
    MON_ERR_SPAWN_CORE = 372,
    MON_ERR_SPAWN_DOMAIN = 373,
    MON_ERR_INTERN_NEW_MONITOR = 374,
    MON_ERR_CAP_SEND = 375,
    MON_ERR_CAP_SEND_TRANSIENT = 376,
    MON_ERR_ROUTE_SET = 377,
    MON_ERR_SPAN_DOMAIN = 378,
    MON_ERR_MAP_URPC_CHAN = 379,
    MON_ERR_RAM_ALLOC_ERR = 380,
    MON_ERR_RAM_ALLOC_RETERR = 381,
    MON_ERR_MULTICAST_PAGE_MAP = 382,
    MON_ERR_WRONG_CAP_TYPE = 383,
    MON_ERR_INTERN_SET = 384,
    MON_ERR_ROUTE_RESET = 385,
    MON_ERR_MAP_MULTIBOOT = 386,
    MON_ERR_UNICAST_SET = 387,
    MON_ERR_MULTICAST_SET = 388,
    MON_ERR_BCAST_INIT = 389,
    MON_ERR_BCAST_CONNECT = 390,
    MON_ERR_CCAST_INIT = 391,
    MON_ERR_CCAST_CONNECT = 392,
    MON_ERR_UNICAST_CONNECT = 393,
    MON_ERR_MULTICAST_CONNECT = 394,
    MON_ERR_UNICAST_INIT = 395,
    MON_ERR_MULTICAST_INIT = 396,
    MON_ERR_SPAWN_XCORE_MONITOR = 397,
    MON_ERR_INCOMPLETE_ROUTE = 398,
    MON_ERR_RSRC_ALLOC = 399,
    MON_ERR_RSRC_MEMBER_LIMIT = 400,
    MON_ERR_RSRC_ILL_MANIFEST = 401,
    MON_ERR_RSRC_NOT_FOUND = 402,
    MON_ERR_CAPOPS_BUSY = 403,
    MON_ERR_INVOKE_IRQ_ALLOCATE = 404,
    MON_ERR_INVOKE_IRQ_SET = 405,
    ROUTE_ERR_NEW_ROUTE = 406,
    ROUTE_ERR_EXPORT = 407,
    ROUTE_ERR_LOOKUP = 408,
    ROUTE_ERR_BIND = 409,
    ROUTE_ERR_CORE_NOT_FOUND = 410,
    ROUTE_ERR_SET_EXPECTED = 411,
    ROUTE_ERR_SEND = 412,
    ROUTE_ERR_NO_SLOTS = 413,
    ROUTE_ERR_WRONG_GROUP_ID = 414,
    ROUTE_ERR_CALL_INIT = 415,
    ROUTE_ERR_CREATE_GROUP_RPC = 416,
    ROUTE_ERR_SET_GROUP_RPC = 417,
    ROUTE_ERR_GET_GROUP_RPC = 418,
    ROUTE_ERR_ALLOC_NID_RPC = 419,
    SPAWN_ERR_LOAD = 420,
    SPAWN_ERR_SPAN = 421,
    SPAWN_ERR_RUN = 422,
    SPAWN_ERR_VSPACE_MAP = 423,
    SPAWN_ERR_GET_CMDLINE_ARGS = 424,
    SPAWN_ERR_SETUP_ENV = 425,
    SPAWN_ERR_UNKNOWN_TARGET_ARCH = 426,
    SPAWN_ERR_UNSUPPORTED_TARGET_ARCH = 427,
    SPAWN_ERR_SETUP_CSPACE = 428,
    SPAWN_ERR_DETERMINE_CPUTYPE = 429,
    SPAWN_ERR_VSPACE_INIT = 430,
    SPAWN_ERR_SETUP_DISPATCHER = 431,
    SPAWN_ERR_ELF_MAP = 432,
    SPAWN_ERR_SET_CAPS = 433,
    SPAWN_ERR_MONEP_SLOT_ALLOC = 434,
    SPAWN_ERR_MONITOR_CLIENT = 435,
    SPAWN_ERR_FREE = 436,
    SPAWN_ERR_CREATE_ROOTCN = 437,
    SPAWN_ERR_CREATE_TASKCN = 438,
    SPAWN_ERR_MINT_TASKCN = 439,
    SPAWN_ERR_CREATE_PAGECN = 440,
    SPAWN_ERR_CREATE_VNODE = 441,
    SPAWN_ERR_COPY_VNODE = 442,
    SPAWN_ERR_CREATE_DISPATCHER = 443,
    SPAWN_ERR_CREATE_DISPATCHER_FRAME = 444,
    SPAWN_ERR_CREATE_SELFEP = 445,
    SPAWN_ERR_CREATE_ARGSPG = 446,
    SPAWN_ERR_CREATE_FDSPG = 447,
    SPAWN_ERR_MINT_ROOTCN = 448,
    SPAWN_ERR_CREATE_SLOTALLOC_CNODE = 449,
    SPAWN_ERR_MINT_BASE_PAGE_CN = 450,
    SPAWN_ERR_MINT_SEGCN = 451,
    SPAWN_ERR_MINT_PAGECN = 452,
    SPAWN_ERR_MINT_INHERITCN = 453,
    SPAWN_ERR_MAP_DISPATCHER_TO_NEW = 454,
    SPAWN_ERR_MAP_DISPATCHER_TO_SELF = 455,
    SPAWN_ERR_MAP_ARGSPG_TO_NEW = 456,
    SPAWN_ERR_MAP_ARGSPG_TO_SELF = 457,
    SPAWN_ERR_MAP_FDSPG_TO_NEW = 458,
    SPAWN_ERR_MAP_FDSPG_TO_SELF = 459,
    SPAWN_ERR_FILL_SMALLCN = 460,
    SPAWN_ERR_MAP_BOOTINFO = 461,
    SPAWN_ERR_FIND_MODULE = 462,
    SPAWN_ERR_MAP_MODULE = 463,
    SPAWN_ERR_UNMAP_MODULE = 464,
    SPAWN_ERR_CREATE_SEGCN = 465,
    SPAWN_ERR_CREATE_SMALLCN = 466,
    SPAWN_ERR_ARGSPG_OVERFLOW = 467,
    SPAWN_ERR_SERIALISE_VSPACE = 468,
    SPAWN_ERR_SETUP_INHERITED_CAPS = 469,
    SPAWN_ERR_SETUP_ARGCN = 470,
    SPAWN_ERR_COPY_ARGCN = 471,
    SPAWN_ERR_SETUP_FDCAP = 472,
    SPAWN_ERR_FDSPG_OVERFLOW = 473,
    SPAWN_ERR_SETUP_SIDCAP = 474,
    SPAWN_ERR_SETUP_KERNEL_CAP = 475,
    SPAWN_ERR_DELETE_ROOTCN = 476,
    SPAWN_ERR_FREE_ROOTCN = 477,
    SPAWN_ERR_DELETE_TASKCN = 478,
    SPAWN_ERR_FREE_TASKCN = 479,
    SPAWN_ERR_COPY_PACN = 480,
    SPAWN_ERR_COPY_MODULECN = 481,
    SPAWN_ERR_COPY_IRQ_CAP = 482,
    SPAWN_ERR_COPY_IO_CAP = 483,
    SPAWN_ERR_COPY_PERF_MON = 484,
    SPAWN_ERR_COPY_KERNEL_CAP = 485,
    SPAWN_ERR_COPY_INHERITCN_CAP = 486,
    SPAWN_ERR_DISPATCHER_SETUP = 487,
    SPAWN_ERR_DOMAIN_ALLOCATE = 488,
    SPAWN_ERR_DOMAIN_NOTFOUND = 489,
    SPAWN_ERR_DOMAIN_RUNNING = 490,
    SPAWN_ERR_FIND_SPAWNDS = 491,
    SPAWN_ERR_MALFORMED_SPAWND_RECORD = 492,
    ELF_ERR_FILESZ = 493,
    ELF_ERR_HEADER = 494,
    ELF_ERR_PROGHDR = 495,
    ELF_ERR_ALLOCATE = 496,
    ELF_ERR_NOT_PAGE_ALIGNED = 497,
    MM_ERR_FIND_NODE = 498,
    MM_ERR_CHUNK_NODE = 499,
    MM_ERR_SLOT_MM_ALLOC = 500,
    MM_ERR_SLOT_NOSLOTS = 501,
    MM_ERR_SLOT_ALLOC_INIT = 502,
    MM_ERR_MM_INIT = 503,
    MM_ERR_MM_ADD = 504,
    MM_ERR_MM_ADD_MULTI = 505,
    MM_ERR_MM_FREE = 506,
    MM_ERR_NEW_NODE = 507,
    MM_ERR_OUT_OF_BOUNDS = 508,
    MM_ERR_ALREADY_PRESENT = 509,
    MM_ERR_ALREADY_ALLOCATED = 510,
    MM_ERR_NOT_FOUND = 511,
    MM_ERR_MISSING_CAPS = 512,
    MM_ERR_CHUNK_SLOT_ALLOC = 513,
    MM_ERR_RESIZE_NODE = 514,
    MM_ERR_REALLOC_RANGE = 515,
    INIT_ERR_SPAWN_MEM_SERV = 516,
    INIT_ERR_INIT_MEM_SERV = 517,
    INIT_ERR_SPAWN_MONITOR = 518,
    INIT_ERR_INIT_MONITOR = 519,
    INIT_ERR_COPY_EP_TO_MEM_SERV = 520,
    INIT_ERR_COPY_EP_TO_MONITOR = 521,
    INIT_ERR_SETUP_MONITOR_CHAN = 522,
    INIT_ERR_SETUP_MEM_SERV_CHAN = 523,
    INIT_ERR_RUN_MONITOR = 524,
    INIT_ERR_RUN_MEM_SERV = 525,
    INIT_ERR_FREE_MONITOR = 526,
    INIT_ERR_FREE_MEM_SERV = 527,
    INIT_ERR_COPY_SUPERCN_CAP = 528,
    INIT_ERR_MAP_BOOTINFO = 529,
    INIT_ERR_COPY_KERNEL_CAP = 530,
    INIT_ERR_COPY_BSP_KCB = 531,
    INIT_ERR_COPY_IPI = 532,
    INIT_ERR_COPY_PERF_MON = 533,
    INIT_ERR_COPY_MODULECN_CAP = 534,
    INIT_ERR_COPY_PACN_CAP = 535,
    INIT_ERR_COPY_IRQ_CAP = 536,
    INIT_ERR_COPY_IO_CAP = 537,
    INIT_ERR_COPY_UMP_CAP = 538,
    INIT_ERR_NO_MATCHING_RAM_CAP = 539,
    CONT_ERR_NO_MORE_SLOTS = 540,
    ETHERSRV_ERR_TOO_MANY_BUFFERS = 541,
    ETHERSRV_ERR_TOO_MANY_VNICS = 542,
    ETHERSRV_ERR_BUFFER_NOT_FOUND = 543,
    ETHERSRV_ERR_NOT_ENOUGH_MEM = 544,
    ETHERSRV_ERR_CANT_TRANSMIT = 545,
    ETHERSRV_ERR_INVALID_STATE = 546,
    ETHERSRV_ERR_FRAME_CAP_MAP = 547,
    PORT_ERR_NOT_ENOUGH_MEMORY = 548,
    PORT_ERR_NO_MORE_PORT = 549,
    PORT_ERR_IN_USE = 550,
    PORT_ERR_REDIRECT = 551,
    PORT_ERR_NOT_FOUND = 552,
    NET_FILTER_ERR_NOT_INITIALIZED = 553,
    NET_FILTER_ERR_NOT_FOUND = 554,
    NET_FILTER_ERR_ALREADY_EXISTS = 555,
    FILTER_ERR_NOT_ENOUGH_MEMORY = 556,
    FILTER_ERR_BUFF_NOT_FOUND = 557,
    FILTER_ERR_FILTER_BUSY = 558,
    FILTER_ERR_NO_NETD_MEM = 559,
    FILTER_ERR_FILTER_NOT_FOUND = 560,
    FILTER_ERR_BUFFER_NOT_FOUND = 561,
    TERM_ERR_TERMINAL_IN_USE = 562,
    TERM_ERR_NOT_PART_OF_SESSION = 563,
    TERM_ERR_EXPORT_SESSION_INTERFACE = 564,
    TERM_ERR_REGISTER_SESSION_INTERFACE = 565,
    TERM_ERR_EXPORT_OUT_INTERFACE = 566,
    TERM_ERR_EXPORT_IN_INTERFACE = 567,
    TERM_ERR_EXPORT_CONF_INTERFACE = 568,
    TERM_ERR_ASSOCIATE_WITH_TERM_REPLY = 569,
    TERM_ERR_RECV_CHARS = 570,
    TERM_ERR_SEND_CHARS = 571,
    TERM_ERR_RECV_CONFIGURATION = 572,
    TERM_ERR_FILTER_NOT_FOUND = 573,
    TERM_ERR_TRIGGER_NOT_FOUND = 574,
    TERM_ERR_LOOKUP_SESSION_RECORD = 575,
    TERM_ERR_PARSE_SESSION_RECORD = 576,
    TERM_ERR_BIND_IN_INTERFACE = 577,
    TERM_ERR_BIND_OUT_INTERFACE = 578,
    TERM_ERR_BIND_CONF_INTERFACE = 579,
    TERM_ERR_IO = 580,
    TERM_ERR_TX_BUSY = 581,
    TERM_ERR_UNKNOWN_CONFIG_OPT = 582,
    TERM_ERR_CHANGE_WAITSET = 583,
    ANGLER_ERR_LOOKUP_TERMINAL = 584,
    ANGLER_ERR_CREATE_SESSIONID = 585,
    ANGLER_ERR_BIND_TERMINAL = 586,
    ANGLER_ERR_INIT_RPCCLIENT = 587,
    ANGLER_ERR_ASSOCIATE_WITH_TERMINAL = 588,
    ANGLER_ERR_STORE_SESSION_STATE = 589,
    TRACE_ERR_SUBSYS_DISABLED = 2,
    TRACE_ERR_NO_BUFFER = 590,
    TRACE_ERR_MAP_BUF = 591,
    TRACE_ERR_CREATE_CAP = 592,
    TRACE_ERR_CAP_COPY = 593,
    TRACE_ERR_KERNEL_INVOKE = 594,
    DRIVERKIT_ERR_NO_CAP_FOUND = 595,
    DRIVERKIT_ERR_NO_DRIVER_FOUND = 596,
    DRIVERKIT_ERR_DRIVER_DETACH = 597,
    DRIVERKIT_ERR_DRIVER_INIT = 598,
    DRIVERKIT_ERR_CONTROL_IFACE_EXPORT = 599,
    DRIVERKIT_ERR_CONTROL_SERVICE_INIT = 600,
    DRIVERKIT_ERR_CAP_CAPACITY = 601,
    PCI_ERR_DEVICE_NOT_INIT = 602,
    PCI_ERR_IOAPIC_INIT = 603,
    PCI_ERR_MINT_IOCAP = 604,
    PCI_ERR_ROUTING_IRQ = 605,
    PCI_ERR_IRQTABLE_SET = 606,
    PCI_ERR_UNKNOWN_GSI = 607,
    PCI_ERR_INVALID_VECTOR = 608,
    PCI_ERR_DEVICE_INIT = 609,
    PCI_ERR_MEM_ALLOC = 610,
    PCI_ERR_WRONG_INDEX = 611,
    PCI_ERR_MSIX_NOTSUP = 612,
    PCI_ERR_MSIX_BADVECTOR = 613,
    PCI_ERR_MSIX_DISABLED = 614,
    ACPI_ERR_NO_MCFG_TABLE = 615,
    ACPI_ERR_INVALID_PATH_NAME = 616,
    ACPI_ERR_INVALID_HANDLE = 617,
    ACPI_ERR_NO_CHILD_BRIDGE = 618,
    ACPI_ERR_GET_RESOURCES = 619,
    ACPI_ERR_SET_IRQ = 620,
    ACPI_ERR_NO_MADT_TABLE = 621,
    ACPI_ERR_OBJECT_NOT_FOUND = 622,
    VTD_ERR_INVALID_CAP = 623,
    VTD_ERR_DOM_NOT_FOUND = 624,
    VTD_ERR_DEV_NOT_FOUND = 625,
    VTD_ERR_DEV_USED = 626,
    VTD_ERR_FULL = 627,
    VTD_ERR_NO_UNITS = 628,
    VTD_ERR_NOT_ENABLED = 629,
    SKB_ERR_CONVERSION_ERROR = 630,
    SKB_ERR_EXECUTION = 631,
    SKB_ERR_EVALUATE = 632,
    SKB_ERR_RUN = 633,
    SKB_ERR_GOAL_FAILURE = 634,
    SKB_ERR_UNEXPECTED_OUTPUT = 635,
    SKB_ERR_OVERFLOW = 636,
    SKB_ERR_IO_OUTPUT = 3,
    SKB_DATAGATHERER_ERR_CPUID = 637,
    FS_ERR_INVALID_FH = 638,
    FS_ERR_NOTDIR = 639,
    FS_ERR_NOTFILE = 640,
    FS_ERR_INDEX_BOUNDS = 641,
    FS_ERR_NOTFOUND = 642,
    FS_ERR_EXISTS = 643,
    FS_ERR_NOTEMPTY = 644,
    FS_ERR_BULK_NOT_INIT = 645,
    FS_ERR_BULK_ALREADY_INIT = 646,
    VFS_ERR_EOF = 4,
    VFS_ERR_BAD_MOUNTPOINT = 647,
    VFS_ERR_MOUNTPOINT_IN_USE = 648,
    VFS_ERR_BAD_URI = 649,
    VFS_ERR_UNKNOWN_FILESYSTEM = 650,
    VFS_ERR_MOUNTPOINT_NOTFOUND = 651,
    VFS_ERR_NOT_SUPPORTED = 652,
    VFS_ERR_IN_OPEN = 653,
    VFS_ERR_IN_STAT = 654,
    VFS_ERR_IN_READ = 655,
    VFS_ERR_BCACHE_LIMIT = 656,
    NFS_ERR_TRANSPORT = 657,
    NFS_ERR_MNT_PERM = 658,
    NFS_ERR_MNT_NOENT = 659,
    NFS_ERR_MNT_IO = 660,
    NFS_ERR_MNT_ACCES = 661,
    NFS_ERR_MNT_NOTDIR = 662,
    NFS_ERR_MNT_INVAL = 663,
    NFS_ERR_MNT_NAMETOOLONG = 664,
    NFS_ERR_MNT_NOTSUPP = 665,
    NFS_ERR_MNT_SERVERFAULT = 666,
    NFS_ERR_PERM = 667,
    NFS_ERR_NOENT = 668,
    NFS_ERR_IO = 669,
    NFS_ERR_NXIO = 670,
    NFS_ERR_ACCES = 671,
    NFS_ERR_EXIST = 672,
    NFS_ERR_XDEV = 673,
    NFS_ERR_NODEV = 674,
    NFS_ERR_NOTDIR = 675,
    NFS_ERR_ISDIR = 676,
    NFS_ERR_INVAL = 677,
    NFS_ERR_FBIG = 678,
    NFS_ERR_NOSPC = 679,
    NFS_ERR_ROFS = 680,
    NFS_ERR_MLINK = 681,
    NFS_ERR_NAMETOOLONG = 682,
    NFS_ERR_NOTEMPTY = 683,
    NFS_ERR_DQUOT = 684,
    NFS_ERR_STALE = 685,
    NFS_ERR_REMOTE = 686,
    NFS_ERR_BADHANDLE = 687,
    NFS_ERR_NOT_SYNC = 688,
    NFS_ERR_BAD_COOKIE = 689,
    NFS_ERR_NOTSUPP = 690,
    NFS_ERR_TOOSMALL = 691,
    NFS_ERR_SERVERFAULT = 692,
    NFS_ERR_BADTYPE = 693,
    NFS_ERR_JUKEBOX = 694,
    LWIP_ERR_MEM = 695,
    LWIP_ERR_BUF = 696,
    LWIP_ERR_TIMEOUT = 697,
    LWIP_ERR_RTE = 698,
    LWIP_ERR_ABRT = 699,
    LWIP_ERR_RST = 700,
    LWIP_ERR_CLSD = 701,
    LWIP_ERR_CONN = 702,
    LWIP_ERR_VAL = 703,
    LWIP_ERR_ARG = 704,
    LWIP_ERR_USE = 705,
    LWIP_ERR_IF = 706,
    LWIP_ERR_ISCONN = 707,
    LWIP_ERR_INPROGRESS = 708,
    LWIP_ERR_TXFULL = 709,
    DIST_ERR_NS_REG = 710,
    DIST_ERR_NS_LOOKUP = 711,
    OCT_ERR_NO_RECORD = 712,
    OCT_ERR_NO_RECORD_NAME = 713,
    OCT_ERR_CONSTRAINT_MISMATCH = 714,
    OCT_ERR_QUERY_SIZE = 715,
    OCT_ERR_INVALID_FORMAT = 716,
    OCT_ERR_UNKNOWN_ATTRIBUTE = 717,
    OCT_ERR_UNSUPPORTED_BINDING = 718,
    OCT_ERR_PARSER_FAIL = 719,
    OCT_ERR_ENGINE_FAIL = 720,
    OCT_ERR_NO_SUBSCRIPTION = 721,
    OCT_ERR_NO_SUBSCRIBERS = 722,
    OCT_ERR_MAX_SUBSCRIPTIONS = 723,
    OCT_ERR_INVALID_ID = 724,
    OCT_ERR_CAP_NAME_UNKNOWN = 725,
    OCT_ERR_CAP_OVERWRITE = 726,
    OCT_ERR_IDCAP_INVOKE = 727,
    KALUGA_ERR_PARSE_MODULES = 728,
    KALUGA_ERR_MODULE_NOT_FOUND = 729,
    KALUGA_ERR_DRIVER_ALREADY_STARTED = 730,
    KALUGA_ERR_DRIVER_NOT_AUTO = 731,
    KALUGA_ERR_WAITING_FOR_ACPI = 732,
    KALUGA_ERR_QUERY_LOCAL_APIC = 733,
    KALUGA_ERR_UNKNOWN_PLATFORM = 734,
    THC_CANCELED = 735,
    MS_ERR_SKB = 736,
    MS_ERR_INIT_PEERS = 737,
    STARTD_ERR_BOOTMODULES = 738,
    LOX_ERR_INIT_LOCKS = 739,
    LOX_ERR_NO_LOCKS = 740,
    VBE_ERR_MODE_NOT_FOUND = 741,
    VBE_ERR_BIOS_CALL_FAILED = 742,
    AHCI_ERR_PORT_INIT = 743,
    AHCI_ERR_PORT_INVALID = 744,
    AHCI_ERR_PORT_BUSY = 745,
    AHCI_ERR_PORT_MISMATCH = 746,
    AHCI_ERR_NO_FREE_PRD = 747,
    AHCI_ERR_ILLEGAL_ARGUMENT = 748,
    SATA_ERR_INVALID_TYPE = 749,
    MMC_ERR_TRANSFER = 750,
    MMC_ERR_READ_READY = 751,
    MMC_ERR_WRITE_READY = 752,
    FAT_ERR_BAD_FS = 753,
    FS_CACHE_FULL = 754,
    FS_CACHE_NOTPRESENT = 755,
    FS_CACHE_CONFLICT = 756,
    OMAP_SDMA_ERR_NO_AVAIL_CHANNEL = 757,
    OMAP_SDMA_ERR_TRANSACTION = 758,
    OMAP_SDMA_ERR_SUPERVISOR = 759,
    OMAP_SDMA_ERR_MISALIGNED_ADDRESS = 760,
    OMAP_SDMA_ERR_HARDWARE_LIMIT_SIZE = 761,
    OMAP_SDMA_ERR_HARDWARE_LIMIT_ADDR = 762,
    OMAP_SDMA_ERR_OUT_OF_BOUNDS = 763,
    OMAP_SDMA_ERR_CAP_LOOKUP = 764,
    ERR_NOTIMP = 765,
    BULK_TRANSFER_MEM = 766,
    BULK_TRANSFER_NO_CALLBACK = 767,
    BULK_TRANSFER_CHAN_CREATE = 768,
    BULK_TRANSFER_CHAN_BIND = 769,
    BULK_TRANSFER_CHAN_ASSIGN_POOL = 770,
    BULK_TRANSFER_CHAN_STATE = 771,
    BULK_TRANSFER_CHAN_TRUST = 772,
    BULK_TRANSFER_CHAN_INVALID_EP = 773,
    BULK_TRANSFER_CHAN_DIRECTION = 774,
    BULK_TRANSFER_POOL_INVALD = 775,
    BULK_TRANSFER_POOL_NOT_ASSIGNED = 776,
    BULK_TRANSFER_POOL_ASSIGN_VETO = 777,
    BULK_TRANSFER_POOL_MAP = 778,
    BULK_TRANSFER_POOL_UNMAP = 779,
    BULK_TRANSFER_POOL_ALREADY_ASSIGNED = 780,
    BULK_TRANSFER_POOL_ALREADY_REMAPPED = 781,
    BULK_TRANSFER_BUFFER_NOT_OWNED = 782,
    BULK_TRANSFER_BUFFER_INVALID = 783,
    BULK_TRANSFER_BUFFER_ALREADY_MAPPED = 784,
    BULK_TRANSFER_BUFFER_STATE = 785,
    BULK_TRANSFER_BUFFER_REFCOUNT = 786,
    BULK_TRANSFER_BUFFER_NOT_A_COPY = 787,
    BULK_TRANSFER_BUFFER_MAP = 788,
    BULK_TRANSFER_BUFFER_UNMAP = 789,
    BULK_TRANSFER_ALLOC_BUFFER_SIZE = 790,
    BULK_TRANSFER_ALLOC_BUFFER_COUNT = 791,
    BULK_TRANSFER_INVALID_ARGUMENT = 792,
    BULK_TRANSFER_SM_NO_PENDING_MSG = 793,
    BULK_TRANSFER_SM_EXCLUSIVE_WS = 794,
    BULK_TRANSFER_NET_MAX_QUEUES = 795,
    BULK_TRANSFER_NET_POOL_USED = 796,
    VIRTIO_ERR_SIZE_INVALID = 797,
    VIRTIO_ERR_MAX_INDIRECT = 798,
    VIRTIO_ERR_CAP_SIZE = 799,
    VIRTIO_ERR_QUEUE_FULL = 800,
    VIRTIO_ERR_QUEUE_EMPTY = 801,
    VIRTIO_ERR_BACKEND = 802,
    VIRTIO_ERR_DEVICE_REGISTER = 803,
    VIRTIO_ERR_NOT_VIRTIO_DEVICE = 804,
    VIRTIO_ERR_VERSION_MISMATCH = 805,
    VIRTIO_ERR_DEVICE_STATUS = 806,
    VIRTIO_ERR_DEVICE_TYPE = 807,
    VIRTIO_ERR_DEVICE_IDLE = 808,
    VIRTIO_ERR_QUEUE_ACTIVE = 809,
    VIRTIO_ERR_QUEUE_INVALID = 810,
    VIRTIO_ERR_QUEUE_BUSY = 811,
    VIRTIO_ERR_BUFFER_SIZE = 812,
    VIRTIO_ERR_BUFFER_STATE = 813,
    VIRTIO_ERR_ARG_INVALID = 814,
    VIRTIO_ERR_NO_BUFFER = 815,
    VIRTIO_ERR_ALLOC_FULL = 816,
    VIRTIO_ERR_BUFFER_USED = 817,
    VIRTIO_ERR_NO_DESC_AVAIL = 818,
    VIRTIO_ERR_DEQ_CHAIN = 819,
    VIRTIO_ERR_INVALID_RING_INDEX = 820,
    VIRTIO_ERR_BLK_REQ_IOERR = 821,
    VIRTIO_ERR_BLK_REQ_UNSUP = 822,
    XEON_PHI_ERR_MGR_REGISTER_FAILED = 823,
    XEON_PHI_ERR_MGR_MAX_CARDS = 824,
    XEON_PHI_ERR_MSG_NOT_REACHABLE = 825,
    XEON_PHI_ERR_MSG_NOT_INITIALIZED = 826,
    XEON_PHI_ERR_CLIENT_OPEN_REJECT = 827,
    XEON_PHI_ERR_CLIENT_DOMAIN_VOID = 828,
    XEON_PHI_ERR_CLIENT_REGISTER = 829,
    XEON_PHI_ERR_CLIENT_BUSY = 830,
    XEON_PHI_ERR_INVALID_ID = 831,
    DMA_ERR_PCI_ADDRESS = 832,
    DMA_ERR_DEVICE_UNSUPPORTED = 833,
    DMA_ERR_DEVICE_IDLE = 834,
    DMA_ERR_ARG_INVALID = 835,
    DMA_ERR_RESET_TIMEOUT = 836,
    DMA_ERR_NO_DESCRIPTORS = 837,
    DMA_ERR_NO_REQUESTS = 838,
    DMA_ERR_CHAN_ERROR = 839,
    DMA_ERR_CHAN_BUSY = 840,
    DMA_ERR_CHAN_IDLE = 841,
    DMA_ERR_REQUEST_UNFINISHED = 842,
    DMA_ERR_REQUEST_UNSUPPORTED = 843,
    DMA_ERR_REQUEST_TOO_LARGE = 844,
    DMA_ERR_REQUEST_ID = 845,
    DMA_ERR_ALIGNMENT = 846,
    DMA_ERR_MEM_OVERLAP = 847,
    DMA_ERR_MEM_NOT_REGISTERED = 848,
    DMA_ERR_MEM_OUT_OF_RANGE = 849,
    DMA_ERR_SVC_REJECT = 850,
    DMA_ERR_SVC_RESOURCES = 851,
    DMA_ERR_SVC_VOID = 852,
    DMA_ERR_SVC_NO_CONNECTION = 853,
    DMA_ERR_SVC_BUSY = 854,
    XOMP_ERR_INVALID_WORKER_ARGS = 855,
    XOMP_ERR_BAD_INVOCATION = 856,
    XOMP_ERR_INVALID_MSG_FRAME = 857,
    XOMP_ERR_SPAWN_WORKER_FAILED = 858,
    XOMP_ERR_MASTER_NOT_INIT = 859,
    XOMP_ERR_WORKER_INIT_FAILED = 860,
    XOMP_ERR_WORKER_STATE = 861,
    XOMP_ERR_INVALID_MEMORY = 862,
    XOMP_ERR_INVALID_TOKEN = 863,
    XOMP_ERR_INVALID_ARGUMENTS = 864,
    NUMA_ERR_NOT_AVAILABLE = 865,
    NUMA_ERR_BITMAP_PARSE = 866,
    NUMA_ERR_BITMAP_RANGE = 867,
    NUMA_ERR_NUMA_MEMBIND = 868,
    NUMA_ERR_LIB_INIT = 869,
    NUMA_ERR_SKB = 870,
    NUMA_ERR_SKB_DATA = 871,
    NUMA_ERR_NODEID_INVALID = 872,
    NUMA_ERR_COREID_INVALID = 873,
    CPUID_ERR_UNSUPPORTED_FUNCTION = 874,
    CPUID_ERR_UNKNOWN_VENDOR = 875,
    CPUID_ERR_INVALID_INDEX = 876,
    DEVQ_ERR_INIT_QUEUE = 877,
    DEVQ_ERR_BUFFER_ID = 878,
    DEVQ_ERR_BUFFER_NOT_IN_REGION = 879,
    DEVQ_ERR_BUFFER_ALREADY_IN_USE = 880,
    DEVQ_ERR_BUFFER_NOT_IN_USE = 881,
    DEVQ_ERR_INVALID_BUFFER_ARGS = 882,
    DEVQ_ERR_INVALID_REGION_ID = 883,
    DEVQ_ERR_REGION_DESTROY = 884,
    DEVQ_ERR_INVALID_REGION_ARGS = 885,
    DEVQ_ERR_REGISTER_REGION = 886,
    DEVQ_ERR_QUEUE_EMPTY = 887,
    DEVQ_ERR_QUEUE_FULL = 888,
    DEVQ_ERR_DESCQ_INIT = 889,
    NET_QUEUE_ERR_WRONG_PORT = 890,
    NET_QUEUE_ERR_WRONG_IP = 891,
    NET_QUEUE_ERR_CHECKSUM = 892,
    NET_QUEUE_ERR_NOT_UDP = 893,
    NET_QUEUE_ERR_UNKNOWN_BUF_TYPE = 894,
    NIC_ERR_IO = 895,
    NIC_ERR_INTR = 896,
    NIC_ERR_NOSYS = 897,
    NIC_ERR_UNKNOWN = 898,
    NIC_ERR_TX_PKT = 899,
    NIC_ERR_RX_PKT = 900,
    NIC_ERR_RX_DISCARD = 901,
    NIC_ERR_ALLOC_BUF = 902,
    NIC_ERR_REGISTER_REGION = 903,
    NIC_ERR_DEREGISTER_REGION = 904,
    NIC_ERR_ALLOC_QUEUE = 905,
    NIC_ERR_ENQUEUE = 906,
    NIC_ERR_QDRIVER = 907,
    PSCI_ERR_NOT_SUPPORTED = 908,
    PSCI_ERR_INVALID_PARAMETER = 909,
    PSCI_ERR_DENIED = 910,
    PSCI_ERR_ALREADY_ON = 911,
    PSCI_ERR_ON_PENDING = 912,
    PSCI_ERR_INTERNAL_FAILURE = 913,
    PSCI_ERR_NOT_PRESENT = 914,
    PSCI_ERR_DISABLED = 915,
    PSCI_ERR_INVALID_ADDRESS = 916,
    PSCI_ERR_UNKNOWN_ERROR = 917
};
 
/* Prototypes: */
 
char* err_getcode(errval_t errval);
char* err_getdomain(errval_t errval);
char* err_getstring(errval_t errval);
static inline bool err_is_fail(errval_t errval);
static inline bool err_is_ok(errval_t errval);
static inline enum err_code err_no(errval_t errval);
void err_print_calltrace(errval_t errval);
static inline errval_t err_push(errval_t errval,enum err_code errcode);
 
/* Function Definitions: */
 
static inline bool err_is_fail(errval_t errval) {
    enum err_code _fof_x3;
 
    _fof_x3 = err_no(errval);
    return ((_fof_x3 >= 5));
}
 
static inline bool err_is_ok(errval_t errval) {
    enum err_code _fof_x2;
 
    _fof_x2 = err_no(errval);
    return ((_fof_x2 < 5));
}
 
static inline enum err_code err_no(errval_t errval) {
 
    return (((enum err_code) (errval & ((1 << 10) - 1))));
}
 
static inline errval_t err_push(errval_t errval,enum err_code errcode) {
 
    return (((errval << 10) | ((errval_t) (1023 & errcode))));
}
 
 
 
#endif // __ERRNO_BARRELFISH__