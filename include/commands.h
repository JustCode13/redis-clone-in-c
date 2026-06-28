#ifndef COMMANDS_H                 // Prevents this header file from being included multiple times
#define COMMANDS_H

#include "common.h"                // Common types, macros, and project-wide definitions
#include "database.h"              // Database-related functions and structures
#include "protocol.h"              // Protocol parsing and response functions
#include "object.h"                // Redis object definitions and functions


// Forward declaration of the Client structure
// Used because only a pointer to Client is needed here
typedef struct Client Client;


// Represents a single Redis command
typedef struct Command {

    // Name of the command (e.g. "GET", "SET", "DEL")
    const char *name;

    // Minimum number of arguments the command accepts
    int min_args;

    // Maximum number of arguments the command accepts
    int max_args;

    // Pointer to the function that executes the command
    // This is called whenever the command is executed
    int (*handler)(Client *client, int argc, char **argv); 
    // when add parantheses it means handler is a pointer to a function which returns int and takes these argumments (Client *client, int argc, char **argv)

} Command;


// Searches for a command by its name
// Returns a pointer to the command if found, otherwise NULL
Command *command_lookup(const char *name);


// Executes a command using the given client and arguments
// Returns the result of the command execution
int command_execute(
    Client *client,
    int argc,
    char **argv
);


// Registers all supported commands into the command table
void register_commands(void);


// Removes all registered commands and cleans up resources
void unregister_commands(void);

#endif      // End of include guard