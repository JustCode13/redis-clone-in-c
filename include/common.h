#ifndef COMMON_h
#define COMMON_h


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#define REDIS_MAX_KEY_SIZE 256
#define REDIS_MAX_CLIENTS 10000
#define REDIS_LOAD_FACTOR 0.75
#define REDIS_DEFAULT_PORT 6379

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t i64;    



#endif // !COMMON_h