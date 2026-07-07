---

excalidraw-plugin: parsed
tags: [excalidraw]

---
==⚠  Switch to EXCALIDRAW VIEW in the MORE OPTIONS menu of this document. ⚠== You can decompress Drawing data with the command palette: 'Decompress current Excalidraw file'. For more info check in plugin settings under 'Saving'


# Excalidraw Data

## Text Elements
redis_clone_in_c/
│
├── CMakeLists.txt                               (~70 LOC)
│   │
│   ├── Libraries / Commands
│   │   ├── cmake_minimum_required()
│   │   ├── project()
│   │   ├── set()
│   │   ├── include_directories()
│   │   ├── add_executable()
│   │   ├── target_compile_options()
│   │   ├── target_link_libraries()
│   │   └── install()
│   │
│   └── Contains
│       ├── C17 standard configuration
│       ├── Windows/Linux compiler detection
│       ├── Debug/Release flags
│       ├── Warning flags
│       ├── Source file list
│       ├── Include directories
│       └── Platform libraries (ws2_32 on Windows)
│
├── include/                                     (~1,020, 896 total LOC)
│   │
│   ├── common.h                                 (~150 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── stdint.h
│   │   │   ├── stddef.h
│   │   │   ├── stdbool.h
│   │   │   ├── stdio.h
│   │   │   ├── stdlib.h
│   │   │   ├── string.h
│   │   │   ├── errno.h
│   │   │   ├── time.h
│   │   │   ├── limits.h
│   │   │   └── assert.h
│   │   │
│   │   ├── Defines
│   │   │   ├── REDIS_VERSION
│   │   │   ├── DEFAULT_PORT
│   │   │   ├── MAX_KEY_SIZE
│   │   │   ├── MAX_VALUE_SIZE
│   │   │   ├── HASH_LOAD_FACTOR
│   │   │   ├── MAX_CLIENTS
│   │   │   ├── RECV_BUFFER_SIZE
│   │   │   ├── SEND_BUFFER_SIZE
│   │   │   ├── ARENA_DEFAULT_SIZE
│   │   │   └── INLINE_BUFFER_SIZE
│   │   │
│   │   ├── typedefs
│   │   │   ├── u8
│   │   │   ├── u16
│   │   │   ├── u32
│   │   │   ├── u64
│   │   │   ├── i32
│   │   │   └── i64
│   │   │
│   │   ├── Enums
│   │   │   ├── RedisType
│   │   │   ├── ErrorCode
│   │   │   └── ClientState
│   │   │
│   │   └── Utility Macros
│   │       ├── MIN()
│   │       ├── MAX()
│   │       ├── ARRAY_SIZE()
│   │       ├── ALIGN_UP()
│   │       ├── UNUSED()
│   │       └── container_of()
│   │
│   ├── allocator.h                              (~170 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   └── stddef.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── Arena
│   │   │   ├── uint8_t *memory
│   │   │   ├── size_t capacity
│   │   │   ├── size_t offset
│   │   │   └── size_t alignment
│   │   │
│   │   ├── FreeBlock
│   │   │   ├── size_t size
│   │   │   └── FreeBlock *nextv 
│   │   │
│   │   ├── PoolAllocator
│   │   │   ├── void *memory
│   │   │   ├── FreeBlock *free_list
│   │   │   ├── size_t object_size
│   │   │   ├── size_t object_count
│   │   │   └── size_t alignment
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── arena_create()
│   │   │   Return:
│   │   │       Arena *
│   │   │   Arguments:
│   │   │       size_t capacity
│   │   │
│   │   ├── arena_alloc()
│   │   │   Return:
│   │   │       void *
│   │   │   Arguments:
│   │   │       Arena *arena
│   │   │       size_t size
│   │   │       size_t alignment
│   │   │
│   │   ├── arena_reset()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       Arena *arena
│   │   │
│   │   ├── arena_destroy()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       Arena *arena
│   │   │
│   │   ├── pool_create()
│   │   │   Return:
│   │   │       PoolAllocator *
│   │   │   Arguments:
│   │   │       size_t object_size
│   │   │       size_t object_count
│   │   │
│   │   ├── pool_alloc()
│   │   │   Return:
│   │   │       void *
│   │   │   Arguments:
│   │   │       PoolAllocator *pool
│   │   │
│   │   ├── pool_free()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       PoolAllocator *pool
│   │   │       void *ptr
│   │   │
│   │   └── pool_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           PoolAllocator *pool
│   │
│   ├── hash.h                                   (~165 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   └── allocator.h
│   │   │
│   │   ├── Enum
│   │   │   └── EntryState
│   │   │       ├── EMPTY
│   │   │       ├── OCCUPIED
│   │   │       └── TOMBSTONE
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── HashEntry
│   │   │   ├── char *key
│   │   │   ├── void *value
│   │   │   ├── uint64_t hash
│   │   │   └── EntryState state
│   │   │
│   │   ├── HashTable
│   │   │   ├── HashEntry *entries
│   │   │   ├── size_t capacity
│   │   │   ├── size_t size
│   │   │   ├── size_t tombstones
│   │   │   └── float load_factor
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── hash_create()
│   │   │   Return:
│   │   │       HashTable *
│   │   │   Arguments:
│   │   │       size_t capacity
│   │   │
│   │   ├── hash_insert()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │       void *value
│   │   │
│   │   ├── hash_find()
│   │   │   Return:
│   │   │       void *
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │
│   │   ├── hash_remove()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │
│   │   ├── hash_resize()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       size_t new_capacity
│   │   │
│   │   └── hash_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           HashTable *table
│   │
│   ├── list.h                                   (~130 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   └── common.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── ListNode
│   │   │   ├── ListNode *prev
│   │   │   ├── ListNode *next
│   │   │   └── void *data
│   │   │
│   │   ├── List
│   │   │   ├── ListNode head
│   │   │   ├── ListNode tail
│   │   │   └── size_t size
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── list_init()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       List *list
│   │   │
│   │   ├── list_push_front()
│   │   │   Return:
│   │   │       ListNode *
│   │   │   Arguments:
│   │   │       List *list
│   │   │       void *data
│   │   │
│   │   ├── list_push_back()
│   │   ├── list_remove()
│   │   ├── list_move_front()
│   │   ├── list_front()
│   │   ├── list_back()
│   │   ├── list_empty()
│   │   └── list_clear()
│
└── FIRST PART END ^voubkFBt

├── include/                                      (continued)
│   │
│   ├── skiplist.h                                (~180 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── stdlib.h
│   │   │   └── math.h
│   │   │
│   │   ├── Defines
│   │   │   ├── SKIPLIST_MAX_LEVEL
│   │   │   └── SKIPLIST_P
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── SkipNode
│   │   │   ├── char *member
│   │   │   ├── double score
│   │   │   ├── SkipNode *forward[SKIPLIST_MAX_LEVEL]
│   │   │   ├── SkipNode *backward
│   │   │   └── int level
│   │   │
│   │   ├── SkipList
│   │   │   ├── SkipNode *header
│   │   │   ├── SkipNode *tail
│   │   │   ├── int level
│   │   │   └── size_t length
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── skiplist_create()
│   │   │   Return:
│   │   │       SkipList *
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── skiplist_insert()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_delete()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_search()
│   │   │   Return:
│   │   │       SkipNode *
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_range()
│   │   │   Return:
│   │   │       size_t
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double min
│   │   │       double max
│   │   │       SkipNode **result
│   │   │
│   │   └── skiplist_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           SkipList *list
│   │
│   ├── object.h                                  (~170 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── list.h
│   │   │   ├── hash.h
│   │   │   └── skiplist.h
│   │   │
│   │   ├── Enum
│   │   │   └── RedisObjectType
│   │   │       ├── OBJ_STRING
│   │   │       ├── OBJ_LIST
│   │   │       ├── OBJ_HASH
│   │   │       ├── OBJ_SET
│   │   │       └── OBJ_ZSET
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── RedisObject
│   │   │   ├── RedisObjectType type
│   │   │   ├── void *value
│   │   │   ├── uint64_t expire_at
│   │   │   ├── uint32_t refcount
│   │   │   └── ListNode *lru_node
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── object_create_string()
│   │   │   Return:
│   │   │       RedisObject *
│   │   │   Arguments:
│   │   │       const char *value
│   │   │
│   │   ├── object_create_list()
│   │   │   Return:
│   │   │       RedisObject *
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── object_create_hash()
│   │   ├── object_create_set()
│   │   ├── object_create_zset()
│   │   ├── object_retain()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       RedisObject *obj
│   │   │
│   │   ├── object_release()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       RedisObject *obj
│   │   │
│   │   └── object_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           RedisObject *obj
│   │
│   ├── database.h                                (~190 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── hash.h
│   │   │   ├── list.h
│   │   │   ├── object.h
│   │   │   └── allocator.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── Database
│   │   │   ├── HashTable *dict
│   │   │   ├── List lru
│   │   │   ├── size_t max_memory
│   │   │   ├── size_t used_memory
│   │   │   ├── Arena *arena
│   │   │   └── uint64_t key_count
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── db_create()
│   │   │   Return:
│   │   │       Database *
│   │   │   Arguments:
│   │   │       size_t max_memory
│   │   │
│   │   ├── db_set()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       Database *db
│   │   │       const char *key
│   │   │       RedisObject *obj
│   │   │
│   │   ├── db_get()
│   │   │   Return:
│   │   │       RedisObject *
│   │   │   Arguments:
│   │   │       Database *db
│   │   │       const char *key
│   │   │
│   │   ├── db_delete()
│   │   ├── db_exists()
│   │   ├── db_expire()
│   │   ├── db_touch_lru()
│   │   ├── db_evict_lru()
│   │   ├── db_cleanup_expired()
│   │   └── db_destroy()
│   │
│   ├── protocol.h                                (~150 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   └── database.h
│   │   │
│   │   ├── Enum
│   │   │   └── RespState
│   │   │       ├── RESP_START
│   │   │       ├── RESP_ARRAY
│   │   │       ├── RESP_BULK
│   │   │       ├── RESP_INLINE
│   │   │       ├── RESP_INTEGER
│   │   │       └── RESP_DONE
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── RespParser
│   │   │   ├── RespState state
│   │   │   ├── char *buffer
│   │   │   ├── size_t length
│   │   │   ├── size_t offset
│   │   │   ├── int argc
│   │   │   └── char **argv
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── parser_init()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       RespParser *parser
│   │   │
│   │   ├── parser_feed()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       RespParser *parser
│   │   │       const char *data
│   │   │       size_t size
│   │   │
│   │   ├── parser_reset()
│   │   ├── parser_complete()
│   │   ├── parser_error()
│   │   └── parser_destroy()
│   │
│   └── commands.h                                (~160 LOC)
│       │
│       ├── Libraries
│       │   ├── common.h
│       │   ├── database.h
│       │   ├── protocol.h
│       │   └── object.h
│       │
│       ├── Struct
│       │
│       ├── Command
│       │   ├── const char *name
│       │   ├── int min_args
│       │   ├── int max_args
│       │   └── int (*handler)(Client *, int, char **)
│       │
│       ├── Functions
│       │
│       ├── command_lookup()
│       │   Return:
│       │       Command *
│       │   Arguments:
│       │       const char *name
│       │
│       ├── command_execute()
│       │   Return:
│       │       int
│       │   Arguments:
│       │       Client *client
│       │       int argc
│       │       char **argv
│       │
│       ├── register_commands()
│       └── unregister_commands()
│
└── PART 2 END ^kl1gl7lG

├── src/                                              (~3,430 LOC)
│
├── main.c                                            (~120 LOC)
│   │
│   ├── Libraries
│   │   ├── common.h
│   │   ├── server.h
│   │   ├── database.h
│   │   ├── persistence.h
│   │   ├── command_registry.h
│   │   ├── network.h
│   │   └── signal.h
│   │
│   ├── Global Variables
│   │   └── Server *server
│   │
│   ├── Functions
│   │
│   ├── int main()
│   │   Return:
│   │       int
│   │   Arguments:
│   │       int argc
│   │       char *argv[]
│   │
│   │   Contains
│   │       ├── Parse command line
│   │       ├── Load configuration
│   │       ├── Initialize allocator
│   │       ├── Initialize database
│   │       ├── Register commands
│   │       ├── Load AOF/RDB
│   │       ├── Start server
│   │       ├── Run event loop
│   │       └── Cleanup
│   │
│   ├── server_shutdown()
│   │   Return:
│   │       void
│   │   Arguments:
│   │       void
│   │
│   │   Contains
│   │       ├── Save database
│   │       ├── Close sockets
│   │       ├── Free memory
│   │       └── Exit
│   │
│   └── signal_handler()
│       Return:
│           void
│       Arguments:
│           int signal
│
├── server/
│   │                                               (~790 LOC)
│   │
│   ├── server.h                                   (~170 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── database.h
│   │   │   ├── network.h
│   │   │   ├── protocol.h
│   │   │   └── persistence.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── Server
│   │   │   ├── int listen_fd
│   │   │   ├── int epoll_fd
│   │   │   ├── Database *db
│   │   │   ├── Client **clients
│   │   │   ├── size_t client_count
│   │   │   ├── size_t max_clients
│   │   │   ├── bool running
│   │   │   ├── uint16_t port
│   │   │   ├── Arena *command_arena
│   │   │   ├── time_t last_save
│   │   │   └── Config config
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── server_create()
│   │   │   Return:
│   │   │       Server *
│   │   │   Arguments:
│   │   │       uint16_t port
│   │   │
│   │   ├── server_start()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       Server *server
│   │   │
│   │   ├── server_stop()
│   │   ├── server_destroy()
│   │   ├── server_tick()
│   │   └── server_accept_clients()
│   │
│   ├── server.c                                   (~620 LOC)
│       │
│       ├── Libraries
│       │   ├── server.h
│       │   ├── network.h
│       │   ├── protocol.h
│       │   ├── command_registry.h
│       │   ├── persistence.h
│       │   └── time.h
│       │
│       ├── Static Variables
│       │   ├── event buffer
│       │   ├── timer values
│       │   └── statistics
│       │
│       ├── Functions
│       │
│       ├── server_create()
│       │   Contains
│       │       ├── Allocate server
│       │       ├── Initialize database
│       │       ├── Initialize arenas
│       │       ├── Create listening socket
│       │       ├── Create epoll instance
│       │       └── Initialize client table
│       │
│       ├── server_start()
│       │   Contains
│       │       ├── Bind socket
│       │       ├── Listen
│       │       ├── Register epoll
│       │       ├── Infinite event loop
│       │       ├── Accept clients
│       │       ├── Read requests
│       │       ├── Execute commands
│       │       ├── Send replies
│       │       ├── Cleanup expired keys
│       │       ├── LRU eviction
│       │       └── Background persistence checks
│       │
│       ├── server_stop()
│       ├── server_destroy()
│       ├── server_tick()
│       ├── handle_client()
│       ├── disconnect_client()
│       ├── expire_keys()
│       ├── perform_lru_eviction()
│       ├── background_save()
│       └── statistics_update()
│
├── network/
│   │                                               (~900 LOC)
│   │
│   ├── network.h                                  (~170 LOC)
│   │
│   │   Libraries
│   │       common.h
│   │       protocol.h
│   │
│   │   Struct
│   │
│   │   Client
│   │       int socket
│   │       sockaddr_in address
│   │       RespParser parser
│   │       char recv_buffer[8192]
│   │       size_t recv_used
│   │       char send_buffer[8192]
│   │       size_t send_used
│   │       bool authenticated
│   │       bool subscribed
│   │       time_t last_activity
│   │
│   │   Functions
│   │
│   │   network_init()
│   │       Return:
│   │           bool
│   │       Arguments:
│   │           void
│   │
│   │   create_server_socket()
│   │       Return:
│   │           int
│   │       Arguments:
│   │           uint16_t port
│   │
│   │   accept_client()
│   │   close_client()
│   │   recv_data()
│   │   send_data()
│   │   make_nonblocking()
│   │   add_epoll()
│   │   remove_epoll()
│   │
│   ├── socket.c                                   (~300 LOC)
│   │
│   │   Contains
│   │       socket()
│   │       bind()
│   │       listen()
│   │       accept()
│   │       setsockopt()
│   │       SO_REUSEADDR
│   │       fcntl()/ioctlsocket()
│   │       TCP initialization
│   │
│   ├── epoll.c                                    (~260 LOC)
│   │
│   │   Contains
│   │       epoll_create()
│   │       epoll_ctl()
│   │       epoll_wait()
│   │       event dispatch
│   │       edge-trigger logic
│   │       read until EAGAIN
│   │
│   └── client.c                                   (~170 LOC)
│       │
│       Contains
│           client_create()
│           client_destroy()
│           client_reset_parser()
│           client_flush_output()
│           client_disconnect()
│
└── PART 3 END ^UvfGYGsy

├── protocol/                                              (~700 LOC)
│   │
│   ├── protocol.h                                         (~150 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── network.h
│   │   │   ├── commands.h
│   │   │   └── database.h
│   │   │
│   │   ├── Enum
│   │   │
│   │   ├── RespType
│   │   │   ├── RESP_SIMPLE_STRING
│   │   │   ├── RESP_ERROR
│   │   │   ├── RESP_INTEGER
│   │   │   ├── RESP_BULK_STRING
│   │   │   ├── RESP_ARRAY
│   │   │   ├── RESP_NULL
│   │   │   └── RESP_INCOMPLETE
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── RespCommand
│   │   │   ├── int argc
│   │   │   ├── char **argv
│   │   │   ├── size_t command_length
│   │   │   └── bool valid
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── resp_parse()
│   │   │   Return:
│   │   │       int
│   │   │   Arguments:
│   │   │       Client *client
│   │   │
│   │   ├── resp_reset()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       RespParser *parser
│   │   │
│   │   ├── resp_free_command()
│   │   ├── resp_encode_simple_string()
│   │   ├── resp_encode_error()
│   │   ├── resp_encode_integer()
│   │   ├── resp_encode_bulk()
│   │   ├── resp_encode_array()
│   │   └── resp_encode_null()
│   │
│   ├── parser.c                                         (~370 LOC)
│   │
│   │   Libraries
│   │       protocol.h
│   │       allocator.h
│   │       string.h
│   │       ctype.h
│   │
│   │   Static Functions
│   │       parse_array()
│   │       parse_bulk_string()
│   │       parse_integer()
│   │       parse_inline()
│   │       parse_simple_string()
│   │       parse_error()
│   │       read_line()
│   │       read_length()
│   │
│   │   Public Functions
│   │       resp_parse()
│   │       resp_reset()
│   │       resp_free_command()
│   │
│   └── encoder.c                                        (~180 LOC)
│       │
│       Libraries
│           protocol.h
│           stdio.h
│
│       Functions
│           resp_encode_simple_string()
│           resp_encode_error()
│           resp_encode_integer()
│           resp_encode_bulk()
│           resp_encode_array()
│           resp_encode_null()
│
├── database/                                             (~760 LOC)
│   │
│   ├── database.c                                       (~310 LOC)
│   │
│   │   Libraries
│   │       database.h
│   │       object.h
│   │       hash.h
│   │       list.h
│   │       allocator.h
│   │
│   │   Static Functions
│   │       remove_expired()
│   │       update_memory_usage()
│   │       rehash_if_needed()
│   │
│   │   Public Functions
│   │       db_create()
│   │       db_set()
│   │       db_get()
│   │       db_delete()
│   │       db_exists()
│   │       db_expire()
│   │       db_cleanup_expired()
│   │       db_destroy()
│   │
│   ├── object.c                                         (~220 LOC)
│   │
│   │   Libraries
│   │       object.h
│   │       allocator.h
│   │
│   │   Functions
│   │       object_create_string()
│   │       object_create_list()
│   │       object_create_hash()
│   │       object_create_set()
│   │       object_create_zset()
│   │       object_retain()
│   │       object_release()
│   │       object_destroy()
│   │
│   └── expire.c                                         (~230 LOC)
│       │
│       Libraries
│           database.h
│           time.h
│
│       Functions
│           db_expire()
│           db_cleanup_expired()
│           ttl_remaining()
│           current_monotonic_time()
│           delete_if_expired()
│
├── datastructures/                                      (~980 LOC)
│   │
│   ├── hash_table.c                                    (~350 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   └── hash.h
│   │   │
│   │   ├── Static Functions
│   │   │
│   │   ├── fnv1a_hash()
│   │   │   Return:
│   │   │       u64
│   │   │   Arguments:
│   │   │       const char *key
│   │   │
│   │   ├── djb2_hash()
│   │   │   Return:
│   │   │       u64
│   │   │   Arguments:
│   │   │       const char *key
│   │   │
│   │   ├── probe_next()
│   │   │   Return:
│   │   │       size_t
│   │   │   Arguments:
│   │   │       size_t index
│   │   │       size_t capacity
│   │   │
│   │   ├── find_slot()
│   │   │   Return:
│   │   │       HashEntry *
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │       u64 hash
│   │   │
│   │   ├── rehash_table()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       size_t new_capacity
│   │   │
│   │   ├── Public Functions
│   │   │
│   │   ├── hash_create()
│   │   │   Return:
│   │   │       HashTable *
│   │   │   Arguments:
│   │   │       size_t capacity
│   │   │
│   │   ├── hash_insert()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │       void *value
│   │   │
│   │   ├── hash_find()
│   │   │   Return:
│   │   │       void *
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │
│   │   ├── hash_remove()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       const char *key
│   │   │
│   │   ├── hash_resize()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       HashTable *table
│   │   │       size_t new_capacity
│   │   │
│   │   └── hash_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           HashTable *table
│   │
│   ├── linked_list.c                                   (~180 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   └── list.h
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── list_init()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       List *list
│   │   │
│   │   ├── list_push_front()
│   │   │   Return:
│   │   │       ListNode *
│   │   │   Arguments:
│   │   │       List *list
│   │   │       void *data
│   │   │
│   │   ├── list_push_back()
│   │   │   Return:
│   │   │       ListNode *
│   │   │   Arguments:
│   │   │       List *list
│   │   │       void *data
│   │   │
│   │   ├── list_remove()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       List *list
│   │   │       ListNode *node
│   │   │
│   │   ├── list_move_front()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       List *list
│   │   │       ListNode *node
│   │   │
│   │   ├── list_front()
│   │   │   Return:
│   │   │       ListNode *
│   │   │   Arguments:
│   │   │       List *list
│   │   │
│   │   ├── list_back()
│   │   │   Return:
│   │   │       ListNode *
│   │   │   Arguments:
│   │   │       List *list
│   │   │
│   │   └── list_clear()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           List *list
│   │
│   ├── skiplist.c                                      (~290 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── skiplist.h
│   │   │   └── stdlib.h
│   │   │
│   │   ├── Static Functions
│   │   │
│   │   ├── random_level()
│   │   │   Return:
│   │   │       int
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── create_node()
│   │   │   Return:
│   │   │       SkipNode *
│   │   │   Arguments:
│   │   │       double score
│   │   │       const char *member
│   │   │       int level
│   │   │
│   │   ├── Public Functions
│   │   │
│   │   ├── skiplist_create()
│   │   │   Return:
│   │   │       SkipList *
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── skiplist_insert()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_delete()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_search()
│   │   │   Return:
│   │   │       SkipNode *
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double score
│   │   │       const char *member
│   │   │
│   │   ├── skiplist_range()
│   │   │   Return:
│   │   │       size_t
│   │   │   Arguments:
│   │   │       SkipList *list
│   │   │       double min
│   │   │       double max
│   │   │       SkipNode **result
│   │   │
│   │   └── skiplist_destroy()
│   │       Return:
│   │           void
│   │       Arguments:
│   │           SkipList *list
│   │
│   └── lru.c                                           (~160 LOC)
│       │
│       ├── Libraries
│       │   ├── database.h
│       │   └── list.h
│       │
│       ├── Functions
│       │
│       ├── lru_touch()
│       │   Return:
│       │       void
│       │   Arguments:
│       │       Database *db
│       │       RedisObject *object
│       │
│       ├── lru_insert()
│       │   Return:
│       │       void
│       │   Arguments:
│       │       Database *db
│       │       RedisObject *object
│       │
│       ├── lru_remove()
│       │   Return:
│       │       void
│       │   Arguments:
│       │       Database *db
│       │       RedisObject *object
│       │
│       ├── lru_evict()
│       │   Return:
│       │       RedisObject *
│       │   Arguments:
│       │       Database *db
│       │
│       └── lru_oldest()
│           Return:
│               RedisObject *
│           Arguments:
│               Database *db
│
└── PART 4 END ^NSF7JVk9

├── commands/                                              (~1,120 LOC)
│   │
│   ├── command_registry.h                                 (~170 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── commands.h
│   │   │   ├── network.h
│   │   │   └── database.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── CommandEntry
│   │   │   ├── const char *name
│   │   │   ├── int min_args
│   │   │   ├── int max_args
│   │   │   ├── int (*handler)(Client *, int, char **)
│   │   │   ├── bool write_command
│   │   │   ├── bool pubsub_command
│   │   │   └── bool admin_command
│   │   │
│   │   ├── Global
│   │   │   └── CommandEntry command_table[]
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── register_commands()
│   │   │   Return:
│   │   │       void
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── command_lookup()
│   │   │   Return:
│   │   │       CommandEntry *
│   │   │   Arguments:
│   │   │       const char *name
│   │   │
│   │   ├── command_execute()
│   │   │   Return:
│   │   │       int
│   │   │   Arguments:
│   │   │       Client *client
│   │   │       int argc
│   │   │       char **argv
│   │   │
│   │   └── unregister_commands()
│   │
│   ├── command_registry.c                               (~160 LOC)
│   │
│   │   Libraries
│   │       command_registry.h
│   │       string.h
│   │
│   │   Static Functions
│   │       register_string_commands()
│   │       register_list_commands()
│   │       register_hash_commands()
│   │       register_set_commands()
│   │       register_zset_commands()
│   │       register_pubsub_commands()
│   │
│   │   Public Functions
│   │       register_commands()
│   │       command_lookup()
│   │       command_execute()
│   │       unregister_commands()
│   │
│   ├── string_commands.c                               (~180 LOC)
│   │
│   │   Libraries
│   │       database.h
│   │       object.h
│   │       protocol.h
│   │
│   │   Functions
│   │
│   │   cmd_set()
│   │       Return:
│   │           int
│   │       Arguments:
│   │           Client *client
│   │           int argc
│   │           char **argv
│   │
│   │   cmd_get()
│   │       Return:
│   │           int
│   │       Arguments:
│   │           Client *client
│   │           int argc
│   │           char **argv
│   │
│   │   cmd_append()
│   │   cmd_strlen()
│   │   cmd_exists()
│   │   cmd_del()
│   │   cmd_expire()
│   │   cmd_ttl()
│   │
│   ├── list_commands.c                                 (~170 LOC)
│   │
│   │   Functions
│   │       cmd_lpush()
│   │       cmd_rpush()
│   │       cmd_lpop()
│   │       cmd_rpop()
│   │       cmd_llen()
│   │       cmd_lrange()
│   │
│   ├── hash_commands.c                                 (~150 LOC)
│   │
│   │   Functions
│   │       cmd_hset()
│   │       cmd_hget()
│   │       cmd_hdel()
│   │       cmd_hexists()
│   │       cmd_hlen()
│   │
│   ├── set_commands.c                                  (~150 LOC)
│   │
│   │   Functions
│   │       cmd_sadd()
│   │       cmd_srem()
│   │       cmd_sismember()
│   │       cmd_smembers()
│   │       cmd_scard()
│   │
│   ├── zset_commands.c                                 (~180 LOC)
│   │
│   │   Functions
│   │       cmd_zadd()
│   │       cmd_zrem()
│   │       cmd_zscore()
│   │       cmd_zrange()
│   │       cmd_zrank()
│   │       cmd_zcard()
│   │
│   └── pubsub_commands.c                               (~160 LOC)
│       │
│       Functions
│           cmd_subscribe()
│           cmd_unsubscribe()
│           cmd_publish()
│           cmd_psubscribe()
│           cmd_punsubscribe()
│
├── persistence/                                        (~760 LOC)
│   │
│   ├── persistence.h                                   (~180 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── database.h
│   │   │   └── object.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── AOFContext
│   │   │   ├── FILE *file
│   │   │   ├── char filename[260]
│   │   │   ├── bool enabled
│   │   │   └── size_t bytes_written
│   │   │
│   │   ├── RDBContext
│   │   │   ├── FILE *file
│   │   │   ├── char filename[260]
│   │   │   ├── uint64_t snapshot_time
│   │   │   └── bool saving
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── persistence_init()
│   │   ├── persistence_shutdown()
│   │   ├── aof_append()
│   │   ├── aof_rewrite()
│   │   ├── aof_load()
│   │   ├── rdb_save()
│   │   ├── rdb_load()
│   │   └── background_save()
│   │
│   ├── aof.c                                           (~260 LOC)
│   │
│   │   Libraries
│   │       persistence.h
│   │       protocol.h
│   │       stdio.h
│   │
│   │   Contains
│   │       Open append file
│   │       Write every write command
│   │       Flush
│   │       Recover database
│   │       Rewrite AOF
│   │
│   ├── rdb.c                                           (~340 LOC)
│   │
│   │   Libraries
│   │       persistence.h
│   │       database.h
│   │
│   │   Contains
│   │       Binary serializer
│   │       Binary loader
│   │       Save strings
│   │       Save hashes
│   │       Save lists
│   │       Save sets
│   │       Save zsets
│   │       Fork background save
│   │
│   └── snapshot.c                                      (~160 LOC)
│       │
│       Functions
│           snapshot_begin()
│           snapshot_finish()
│           snapshot_write_object()
│           snapshot_restore_object()
│
├── memory/                                             (~520 LOC)
│   │
│   ├── arena.c                                         (~170 LOC)
│   │
│   │   Functions
│   │       arena_create()
│   │       arena_alloc()
│   │       arena_reset()
│   │       arena_destroy()
│   │
│   ├── pool.c                                          (~180 LOC)
│   │
│   │   Functions
│   │       pool_create()
│   │       pool_alloc()
│   │       pool_free()
│   │       pool_destroy()
│   │
│   └── memory_utils.c                                  (~170 LOC)
│       │
│       Functions
│           align_pointer()
│           checked_malloc()
│           checked_realloc()
│           checked_free()
│           memory_statistics()
│
└── PART 5 END ^GRXYjLnt

├── pubsub/                                              (~330 LOC)
│   │
│   ├── pubsub.h                                         (~120 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   ├── network.h
│   │   │   ├── hash.h
│   │   │   └── list.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── Channel
│   │   │   ├── char *name
│   │   │   ├── List subscribers
│   │   │   └── size_t subscriber_count
│   │   │
│   │   ├── PubSub
│   │   │   ├── HashTable *channels
│   │   │   └── size_t total_channels
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── pubsub_create()
│   │   │   Return:
│   │   │       PubSub *
│   │   │   Arguments:
│   │   │       void
│   │   │
│   │   ├── pubsub_destroy()
│   │   ├── subscribe_client()
│   │   ├── unsubscribe_client()
│   │   ├── publish_message()
│   │   └── remove_client_from_all_channels()
│   │
│   └── pubsub.c                                         (~210 LOC)
│       │
│       Libraries
│           pubsub.h
│           protocol.h
│           string.h
│
│       Static Functions
│           create_channel()
│           destroy_channel()
│
│       Public Functions
│           pubsub_create()
│           pubsub_destroy()
│           subscribe_client()
│           unsubscribe_client()
│           publish_message()
│           remove_client_from_all_channels()
│
├── utils/                                               (~480 LOC)
│   │
│   ├── config.h                                         (~120 LOC)
│   │   │
│   │   ├── Libraries
│   │   │   ├── common.h
│   │   │   └── stdio.h
│   │   │
│   │   ├── Struct
│   │   │
│   │   ├── Config
│   │   │   ├── uint16_t port
│   │   │   ├── size_t max_memory
│   │   │   ├── bool append_only
│   │   │   ├── bool save_snapshots
│   │   │   ├── size_t arena_size
│   │   │   ├── size_t max_clients
│   │   │   ├── char aof_file[260]
│   │   │   ├── char rdb_file[260]
│   │   │   └── uint32_t save_interval
│   │   │
│   │   ├── Functions
│   │   │
│   │   ├── config_load()
│   │   │   Return:
│   │   │       bool
│   │   │   Arguments:
│   │   │       Config *config
│   │   │       const char *filename
│   │   │
│   │   ├── config_save()
│   │   ├── config_defaults()
│   │   └── config_validate()
│   │
│   ├── config.c                                         (~170 LOC)
│   │
│   │   Libraries
│   │       config.h
│   │       string.h
│   │
│   │   Contains
│   │       Read config file
│   │       Parse options
│   │       Validate values
│   │       Apply defaults
│   │
│   ├── logger.h                                         (~60 LOC)
│   │
│   │   Libraries
│   │       common.h
│   │
│   │   Enum
│   │       LogLevel
│   │           LOG_DEBUG
│   │           LOG_INFO
│   │           LOG_WARN
│   │           LOG_ERROR
│   │
│   │   Functions
│   │       log_message()
│   │       log_init()
│   │       log_shutdown()
│   │
│   ├── logger.c                                         (~130 LOC)
│   │
│   │   Libraries
│   │       logger.h
│   │       stdarg.h
│   │
│   │   Contains
│   │       Timestamp generation
│   │       Console logging
│   │       File logging
│   │       Log formatting
│   │
│   └── time_utils.c                                     (~120 LOC)
│       │
│       Libraries
│           common.h
│           time.h
│
│       Functions
│           monotonic_ms()
│           unix_timestamp()
│           sleep_ms()
│           elapsed_ms()
│
├── tests/                                               (~620 LOC)
│   │
│   ├── test_hash.c                                     (~110 LOC)
│   ├── test_skiplist.c                                 (~90 LOC)
│   ├── test_database.c                                 (~120 LOC)
│   ├── test_protocol.c                                 (~100 LOC)
│   ├── test_network.c                                  (~80 LOC)
│   ├── test_commands.c                                 (~120 LOC)
│
├── data/                                                (~0 LOC)
│   │
│   ├── dump.rdb
│   ├── appendonly.aof
│   └── redis.conf
│
├── docs/                                                (~150 LOC)
│   │
│   ├── protocol.md
│   ├── architecture.md
│   ├── memory.md
│   └── commands.md
│
├───────────────────────────────────────────────────────────────
│
│                 FINAL LINE COUNT
│
├───────────────────────────────────────────────────────────────
│
├── CMakeLists.txt ...............................     70
│
├── include/ .....................................  1,850
│
├── src/main.c ...................................    120
│
├── server/ ......................................    790
│
├── network/ .....................................    900
│
├── protocol/ ....................................    700
│
├── database/ ....................................    760
│
├── datastructures/ ...............................    980
│
├── commands/ ....................................  1,120
│
├── persistence/ .................................    760
│
├── memory/ ......................................    520
│
├── pubsub/ ......................................    330
│
├── utils/ .......................................    480
│
├── tests/ .......................................    620
│
├── docs/ ........................................    150
│
├── data/ ........................................      0
│
├───────────────────────────────────────────────────────────────
│
│ TOTAL PROJECT
│
│ ≈ 10,150 lines
│
├───────────────────────────────────────────────────────────────
│
│ NOTE
│
│ This architecture is considerably larger than the original
│ estimate (3,500–5,000 LOC). It represents a much more
│ industry-style educational Redis clone with separate modules,
│ cleaner layering, better maintainability, testing, logging,
│ configuration, and persistence organization.
│
│ A true 3,500–5,000 LOC implementation would merge many of
│ these modules together and implement fewer commands and
│ features.
└─────────────────────────────────────────────────────────────── ^E8uI6HUp

REDIS CLONE LEARNING ROADMAP
(Build these mini-projects/modules BEFORE the Redis Clone)

redis_clone_in_c
│
├── PHASE 1 — Foundation (Must Master First)
│   │
│   ├── Build:
│   │   └── include/
│   │
│   ├── Learn
│   │   ├── Header files
│   │   ├── Source file organization
│   │   ├── CMake
│   │   ├── Structs
│   │   ├── Enums
│   │   ├── typedef
│   │   ├── Macros
│   │   ├── const
│   │   ├── static
│   │   ├── extern
│   │   └── Project architecture
│   │
│   └── Mini Project
│       └── Small Utility Library
│
├── PHASE 2 — Memory Management
│   │
│   ├── Build:
│   │   └── memory/
│   │
│   ├── Learn
│   │   ├── malloc()
│   │   ├── calloc()
│   │   ├── realloc()
│   │   ├── free()
│   │   ├── Memory alignment
│   │   ├── Pointer arithmetic
│   │   ├── Arena allocator
│   │   ├── Pool allocator
│   │   ├── Free list
│   │   ├── Memory fragmentation
│   │   └── Memory debugging
│   │
│   └── Mini Project
│       └── Custom Memory Allocator
│
├── PHASE 3 — Core Data Structures
│   │
│   ├── Build:
│   │   └── datastructures/
│   │
│   ├── Learn
│   │   ├── Dynamic arrays
│   │   ├── Doubly linked list
│   │   ├── Sentinel nodes
│   │   ├── Hash functions
│   │   ├── Open addressing
│   │   ├── Rehashing
│   │   ├── Tombstones
│   │   ├── Skip List
│   │   ├── Big-O analysis
│   │   └── LRU Cache
│   │
│   └── Mini Projects
│       ├── Hash Table
│       ├── Skip List
│       └── LRU Cache
│
├── PHASE 4 — Database Engine
│   │
│   ├── Build:
│   │   └── database/
│   │
│   ├── Learn
│   │   ├── Key-Value stores
│   │   ├── Object abstraction
│   │   ├── Reference counting
│   │   ├── TTL
│   │   ├── Monotonic clock
│   │   ├── Memory limits
│   │   ├── Eviction
│   │   └── Object lifecycle
│   │
│   └── Mini Project
│       └── In-Memory Key-Value Store
│
├── PHASE 5 — Networking
│   │
│   ├── Build:
│   │   └── network/
│   │
│   ├── Learn
│   │   ├── TCP/IP
│   │   ├── socket()
│   │   ├── bind()
│   │   ├── listen()
│   │   ├── accept()
│   │   ├── recv()
│   │   ├── send()
│   │   ├── Non-blocking sockets
│   │   ├── SO_REUSEADDR
│   │   ├── fcntl()
│   │   └── Partial reads
│   │
│   └── Mini Project
│       └── Multi-client TCP Server
│
├── PHASE 6 — Event Driven Programming
│   │
│   ├── Build:
│   │   └── server/
│   │
│   ├── Learn
│   │   ├── epoll
│   │   ├── Event loop
│   │   ├── Client management
│   │   ├── Timers
│   │   ├── Event dispatching
│   │   ├── State machines
│   │   └── Single-threaded servers
│   │
│   └── Mini Project
│       └── epoll Chat Server
│
├── PHASE 7 — Protocol Parsing
│   │
│   ├── Build:
│   │   └── protocol/
│   │
│   ├── Learn
│   │   ├── RESP protocol
│   │   ├── Binary protocols
│   │   ├── Streaming parsers
│   │   ├── State machines
│   │   ├── Command parsing
│   │   ├── Serialization
│   │   └── Deserialization
│   │
│   └── Mini Project
│       └── RESP Parser
│
├── PHASE 8 — Command Engine
│   │
│   ├── Build:
│   │   └── commands/
│   │
│   ├── Learn
│   │   ├── Command dispatch
│   │   ├── Function pointers
│   │   ├── Command registry
│   │   ├── Validation
│   │   ├── Error handling
│   │   └── Command execution
│   │
│   └── Mini Project
│       └── CLI Command Dispatcher
│
├── PHASE 9 — Persistence
│   │
│   ├── Build:
│   │   └── persistence/
│   │
│   ├── Learn
│   │   ├── File I/O
│   │   ├── Binary serialization
│   │   ├── AOF
│   │   ├── RDB
│   │   ├── fork()
│   │   ├── Recovery
│   │   └── Durability
│   │
│   └── Mini Project
│       └── Database Snapshot System
│
├── PHASE 10 — Publish / Subscribe
│   │
│   ├── Build:
│   │   └── pubsub/
│   │
│   ├── Learn
│   │   ├── Pub/Sub architecture
│   │   ├── Channels
│   │   ├── Subscribers
│   │   ├── Broadcasting
│   │   └── Client groups
│   │
│   └── Mini Project
│       └── Publish-Subscribe Server
│
├── PHASE 11 — Utilities
│   │
│   ├── Build:
│   │   └── utils/
│   │
│   ├── Learn
│   │   ├── Configuration files
│   │   ├── Logging
│   │   ├── Time utilities
│   │   ├── Error reporting
│   │   └── Project utilities
│   │
│   └── Mini Project
│       └── Config + Logger Library
│
├── PHASE 12 — Integration
│   │
│   ├── Build
│   │   ├── main.c
│   │   └── Complete Redis Clone
│   │
│   ├── Learn
│   │   ├── System integration
│   │   ├── Module communication
│   │   ├── Startup sequence
│   │   ├── Shutdown sequence
│   │   ├── Debugging
│   │   ├── Testing
│   │   └── Performance optimization
│   │
│   └── Final Project
│       └── Redis Clone
│
└── Learning Order
    │
    ├── Foundation
    ├── Memory
    ├── Data Structures
    ├── Database
    ├── Networking
    ├── Event Loop
    ├── Protocol Parser
    ├── Command Engine
    ├── Persistence
    ├── Pub/Sub
    ├── Utilities
    └── Complete Redis Clone ^jmNpxAbu

RedisType

REDIS_STRING

REDIS_LIST

REDIS_HASH,

REDIS_SET,

REDIS_ZSET ^1Z2ANK0e

ErrorCode

ERR_OK = 0,

ERR_MEMORY,

ERR_NOT_FOUND,

ERR_EXISTS,

ERR_INVALID_ARGUMENT,

ERR_OVERFLOW,

ERR_IO,

ERR_NETWORK,

ERR_PROTOCOL,

ERR_UNKNOWN ^l5BYXkTN

ClientState

CLIENT_DISCONNECTED,

CLIENT_CONNECTING,

CLIENT_CONNECTED,

CLIENT_READING,

CLIENT_WRITING,

CLIENT_CLOSING ^iqk9lGIc

#define REDIS_VERSION "1.0.0"

// Default port on which the Redis server will listen
#define DEFAULT_PORT 6379

// Maximum number of characters allowed in a key
#define MAX_KEY_SIZE 512

// Maximum size of a value (1 MB)
#define MAX_VALUE_SIZE (1024 * 1024)

// Hash table load factor before resizing
#define HASH_LOAD_FACTOR 0.75f

// Maximum number of clients that can connect simultaneously
#define MAX_CLIENTS 1024

// Size of the receive buffer for incoming network data
#define RECV_BUFFER_SIZE 4096

// Size of the send buffer for outgoing network data
#define SEND_BUFFER_SIZE 4096

// Default size of the memory arena (1 MB)
#define ARENA_DEFAULT_SIZE (1024 * 1024)

// Size of the small inline buffer stored inside objects
#define INLINE_BUFFER_SIZE 64 ^Qm88Jgjd


 ^EPVT23pN

arena.c (Part 1)
├── arena_create()
│   ├── Section 1 — Function interface and dependencies
│   │   ├── Required headers for malloc(), free(), size_t
│   │   ├── Function signature: Arena * return type
│   │   ├── Why capacity uses size_t
│   │   └── Arena structure fields that must be initialized
│   ├── Section 2 — Arena object allocation
│   │   ├── Allocating the Arena structure with malloc()
│   │   ├── NULL check after allocation
│   │   ├── Why allocating the struct separately from its buffer
│   │   └── Guard-clause error handling
│   ├── Section 3 — Backing memory allocation
│   │   ├── Allocating the arena memory buffer
│   │   ├── Handling second-allocation failure
│   │   ├── Cleanup of previously allocated resources
│   │   └── Preventing memory leaks on partial failure
│   └── Section 4 — Initialization and return
│       ├── Initializing memory pointer
│       ├── Initializing capacity
│       ├── Initializing allocation offset
│       └── Returning a fully initialized Arena pointer

arena.c (Part 2)
├── arena_alloc()
│   ├── Section 1 — Function interface and validation
│   │   ├── Required headers for uintptr_t
│   │   ├── Purpose of Arena *, size, and alignment parameters
│   │   ├── Validating input pointers and sizes
│   │   └── Production checks for alignment validity
│   ├── Section 2 — Alignment calculation
│   │   ├── Converting pointers to uintptr_t
│   │   ├── Alignment formula: (ptr + align - 1) & ~(align - 1)
│   │   ├── Why alignment must be a power of two
│   │   └── Computing padding before allocation
│   ├── Section 3 — Capacity and overflow checks
│   │   ├── Calculating required space including padding
│   │   ├── Detecting arena exhaustion
│   │   ├── Preventing integer overflow during size calculations
│   │   └── Failure return convention
│   └── Section 4 — Completing the allocation
│       ├── Computing returned memory address
│       ├── Advancing the arena offset
│       ├── Returning aligned memory
│       └── Bump-pointer allocator behavior

arena.c (Part 3)
├── arena_reset()
│   ├── Section 1 — Function interface and safety
│   │   ├── Purpose of Arena * parameter
│   │   ├── NULL pointer handling
│   │   └── Why reset returns void
│   └── Section 2 — Resetting allocator state
│       ├── Resetting only the allocation offset
│       ├── Why allocated memory is not freed
│       ├── Constant-time reset operation
│       └── Reusing the arena after reset

arena.c (Part 4)
├── arena_destroy()
│   ├── Section 1 — Function interface and safety
│   │   ├── Purpose of Arena * parameter
│   │   ├── NULL pointer handling
│   │   └── Ownership rules for destruction
│   ├── Section 2 — Resource cleanup
│   │   ├── Freeing the backing memory buffer
│   │   ├── Freeing the Arena structure
│   │   ├── Correct free order
│   │   └── free(NULL) behavior and conventions
│   └── Section 3 — Production cleanup conventions
│       ├── Avoiding double-free bugs
│       ├── Pointer invalidation after destruction
│       └── Lifetime management responsibilities ^J9A8tHBG

hash_table.c

├── fnv1a_hash() (Part 1)
│
│   ├── Section 1: Purpose & Contract
│   │   ├── topic: what the function does
│   │   ├── topic: why const char *key is the only argument and how it is used
│   │   ├── topic: why u64 is returned and how the hash value is produced
│   │   └── topic: failure contract (NULL key, assumptions, caller responsibility)
│   │
│   ├── Section 2: Hash Initialization
│   │   ├── topic: choose FNV offset basis
│   │   ├── topic: initialize running hash value
│   │   └── topic: prepare to iterate through bytes
│   │
│   ├── Section 3: Byte Processing
│   │   ├── topic: read one byte at a time
│   │   ├── topic: XOR current byte into hash
│   │   ├── topic: multiply by FNV prime
│   │   └── topic: continue until string terminator
│   │
│   └── Section 4: Finish
│       ├── topic: produce final hash value
│       ├── topic: deterministic behavior for identical keys
│       └── topic: return result
│
├── djb2_hash() (Part 2)
│
│   ├── Section 1: Purpose & Contract
│   │   ├── topic: what the function does
│   │   ├── topic: why const char *key is required
│   │   ├── topic: why u64 is returned
│   │   └── topic: failure contract (NULL key, caller responsibility)
│   │
│   ├── Section 2: Hash Initialization
│   │   ├── topic: choose DJB2 initial constant
│   │   ├── topic: initialize running hash
│   │   └── topic: prepare string iteration
│   │
│   ├── Section 3: Byte Processing
│   │   ├── topic: read characters sequentially
│   │   ├── topic: multiply previous hash by 33
│   │   ├── topic: add current byte
│   │   └── topic: repeat until null terminator
│   │
│   └── Section 4: Finish
│       ├── topic: produce final hash
│       ├── topic: deterministic output
│       └── topic: return result
│
├── probe_next() (Part 3)
│
│   ├── Section 1: Purpose & Contract
│   │   ├── topic: what the function does
│   │   ├── topic: why index and capacity are needed
│   │   ├── topic: why size_t is returned
│   │   └── topic: failure contract (invalid capacity assumptions)
│   │
│   ├── Section 2: Next Probe Position
│   │   ├── topic: advance current index
│   │   ├── topic: wrap around table end
│   │   └── topic: ensure returned index stays inside capacity
│   │
│   └── Section 3: Finish
│       ├── topic: return next probe index
│
├── find_slot() (Part 4)
│
│   ├── Section 1: Purpose & Contract
│   │   ├── topic: what the function does
│   │   ├── topic: why table, key and precomputed hash are required
│   │   ├── topic: why HashEntry * is returned
│   │   └── topic: failure contract (NULL, table full, invalid arguments)
│   │
│   ├── Section 2: Starting Search
│   │   ├── topic: validate arguments
│   │   ├── topic: compute initial bucket index
│   │   ├── topic: prepare probing variables
│   │   └── topic: initialize first tombstone tracking (if used)
│   │
│   ├── Section 3: Probe Loop
│   │   ├── topic: inspect current slot
│   │   ├── topic: detect empty slot
│   │   ├── topic: detect occupied slot
│   │   ├── topic: compare stored hash
│   │   ├── topic: compare key contents
│   │   ├── topic: detect deleted/tombstone slot
│   │   ├── topic: remember first reusable tombstone
│   │   ├── topic: move to next probe location
│   │   └── topic: stop after full-table scan
│   │
│   └── Section 4: Result Selection
│       ├── topic: return matching entry
│       ├── topic: return reusable tombstone
│       ├── topic: return empty slot
│       └── topic: return NULL when no usable slot exists
│
└── rehash_table() (Part 5)
    │
    ├── Section 1: Purpose & Contract
    │   ├── topic: what the function does
    │   ├── topic: why table and new_capacity are required
    │   ├── topic: why bool is returned
    │   └── topic: failure contract (allocation failure, invalid capacity, caller responsibility)
    │
    ├── Section 2: Prepare New Table
    │   ├── topic: validate arguments
    │   ├── topic: allocate new entry array
    │   ├── topic: initialize all slots to empty
    │   └── topic: prepare temporary table metadata
    │
    ├── Section 3: Reinsert Existing Entries
    │   ├── topic: iterate over old table
    │   ├── topic: skip empty slots
    │   ├── topic: skip deleted/tombstone slots
    │   ├── topic: compute destination slot
    │   ├── topic: insert into new table
    │   ├── topic: preserve stored key/value
    │   └── topic: preserve element count
    │
    └── Section 4: Replace Old Storage
        ├── topic: free old entry array
        ├── topic: install new storage
        ├── topic: update capacity metadata
        ├── topic: keep table in consistent state on failure
        └── topic: return success or failure ^Hvuytv6V

hash_create() (Part 1)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what the function creates and initializes
│   ├── Topic: why capacity is needed and how it determines the initial table size
│   ├── Topic: why the function returns HashTable * and how that pointer is produced
│   └── Topic: failure contract (NULL on allocation failure, caller ownership, cleanup responsibility)
│
├── Section 2: Allocate & Validate
│   ├── Topic: validate requested capacity
│   ├── Topic: allocate HashTable structure
│   ├── Topic: initialize structure to a known safe state
│   └── Topic: allocate HashEntry array
│
├── Section 3: Initialize Table State
│   ├── Topic: initialize every entry to EMPTY state
│   ├── Topic: initialize key/value/hash fields
│   ├── Topic: initialize capacity, size and tombstone counters
│   └── Topic: initialize default load factor
│
└── Section 4: Failure Cleanup & Return
    ├── Topic: handle entry allocation failure
    ├── Topic: release partially allocated resources
    ├── Topic: return initialized table
    └── Topic: ownership after successful return


hash_insert() (Part 2)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what inserting into the hash table means
│   ├── Topic: why table, key and value are required
│   ├── Topic: why bool is returned and what true/false represent
│   └── Topic: failure contract (invalid arguments, allocation failure, resize failure)
│
├── Section 2: Validation & Resize Decision
│   ├── Topic: validate input pointers
│   ├── Topic: compute hash value
│   ├── Topic: calculate current load factor
│   ├── Topic: decide whether resizing is required
│   └── Topic: perform resize before insertion
│
├── Section 3: Locate Destination Slot
│   ├── Topic: compute initial bucket index
│   ├── Topic: probe through collisions
│   ├── Topic: reuse TOMBSTONE slots correctly
│   ├── Topic: detect existing key
│   └── Topic: distinguish insert versus update
│
└── Section 4: Store Entry & Finish
    ├── Topic: duplicate/store key ownership
    ├── Topic: store value pointer
    ├── Topic: cache hash value
    ├── Topic: update slot state
    ├── Topic: update size and tombstone counters
    └── Topic: return success or failure


hash_find() (Part 3)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what searching means
│   ├── Topic: why table and key are required
│   ├── Topic: why void * is returned
│   └── Topic: failure contract (NULL for invalid input or missing key)
│
├── Section 2: Prepare Search
│   ├── Topic: validate arguments
│   ├── Topic: compute hash
│   ├── Topic: compute starting bucket
│   └── Topic: prepare probing variables
│
├── Section 3: Probe & Compare
│   ├── Topic: examine current slot
│   ├── Topic: handle EMPTY slots
│   ├── Topic: skip TOMBSTONE slots
│   ├── Topic: compare cached hash
│   ├── Topic: compare key strings
│   └── Topic: continue probing after collisions
│
└── Section 4: Return Result
    ├── Topic: return associated value
    ├── Topic: return NULL when key is absent
    └── Topic: search termination conditions


hash_remove() (Part 4)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what removing an entry means
│   ├── Topic: why table and key are required
│   ├── Topic: why bool is returned
│   └── Topic: failure contract (invalid input or key not found)
│
├── Section 2: Locate Target Entry
│   ├── Topic: validate arguments
│   ├── Topic: compute hash
│   ├── Topic: probe to locate matching entry
│   └── Topic: verify exact key match
│
├── Section 3: Delete Entry
│   ├── Topic: release owned key memory
│   ├── Topic: preserve value ownership rules
│   ├── Topic: mark slot as TOMBSTONE
│   ├── Topic: clear entry fields safely
│   └── Topic: maintain probe-chain correctness
│
└── Section 4: Update Metadata & Return
    ├── Topic: decrement size
    ├── Topic: increment tombstone counter
    ├── Topic: decide whether cleanup/rehash is needed
    └── Topic: return success or failure


hash_resize() (Part 5)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what resizing accomplishes
│   ├── Topic: why table and new_capacity are required
│   ├── Topic: why bool is returned
│   └── Topic: failure contract (original table remains valid on failure)
│
├── Section 2: Prepare New Table
│   ├── Topic: validate requested capacity
│   ├── Topic: allocate new entry array
│   ├── Topic: initialize every slot
│   └── Topic: prepare temporary metadata
│
├── Section 3: Rehash Existing Entries
│   ├── Topic: iterate over old table
│   ├── Topic: skip EMPTY slots
│   ├── Topic: skip TOMBSTONE slots
│   ├── Topic: recompute destination index
│   ├── Topic: insert into new table using probing
│   └── Topic: preserve existing key/value ownership
│
└── Section 4: Commit Resize
    ├── Topic: replace old entry array
    ├── Topic: free old storage
    ├── Topic: update capacity and counters
    ├── Topic: preserve table consistency on failure
    └── Topic: return success or failure


hash_destroy() (Part 6)
│
├── Section 1: Purpose & Contract
│   ├── Topic: what resources must be released
│   ├── Topic: why only the table pointer is required
│   ├── Topic: why return type is void
│   └── Topic: ownership contract (what this function frees and what it does not)
│
├── Section 2: Validate & Walk Table
│   ├── Topic: handle NULL table safely
│   ├── Topic: iterate through every slot
│   ├── Topic: identify valid OCCUPIED entries
│   └── Topic: ignore EMPTY and TOMBSTONE entries
│
├── Section 3: Release Resources
│   ├── Topic: free owned key strings
│   ├── Topic: decide whether values should be freed
│   ├── Topic: free entry array
│   └── Topic: free HashTable structure
│
└── Section 4: Final Cleanup
    ├── Topic: cleanup order
    ├── Topic: avoid memory leaks
    ├── Topic: avoid double-free situations
    └── Topic: caller responsibilities after destruction ^k6eX8mk2

pool.c (Part 1)
├── pool_create()
│   ├── Section 1: Purpose & Allocation Contract
│   │   ├── what the pool allocator creates and owns
│   │   ├── object_size vs object_count and total memory calculation
│   │   ├── why PoolAllocator and pool memory are allocated separately
│   │   └── ownership and cleanup responsibilities on success/failure
│   ├── Section 2: Memory Allocation Strategy
│   │   ├── allocating the PoolAllocator structure
│   │   ├── allocating one contiguous memory block for all objects
│   │   ├── integer overflow when computing total pool size
│   │   └── failure handling with cleanup of partially allocated resources
│   ├── Section 3: Free List Construction
│   │   ├── dividing contiguous memory into fixed-size blocks
│   │   ├── pointer arithmetic to locate each object
│   │   ├── storing FreeBlock metadata inside each free object
│   │   └── linking every block into the intrusive free list
│   └── Section 4: Initializing Pool State
│       ├── initializing allocator fields
│       ├── setting the initial free_list head
│       ├── alignment considerations for object storage
│       └── final return contract

pool.c (Part 2)
├── pool_alloc()
│   ├── Section 1: Allocation Contract
│   │   ├── purpose of allocating one object
│   │   ├── empty pool detection
│   │   ├── return value contract
│   │   └── ownership of returned object
│   ├── Section 2: Removing a Block from the Free List
│   │   ├── taking the first free block
│   │   ├── advancing the free_list head
│   │   ├── why allocation is O(1)
│   │   └── preserving remaining free blocks
│   └── Section 3: Returning the Object
│       ├── converting FreeBlock pointer into user object pointer
│       ├── whether object memory should be initialized
│       └── production conventions for allocator behavior

pool.c (Part 3)
├── pool_free()
│   ├── Section 1: Free Contract
│   │   ├── purpose of returning an object to the pool
│   │   ├── expected validity of the supplied pointer
│   │   ├── handling NULL pointers
│   │   └── ownership after freeing
│   ├── Section 2: Rebuilding the Free List
│   │   ├── treating the returned object as a FreeBlock
│   │   ├── inserting at the front of the free list
│   │   ├── updating next pointers correctly
│   │   └── why deallocation is O(1)
│   └── Section 3: Safety Considerations
│       ├── double-free risks
│       ├── freeing pointers not owned by the pool
│       ├── production debugging techniques
│       └── allocator assumptions versus runtime validation

pool.c (Part 4)
├── pool_destroy()
│   ├── Section 1: Destruction Contract
│   │   ├── purpose of destroying the pool
│   │   ├── handling NULL allocator pointers
│   │   ├── ownership of managed memory
│   │   └── destruction guarantees
│   └── Section 2: Releasing Resources
│       ├── freeing the pool memory block
│       ├── freeing the PoolAllocator structure
│       ├── correct destruction order
│       └── avoiding resource leaks and invalid access ^5TbTUvKq

%%
## Drawing
```compressed-json
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
```
%%