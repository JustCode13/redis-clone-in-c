#ifndef PROTOCOL_H                     // Prevents this header file from being included multiple times
#define PROTOCOL_H

#include "common.h"                    // Includes common project definitions, types, and macros
#include "database.h"                  // Includes database-related structures and functions


// Represents the current state of the RESP parser while reading client data
typedef enum {

    // Parser is waiting for the beginning of a command
    RESP_START,

    // Parser is reading an array
    RESP_ARRAY,

    // Parser is reading a bulk string
    RESP_BULK,

    // Parser is reading an inline command
    RESP_INLINE,

    // Parser is reading an integer
    RESP_INTEGER,

    // Parsing has completed successfully
    RESP_DONE

} RespState;


// Represents a RESP parser used to parse incoming client commands
typedef struct RespParser {

    // Current parsing state
    RespState state;

    // Buffer that stores received raw data
    char *buffer;

    // Total number of bytes currently stored in the buffer
    size_t length;

    // Current reading position inside the buffer
    size_t offset;

    // Number of parsed command arguments
    int argc;

    // Array containing pointers to each parsed argument
    char **argv;

} RespParser;


// Initializes a RESP parser before it is used
void parser_init(RespParser *parser);


// Adds new data to the parser and attempts to parse it
// Returns true if parsing succeeds, otherwise false
bool parser_feed(
    RespParser *parser,
    const char *data,
    size_t size
);


// Resets the parser so it can parse a new command
void parser_reset(RespParser *parser);


// Returns true if a complete command has been parsed
bool parser_complete(RespParser *parser);


// Returns true if the parser encountered an error
bool parser_error(RespParser *parser);


// Releases all memory used by the parser
void parser_destroy(RespParser *parser);

#endif      // End of include guard