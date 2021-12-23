//
// Created by Yannis Teissier on 26/11/2021.
//
#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "../game/core.h"

#define BUFFERSIZE 255

typedef struct {
    player *clients;
    int client_count;
} clients_list;

extern clients_list clientsList;

int create_server(char *ip, int port);

void *listening(void * socketfd);

void init_client_list(clients_list *clients);

void add_client(clients_list *clients, player client);

void remove_client(clients_list *clients, int socket);

int * randomize_pairs();

void *handle_clients();

void *thread_party(void *ptr);

void player_wanted_replay(player p1, player p2);

#endif //SERVER_SERVER_H
