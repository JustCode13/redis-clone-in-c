#ifndef CONFIG_H
#define CONFIG_H

/*
 * Configuration system for Redis clone.
 *
 * This file defines:
 * - Default server settings
 * - Config structure
 * - Configuration management functions
 */


#include "common.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/*
========================================================
                    DEFAULT VALUES
========================================================
*/


// Default TCP port where server listens
#define DEFAULT_PORT 6379


// Default maximum memory allowed (256 MB)
#define DEFAULT_MAX_MEMORY (256ULL * 1024 * 1024)


// Default maximum connected clients
#define DEFAULT_MAX_CLIENTS 10000


// Default Append Only File name
#define DEFAULT_AOF_FILE "appendonly.aof"


// Default RDB snapshot file name
#define DEFAULT_RDB_FILE "dump.rdb"


// Default snapshot interval (seconds)
#define DEFAULT_SAVE_INTERVAL 300



/*
========================================================
                    CONFIG STRUCTURE
========================================================
*/


typedef struct Config {

    /*
     * Server TCP listening port
     *
     * Example:
     * 6379
     */
    uint16_t port;



    /*
     * Maximum memory Redis clone can use
     *
     * Example:
     * 256 MB
     */
    size_t max_memory;



    /*
     * Enables Append Only File persistence
     *
     * true  -> write commands to AOF
     * false -> disable AOF
     */
    bool append_only;



    /*
     * Enables RDB snapshot persistence
     *
     * true  -> allow snapshots
     * false -> disable snapshots
     */
    bool save_snapshots;



    /*
     * Initial arena allocator size
     *
     * Used by memory subsystem
     */
    size_t arena_size;



    /*
     * Maximum simultaneous clients
     */
    size_t max_clients;



    /*
     * Path of AOF persistence file
     */
    char aof_file[260];



    /*
     * Path of RDB snapshot file
     */
    char rdb_file[260];



    /*
     * Seconds between automatic snapshots
     */
    uint32_t save_interval;


} Config;



/*
========================================================
                 FUNCTION DECLARATIONS
========================================================
*/



/*
 * Loads configuration from file.
 *
 * Arguments:
 *
 * config:
 *      Pointer to Config structure which receives values
 *
 * filename:
 *      Path of configuration file
 *
 *
 * Returns:
 *
 * true:
 *      Configuration loaded successfully
 *
 * false:
 *      Loading failed
 */
bool config_load(
    Config *config,
    const char *filename
);



/*
 * Saves current configuration to file.
 *
 * Arguments:
 *
 * config:
 *      Configuration data to save
 *
 * filename:
 *      Output configuration file path
 *
 *
 * Returns:
 *
 * true:
 *      Saved successfully
 *
 * false:
 *      Save failed
 */
bool config_save(
    Config *config,
    const char *filename
);



/*
 * Initializes configuration with default values.
 *
 * Example:
 *
 * port = 6379
 * max_memory = 256MB
 * max_clients = 10000
 */
void config_defaults(
    Config *config
);



/*
 * Validates configuration values.
 *
 * Checks:
 *
 * - Port is valid
 * - Memory limit is valid
 * - Client count is valid
 * - File paths are valid
 *
 *
 * Returns:
 *
 * true:
 *      Configuration is valid
 *
 * false:
 *      Invalid configuration
 */
bool config_validate(
    const Config *config
);



#endif // CONFIG_H