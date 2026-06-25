#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <time.h>

// #include "common.h"
// #include "client.h"
// #include "database.h"
// #include "persistence.h"
// #include "pubsub.h"
// #include "lru.h"

typedef struct RedisServer {
    SOCKET listen_fd;
    Client **clients;
    Database db;
    AOFState aof;
    PubSubManager pubsub;
    LRUCache lru;
    uint64_t start_time;
    size_t connected_clients;
    int running;
} RedisServer;

// int server_init(RedisServer *server, int port);

// int server_start(RedisServer *server);

// void server_stop(RedisServer *server);

// int server_accept_client(RedisServer *server);

// void server_disconnect_client(RedisServer *server,
//                               Client *client);

// void server_process_events(RedisServer *server);

#endif