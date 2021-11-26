
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

void *thread_party(void *ptr)
{

    char buffer_in[BUFFERSIZE];
    char buffer_out[BUFFERSIZE];

    //temp
    game game; 
    rules rules;
    int Nb_Round_Max = rules.nb_round;

    //Player
    //player p1, player p2
    //player *p2 = (player *)ptr;
    player *players[] = (player *)ptr;
    player p1 = *players[0];
    player p2 = *players[1];

    //Création de la partie
    party party;
    init_party(&game, &party, p1, p2 );
    sleep(5);

    printf("Send party id to client\n");
    sprintf(buffer_out, "party %i", party.id);
    write(p1.connection.sockfd, buffer_out, strlen(buffer_out));
    write(p2.connection.sockfd, buffer_out, strlen(buffer_out));

    //int round = 1;

    sleep(5);

    printf("Send start to client\n");
    sprintf(buffer_out, "start");
    write(p1.connection.sockfd, buffer_out, strlen(buffer_out));
    write(p2.connection.sockfd, buffer_out, strlen(buffer_out));

    /* p1.status = 1;
    p2.status = 1; */
    
    int p1Result=0;
    int p2Result=0;
    int p1Time=0;
    int p2Time=0;

    int nbRound=0;
    //Gestion des rounds
    for(; nbRound <= Nb_Round_Max; nbRound++)
    {
        answer_struct buffer_answer1, buffer_answer2;
        
        
        read(p1.connection.sockfd, &buffer_answer1, BUFFERSIZE);
        read(p2.connection.sockfd, &buffer_answer2, BUFFERSIZE);
        
        printf("[SERVER] Received answer from #%i: \n Answer : %i\n Time : %i\n", p1.connection.index,
               buffer_answer1.choice, buffer_answer1.time);
        p1Result = buffer_answer1.choice;
        p1Time = buffer_answer1.time;

        printf("[SERVER] Received answer from #%i: \n Answer : %i\n Time : %i\n", p2.connection.index,
               buffer_answer2.choice, buffer_answer2.time);
        p2Result = buffer_answer2.choice;
        p2Time = buffer_answer2.time;
        
        
        round round;
        init_round(&round, p1Result, p1Time, p2Result, p2Time);
        
        sleep(5);

        //TODO : Update wallet
        //win round

        printf("Send round result to client\n");
        sprintf(buffer_out, "round %i,P1: %i, P2: %i ", nbRound, p1Result, p2Result);
        write(p1.connection.sockfd, buffer_out, strlen(buffer_out));
        write(p2.connection.sockfd, buffer_out, strlen(buffer_out));

        sleep(5);


    }

    //Fin de partie
    if(nbRound == Nb_Round_Max) 
    {
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