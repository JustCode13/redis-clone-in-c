#ifndef COMMON_H          // Prevents this header file from being included more than once
#define COMMON_H

#include <stdint.h>       // Fixed-size integer types like uint8_t, int32_t
#include <stddef.h>       // Defines size_t, offsetof(), NULL
#include <stdbool.h>      // Adds the bool, true, and false keywords
#include <stdio.h>        // Input/output functions like printf(), scanf(), fopen()
#include <stdlib.h>       // Memory allocation, process control, conversions
#include <string.h>       // String and memory manipulation functions
#include <errno.h>        // Error codes set by system/library functions
#include <time.h>         // Time and date related functions
#include <limits.h>       // Integer limits like INT_MAX, CHAR_MAX
#include <assert.h>       // assert() for debugging
#include <stdalign.h>     // align_of() or _Alignof() for getting alignment

// Stores the current version of the Redis project
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
#define INLINE_BUFFER_SIZE 64



// Short name for an unsigned 8-bit integer
typedef uint8_t  u8;

// Short name for an unsigned 16-bit integer
typedef uint16_t u16;

// Short name for an unsigned 32-bit integer
typedef uint32_t u32;

// Short name for an unsigned 64-bit integer
typedef uint64_t u64;

// Short name for a signed 32-bit integer
typedef int32_t  i32;

// Short name for a signed 64-bit integer
typedef int64_t  i64;

// Short name for a signed 64-bit integer
typedef uintptr_t uptr_t;


// Represents the type of data stored in a Redis key
typedef enum {

    // Key stores a string value
    REDIS_STRING,

    // Key stores a list
    REDIS_LIST,

    // Key stores a hash table
    REDIS_HASH,

    // Key stores a set
    REDIS_SET,

    // Key stores a sorted set
    REDIS_ZSET

} RedisType;


// Represents the result of an operation or an error code
typedef enum {

    // Operation completed successfully
    ERR_OK = 0,

    // Memory allocation failed
    ERR_MEMORY,

    // Requested item was not found
    ERR_NOT_FOUND,

    // Item already exists
    ERR_EXISTS,

    // Invalid argument was passed to a function
    ERR_INVALID_ARGUMENT,

    // Integer or buffer overflow occurred
    ERR_OVERFLOW,

    // File or input/output error
    ERR_IO,

    // Network-related error
    ERR_NETWORK,

    // Invalid protocol or malformed data
    ERR_PROTOCOL,

    // Unknown or unexpected error
    ERR_UNKNOWN

} ErrorCode;


// Represents the current state of a client connection
typedef enum {

    // Client is not connected
    CLIENT_DISCONNECTED,

    // Client is trying to establish a connection
    CLIENT_CONNECTING,

    // Client is successfully connected
    CLIENT_CONNECTED,

    // Server is reading data from the client
    CLIENT_READING,

    // Server is sending data to the client
    CLIENT_WRITING,

    // Client connection is being closed
    CLIENT_CLOSING

} ClientState;


// Returns the smaller of two values
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Returns the larger of two values
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Returns the number of elements in a fixed-size array
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Rounds a value up to the nearest alignment boundary
#define ALIGN_UP(value, alignment) (((value) + ((alignment) - 1)) & ~((alignment) - 1))

// Marks a variable as intentionally unused to suppress compiler warnings
#define UNUSED(x) ((void)(x))


// Uses compiler-specific support when compiling with GCC or Clang
#if defined(__GNUC__) || defined(__clang__)

// Converts a pointer to a structure member back into a pointer to the containing structure
// Example: &person.age->Person *
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#else

// Generic version of container_of() for other compilers
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#endif

#endif   // End of include guard