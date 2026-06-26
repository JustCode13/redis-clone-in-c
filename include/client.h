#ifndef CLIENT_H
#define CLIENT_H

#include <WinSock2.h>
#include <stdint.h>

#include <common.h>
#include <arena.h>
#include <resp.h>

typedef struct Client {
    SOCKET fd;
    Arena arena;
    RespParser parser;
    
    char recv_buffer[8192];
    size_t recv_used;

    char send_buffer[8192];
    size_t send_used;

    uint64_t last_activity;
} Client;


Client *client_create(SOCKET fd);

void client_destroy(Client *client);

int client_recv(Client *client);

int client_send(Client *client);

void client_reset(Client *client);

#endif // !CLIENT_H
