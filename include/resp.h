#ifndef RESP_H
#define RESP_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "common.h"

#define RESP_MAX_ARGUMENTS       32
#define RESP_MAX_COMMAND_LENGTH  1024

typedef enum
{
    RESP_START,
    RESP_ARRAY,
    RESP_BULK,
    RESP_INTEGER,
    RESP_STRING,
    RESP_DONE

} RespState;

typedef struct
{
    int argc;

    char *argv[RESP_MAX_ARGUMENTS];

} RespCommand;

typedef struct
{
    RespState state;

    size_t expected;

    size_t received;

    RespCommand command;

} RespParser;

/* Parser */

int resp_parse(RespParser *parser,
               const char *buffer,
               size_t length);

void resp_reset(RespParser *parser);

/* Encoder */

int resp_encode_ok(char *buffer,
                   size_t buffer_size);

int resp_encode_error(char *buffer,
                      size_t buffer_size,
                      const char *message);

int resp_encode_bulk(char *buffer,
                     size_t buffer_size,
                     const char *data);

int resp_encode_integer(char *buffer,
                        size_t buffer_size,
                        int64_t value);

#endif