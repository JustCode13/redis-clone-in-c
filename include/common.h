#ifndef COMMON_h
#define COMMON_h


#include <stdint.h> // get particular size int
#include <stddef.h> // to use size_t
#include <stdbool.h> // to get, use boolean, true and false
#include <errno.h> // so we can get errors
#include <time.h> // so we can work with time

#define REDIS_MAX_KEY_SIZE 256 // maximum size keys redis will store
#define REDIS_MAX_CLIENTS 10000 // maxium number of clients redis will allow
#define REDIS_LOAD_FACTOR 0.75
#define REDIS_DEFAULT_PORT 6379 // default port where redis will listen

// some predefine int types
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t i64;    



#endif // !COMMON_h