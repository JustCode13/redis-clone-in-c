#include <stdio.h>

#include "server.h"

int main(void)
{
    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    RedisServer server;

    if (server_init(&server, REDIS_DEFAULT_PORT) != 0)
    {
        printf("Server initialization failed\n");
        WSACleanup();
        return 1;
    }

    if (server_start(&server) != 0)
    {
        printf("Server failed to start\n");
        server_stop(&server);
        WSACleanup();
        return 1;
    }

    server_stop(&server);

    WSACleanup();

    return 0;
}