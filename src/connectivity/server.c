//
// Created by Yannis Teissier on 26/11/2021.
//

#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../headers/connectivity/server.h"
#include "../../headers/communication/commands.h"

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

void *listening(void *socketfd) {

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
        printf("User connected\n");
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

void *handle_clients() {
    int *pair;

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

                printf("Running thread for party\n");

                pthread_create(&thread, 0, thread_party, players);
                pthread_detach(thread);
            }
        }
    }
    pthread_exit(0);
}


void *thread_party(void *ptr) {

    //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


    char buffer_out[BUFFERSIZE];

    //temp
    int Nb_Round_Max = rules0.nb_round;

    //Player
    //player p1, player p2
    //player *p2 = (player *)ptr;
    player *players = (player *) ptr;
    player p1 = players[0];
    player p2 = players[1];

    printf("Send user id to client\n");
    sprintf(buffer_out, "id %i", p1.id);
    write(p1.socket, buffer_out, strlen(buffer_out));
    sprintf(buffer_out, "id %i", p2.id);
    write(p2.socket, buffer_out, strlen(buffer_out));

    //Création de la partie
    party party;
    init_party(&party, p1, p2);
    sleep(5);

    printf("Send party id to client\n");
    sprintf(buffer_out, "party %i", party.id);
    write(p1.socket, buffer_out, strlen(buffer_out));
    write(p2.socket, buffer_out, strlen(buffer_out));

    //int round = 1;

    sleep(5);

    printf("Send start to client\n");
    sprintf(buffer_out, "start");
    write(p1.socket, buffer_out, strlen(buffer_out));
    write(p2.socket, buffer_out, strlen(buffer_out));

    /* p1.status = 1;
    p2.status = 1; */

    int p1Result = 0;
    int p2Result = 0;
    int p1Time = 0;
    int p2Time = 0;
    int nbRound = 1;

    //Gestion des rounds
    while (nbRound <= Nb_Round_Max) {
        size_t p1_t = 0, p2_t = 0;

        printf("Round %i\n", nbRound);
        answer_struct buffer_answer1, buffer_answer2;
        init_answer(&buffer_answer1);
        init_answer(&buffer_answer2);

        printf("Reading response from clients\n");
        p1_t = recv(p1.socket, &buffer_answer1, BUFFERSIZE, 0);
        p2_t = recv(p2.socket, &buffer_answer2, BUFFERSIZE, 0);

        printf("[SERVER] Received answer from #%i: \n Answer : %i\n Time : %i\n", p1.id,
               buffer_answer1.choice, buffer_answer1.time);
        p1Result = buffer_answer1.choice;
        p1Time = buffer_answer1.time;

        printf("[SERVER] Received answer from #%i: \n Answer : %i\n Time : %i\n", p2.id,
               buffer_answer2.choice, buffer_answer2.time);
        p2Result = buffer_answer2.choice;
        p2Time = buffer_answer2.time;

        round round_struct;
        init_round(&round_struct, p1Result, p1Time, p2Result, p2Time);

        sleep(5);

        //TODO : Update wallet
        //win round

        printf("Send round result to client...\n");

        // TODO : Send round result to client SET status to finished
        write(p1.socket, (void *)round_struct, sizeof(round));
        write(p2.socket, (void *)round_struct, sizeof(round));
        printf("Round result sent\n");
        //pthread_mutex_lock(&mutex);
        //pthread_mutex_unlock(&mutex);

        if (p1_t > 0 || p2_t > 0) {
            nbRound += 1;
        }
    }
    printf("BLABLA\n");

    //Fin de partie
    if (nbRound == Nb_Round_Max) {
        printf("Fin de la partie\n");
        p1.status = 0;
        p2.status = 0;
        int win = 1;
        //TODO win = winner(j1, j2)
        sprintf("Le gagnant est %i", win);

        //TODO write results.csv
        sleep(5);
    }

    pthread_exit(0);
}


int *randomize_pairs() {
    int *pair = malloc(sizeof(int) * 2);
    pair[0] = rand() % clientsList.client_count;
    pair[1] = rand() % clientsList.client_count;

    while (pair[0] == pair[1]) {
        pair[1] = rand() % clientsList.client_count;
    }
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
