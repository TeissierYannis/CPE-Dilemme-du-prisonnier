
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../headers/srvcxnmanager.h"
#include "../headers/communication/commands.h"
#include "../headers/game/core.h"
#include "../headers/configs/read_rules.h"

connection_t *connections[MAXSIMULTANEOUSCLIENTS];

void init_sockets_array() {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        connections[i] = NULL;
    }
}

void add(connection_t *connection) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == NULL) {
            connections[i] = connection;
            return;
        }
    }
    perror("[SERVER] Too much simultaneous connections");
    exit(-5);
}

void del(connection_t *connection) {
    for (int i = 0; i < MAXSIMULTANEOUSCLIENTS; i++) {
        if (connections[i] == connection) {
            connections[i] = NULL;
            return;
        }
    }
    perror("[SERVER] Connection not in pool ");
    exit(-5);
}
/*
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&lock);
pthread_mutex_unlock(&lock);
 */

/**
 * Thread allowing server to handle multiple client connections
 * @param ptr connection_t 
 * @return 
 */
void *thread_process(void *ptr) {
    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];

    // Lecture des règles
    rules rules;
    read_rules(&rules);

    int MAX_ROUND = rules.nb_round;

    // Création d'une partie
    game game;
    init_game(&game);

    connection_t *connection;

    if (!ptr)
        pthread_exit(0);

    connection = (connection_t *) ptr;
    printf("[SERVER] New incoming connection \n");

    add(connection);

    //Welcome the new client
    printf("[SERVER] Welcome #%i\n", connection->index);
    sprintf(buffer_out, "id %i", connection->index);
    write(connection->sockfd, buffer_out, strlen(buffer_out));

    // TODO Traitement des joueurs et début de la partie
    player pl;
    init_player(&game, &pl, "127.0.0.1", &rules);
    pl.id = connection->index;

    while (game.players_count < 2) {
        sleep(1);
    }

    party party;
    player p1 = game.player[0];
    player p2 = game.player[1];

    init_party(&game, &party, p1, p2);

    sleep(5);

    // TODO Envoyer ID party

    printf("Send party id to client\n");
    sprintf(buffer_out, "party %i", party.id);
    write(connection->sockfd, buffer_out, strlen(buffer_out));

    int round = 1;

    sleep(5);

    printf("Send start to client\n");
    sprintf(buffer_out, "start");
    write(connection->sockfd, buffer_out, strlen(buffer_out));

    char * status = "ingame";

    for (; round <= MAX_ROUND; round++) {

        // TODO ENVOYER ROUND
        answer_struct buffer_answer;

        read(connection->sockfd, &buffer_answer, BUFFERSIZE);
        printf("[SERVER] Received answer from #%i: \n Answer : %i\n Time : %i\n", connection->index,
               buffer_answer.choice, buffer_answer.time);

        // TODO Traitement des réponses

        sleep(5);

        printf("Send round result to client\n");

        if (round == MAX_ROUND) {
            status = "finished";
        }

        round_result rr = {1, 2, round};
        strcpy(rr.status, status);

        // TODO Envoyer resultat round
        write(connection->sockfd, &rr, sizeof(round_result));
    }

    printf("Fin de la partie\n");

    sleep(5);

    printf("[SERVER] Connection to client %i ended \n", connection->index);
    close(connection->sockfd);
    del(connection);
    free(connection);
    pthread_exit(0);

}

int create_server_socket(char *ip_address, int port) {
    int sockfd = -1;
    struct sockaddr_in address;

    /* create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd <= 0) {
        fprintf(stderr, "[SERVER] %s: error: cannot create socket\n");
        return -3;
    }


    /* bind socket to port */
    address.sin_family = AF_INET;
    //bind to all ip : 
    //address.sin_addr.s_addr = INADDR_ANY;
    //ou 0.0.0.0 
    //Sinon  127.0.0.1
    address.sin_addr.s_addr = inet_addr(ip_address);
    address.sin_port = htons(port);

    /* prevent the 60 secs timeout */
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse, sizeof(reuse));

    /* bind */
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(struct sockaddr_in)) < 0) {
        fprintf(stderr, "[SERVER] error: cannot bind socket to port %d\n", port);
        return -4;
    }

    return sockfd;
}
