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
#include <stdbool.h>
#include "../../headers/connectivity/server.h"
#include "../../headers/game/rules.h"

clients_list clientsList;

int is_running = 1;

/**
 * Create server socket from IP and PORT
 * @brief Create server socket from IP and PORT
 * @param ip IP address
 * @param port PORT
 * @return server socket
 */
int create_server(char *ip, int port) {

    // Initialize the clients list
    init_client_list(&clientsList);

    // Socket file descriptor
    int socketfd = -1;

    // Socket address
    struct sockaddr_in server_addr;
    // create socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

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
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(int));

    // bind
    if (bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error binding socket\n");
        return -4;
    }

    // return socket
    return socketfd;
}

/**
 * Accept client connection
 * @brief Accept client connection
 * @param socketfd server socket
 * @return client socket
 */
void *listening(void *socketfd) {
    // Socket file descriptor converted to int
    socketfd = *(int *) socketfd;
    // Listen on port
    if (listen(socketfd, 50) < 0) {
        fprintf(stderr, "[LISTENING] Error listening\n");
        is_running = 0;
        fprintf(stderr, "[LISTENING] Stopping listening thread.\n");
        pthread_exit(0);
    }

    // Accept connection
    while (is_running) {
        // Socket file descriptor
        struct sockaddr_in client_addr;
        // Socket address size
        socklen_t client_addr_len = sizeof(client_addr);
        // Accept connection
        int client_sock = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
        printf("[LISTENING] User connected #%d\n", client_sock);
        // check if connection is accepted
        if (client_sock < 0) {
            fprintf(stderr, "[LISTENING] Error accepting connection\n");
        }

        // Create a new client and add to global list
        player player;
        init_player(&player, client_sock);
        add_client(&clientsList, player);
        printf("Clients connected : %d\n", clientsList.client_count);
    }
    pthread_exit(0);
}

/**
 * Dispatch client to parties thread
 * @brief Dispatch client to parties thread
 * @return void*
 */
void *handle_clients() {
    int *pair;
    pthread_t thread;

    while (is_running) {
        sleep(1);
        // Si 2 joueurs sont disponibles
        if (clientsList.client_count >= 2) {
            // Randomize clients pairs
            pair = randomize_pairs();
            // Client.status = 0 -> free && 1 -> busy
            if (clientsList.clients[pair[0]].status == 0 && clientsList.clients[pair[1]].status == 0) {
                clientsList.clients[pair[0]].status = 1;
                clientsList.clients[pair[1]].status = 1;

                // Create list of 2 clients from random pair
                player *players = malloc(sizeof(player) * 2);
                players[0] = clientsList.clients[pair[0]];
                players[1] = clientsList.clients[pair[1]];

                printf("[HANDLER] Running thread for party\n");

                // Create thread for party
                pthread_create(&thread, 0, thread_party, players);
                pthread_detach(thread);

                // Remove players from list
                remove_client(&clientsList, players[0].socket);
                remove_client(&clientsList, players[1].socket);
            }
        }
        usleep(10000); // Faire une pause dans le while TRUE (en us)
    }
    printf("[HANDLER] Stopping handler thread.\n");
    pthread_exit(0);
}


/**
 * Thread for party
 * @brief Thread for party
 * @param players list of players
 */
void *thread_party(void *ptr) {
  //  char buffer_out[BUFFERSIZE];
    Buffer_out buffer;

    //temp
    int Nb_Round_Max = rules0.nb_round;

    player *players = (player *) ptr;
    player p1 = players[0];
    player p2 = players[1];

    printf("Send user id to client\n");

    sprintf(buffer.out, "id %d:1", p1.id);
    printf("%s\n", buffer.out);
    write(p1.socket, &buffer, sizeof(buffer));

    sprintf(buffer.out, "id %d:2", p2.id);
    printf("%s\n", buffer.out);
    write(p2.socket, &buffer, sizeof(buffer));

    sleep(3);

    // create party
    party party;
    init_party(&party, p1, p2);

    printf("[PARTY #%d] Party running\n", party.id);

    printf("[PARTY #%d] Send party id to client\n", party.id);
   
    sprintf(buffer.out, "party %i", party.id);
    
    write(p1.socket, buffer.out, sizeof(buffer));
    write(p2.socket, buffer.out, sizeof(buffer));

    sleep(3);

    // status 0 = playing, 1 = finished
    printf("[PARTY #%d] Send start instruction to client\n", party.id);
    int status = 0;

    sprintf(buffer.out, "status %d", status);
    write(p1.socket, buffer.out, sizeof(buffer));
    write(p2.socket, buffer.out, sizeof(buffer));
    printf("TAILLE ENVOYEE : %d\n", sizeof(buffer));
   // sleep(3);

    int nbRound = 1;

    int p1Result, p2Result, p1Time, p2Time, p1Wallet, p2Wallet;
    size_t p1_sizet, p2_sizet;
    answer_struct buffer_answer1, buffer_answer2;
    round round_struct, round_party;
    //Gestion des rounds
    while (nbRound <= Nb_Round_Max) {
        printf("[PARTY #%d] Round %i\n", nbRound, party.id);
        
        init_answer(&buffer_answer1);
        init_answer(&buffer_answer2);

        printf("[PARTY #%d] Reading response from clients\n", party.id);
       // p1_t = read(p1.socket, &buffer_answer1, sizeof(answer_struct));
       // p2_t = read(p2.socket, &buffer_answer2, sizeof(answer_struct));
       p1_sizet = read(p1.socket, &buffer_answer1, sizeof(buffer_answer1));
       p2_sizet = read(p2.socket, &buffer_answer2, sizeof(buffer_answer2));
        
        if(p1_sizet < 0 || p2_sizet < 0){
            perror("[PARTY] Error reading response from clients");
            close(p1.socket);
            close(p2.socket);
            exit(EXIT_FAILURE);
        } 

        usleep(100000); // Wait a little
        
        p1_sizet = 1;
        p2_sizet = 1;
        printf("Réponse J1 reçue ... = %d\n", buffer_answer1.choice);
        if (p1_sizet > 0 || p2_sizet > 0) {

            printf("[PARTY #%d] Received answer from #%i: \n Answer : %i\n Time : %i\n",party.id,p1.id,buffer_answer1.choice,buffer_answer1.time);
            // fill answer struct
            p1Result = buffer_answer1.choice;
            p1Time = buffer_answer1.time;

            printf("[PARTY #%d] Received answer from #%i: \n Answer : %i\n Time : %i\n",party.id,p2.id,buffer_answer2.choice,buffer_answer2.time);
            // fill answer struct
            p2Result = buffer_answer2.choice;
            p2Time = buffer_answer2.time;

            if (nbRound == Nb_Round_Max) {
                status = 1;
                printf("JEU FINI !!! \n");
            }

            //Update wallet
            // Les calcul de scores
            updateWallet(p1Result, p2Result, &p1, &p2);
            printf("Wallet: P1: %d - P2: %d\n", p1.wallet, p2.wallet);

            p1Wallet = p1.wallet;
            p2Wallet = p2.wallet; 

            printf("[PARTY #%d] Generating round result\n", party.id);
            
            init_round(&round_struct, p1Result, p1Time, p2Result, p2Time, status, nbRound, p1Wallet, p2Wallet);
            init_round(&round_party, p1Result, p1Time, p2Result, p2Time, status, nbRound, p1Wallet, p2Wallet);

            printf("[PARTY #%d] Sending round result to clients... \n", party.id);
            printf("Envoie du round ... avec numero = %d\n", round_struct.round_number);
            printf("Envoie du round ... avec choix j1 = %d\n", round_struct.p1_result);
            write(p1.socket, &round_struct, sizeof(round));
            write(p2.socket, &round_struct, sizeof(round));
            printf("[PARTY #%d] Round result sent. \n", party.id);

            add_round_to_party(&party, &round_struct);

            nbRound += 1;
        }
    }
    printf("[PARTY #%d] Every rounds was played \n", party.id);

    int win = winner(p1, p2);
    write(p1.socket, &win, sizeof(int));
    write(p2.socket, &win, sizeof(int));

    printf("[PARTY #%d] Le gagnant est %d\n", party.id, win);

    printf("[PARTY #%d] Generating recap...\n", party.id);
    recap party_recap = generating_recap(&party);
    printf("[PARTY #%d] Sending recap to clients... \n", party.id);
    write(p1.socket, &party_recap, sizeof(recap));
    write(p2.socket, &party_recap, sizeof(recap));
    printf("[PARTY #%d] Recap sent. \n", party.id);

    // End of the party
    printf("[PARTY #%d] Fin de la partie\n", party.id);

    printf("[PARTY #%d] Logging results...\n", party.id);
    //TODO write results.csv
    
    printf("[PARTY #%d] Results logged...\n", party.id);
    printf("[PARTY #%d] Leaving party...\n", party.id);
    
    // Recupérer si le joueur veut rejouer ou quitter
    player_wanted_replay(p1, p2);

    free(players);

    pthread_exit(0);
}

void player_wanted_replay(player p1, player p2) {
    int p1_res, p2_res;
    char status_j1[20];
    char status_j2[20];
    Buffer_out buffer_j1;
    Buffer_out buffer_j2;

    printf("[PARTY] Waiting for players wanted to replay\n");
    p1_res = read(p1.socket, &buffer_j1, sizeof(buffer_j1));
    p2_res = read(p2.socket, &buffer_j2, sizeof(buffer_j2));

    if(p1_res < 0 || p2_res < 0){
        perror("[PARTY] Error reading response from clients");
        close(p1.socket);
        close(p2.socket);
        exit(EXIT_FAILURE);
    }

    strcpy(status_j1, buffer_j1.out);
    strcpy(status_j2, buffer_j2.out);
    // P1 want to replay
    if(strcmp(status_j1, "online") == 0) {
        printf("P1 want to replay\n");
        p1.status = 0;
        // Add client to the queue
        player from_p1;
        init_player(&from_p1, p1.socket);
        add_client(&clientsList, from_p1);
    }
        // P1 do not want to replay
    else {
        printf("P1 is leaving\n");
        close(p1.socket);
        // Closing socket
    }

    // P2 want to replay
    if(strcmp(status_j2, "online") == 0) {
        printf("P2 want to replay\n");
        p2.status = 0;
        // Add client to the queue
        player from_p2;
        init_player(&from_p2, p2.socket);
        add_client(&clientsList, from_p2);
    } // P2 do not want to replay
    else {
        printf("P2 is leaving\n");
        close(p2.socket);
        // Closing socket
    }
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
