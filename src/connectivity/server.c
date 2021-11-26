//
// Created by Yannis Teissier on 26/11/2021.
//

#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../headers/connectivity/server.h"

int create_server(char *ip, int port) {

    // Initialize the clients list
    init_client_list(&clientsList);

    // Socket file descriptor
    int socketfd = -1;

    // Socket address
    struct sockaddr_in server_addr;
    // create socket
    socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // check if socket is created
    if (socketfd <= 0) {
        fprintf(stderr, "Error creating socket\n");
        return -3;
    }

    // bind socket protocol
    server_addr.sin_family = AF_INET;
    // bind ip to socket
    server_addr.sin_addr.s_addr = inet_addr(ip);
    // bind port to socket
    server_addr.sin_port = htons(port);

    // prevent 60 timeout
    int timeout = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    // bind
    if (bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error binding socket\n");
        return -4;
    }

    return socketfd;
}

void *listening(void * socketfd) {

    socketfd = *(int *) socketfd;
    // Listen on port
    if (listen(socketfd, 50) < 0) {
        fprintf(stderr, "Error listening\n");
        pthread_exit(0);
    }

    // Accept connection
    while (1) {
        // Socket file descriptor
        struct sockaddr_in client_addr;
        // Socket address size
        socklen_t client_addr_len = sizeof(client_addr);
        // Accept connection
        int client_sock = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
        printf("User connected");
        // check if connection is accepted
        if (client_sock < 0) {
            fprintf(stderr, "Error accepting connection\n");
        }

        // Create a new client and add to global list
        player player;
        init_player(&player, client_sock);
        add_client(&clientsList, player);
    }
    pthread_exit(0);
}

void * handle_clients() {
    int * pair;

    while (1) {
        if (clientsList.client_count >= 2) {
            pair = randomize_pairs();
            // TODO IF ENCORE 1 ET PAS PLUS RIEN
            // Client.status = 0 -> free && 1 -> busy
            if (clientsList.clients[pair[0]].status == 0 && clientsList.clients[pair[1]].status == 0) {
                clientsList.clients[pair[0]].status = 1;
                clientsList.clients[pair[1]].status = 1;

                pthread_t thread;

                player *players = malloc(sizeof(player) * 2);
                players[0] = clientsList.clients[pair[0]];
                players[1] = clientsList.clients[pair[1]];

                pthread_create(&thread, 0, handle_clients, players);
            }

        }
    }

    pthread_exit(0);
}

int * randomize_pairs() {
    int * pair = malloc(sizeof(int) * 2);
    pair[0] = rand() % clientsList.client_count;
    pair[1] = rand() % clientsList.client_count;
    return pair;
}

void init_client_list(clients_list *client_list) {
    client_list->clients = malloc(sizeof(player) * 10);
    client_list->client_count = 0;
}

void add_client(clients_list *client_list, player client) {
    client_list->clients[client_list->client_count] = client;
    client_list->client_count++;
}

void remove_client(clients_list *client_list, int socketfd) {
    for (int i = 0; i < client_list->client_count; i++) {
        if (client_list->clients[i].socket == socketfd) {
            for (int j = i; j < client_list->client_count - 1; j++) {
                client_list->clients[j] = client_list->clients[j + 1];
            }
            client_list->client_count--;
            break;
        }
    }
}
