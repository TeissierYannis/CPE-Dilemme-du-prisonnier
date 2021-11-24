#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <string.h>
#include "headers/communication/commands.h"
#include "headers/srvcxnmanager.h"
#include "headers/configs/configurator.h"
#include "headers/configs/read_rules.h"
#include "headers/game/core.h"



int main(int argc, char **argv)
{
    //Initialize game
    game game0;
    init_game(&game0);
    
    // Initialize the configuration
    server_config server_config = readconfig();

    // Read rules
    rules rules0;
    read_rules(&rules0);

    //rules0.default_wallet = 50;

    //add player
    player player0;
    char *ip = malloc(sizeof(char) * 20);
    ip = "127.0.0.1";
    init_player(&game0, &player0, ip, &rules0);

    player player1;
    char *ip1 = malloc(sizeof(char) * 20);
    ip1 = "192.168.0.1";
    init_player(&game0, &player1, ip1, &rules0);

    //add party
    party party0;
    init_party(&game0, &party0, player0, player1);
    
    //init round;
    round round0;
    init_round(&round0, 2, 4, 0.125, 0.145);
    
    //add_round_to_party
    add_round_to_party(&party0, round0);
    

    // TEST
    /*
    printf("Test: %d\n", game->parties_count);
    printf("Test: %d\n", game->players_count); 
    printf("ip0:%s\n",game0.player[1].ip);
    printf("ip1:%s\n",game0.player[2].ip);
    printf("j1:%s - j2:%s\n", party0.player_game[0].ip, party0.player_game[1].ip);
    */

    // Initialize the server commands
    setup_commands();

    int sockfd;
    int index = 1;
    connection_t *connection;
    pthread_t thread;

    // init array
    init_sockets_array();
    // create socket
    sockfd = create_server_socket(server_config.ip, atoi(server_config.port));

    // listen on port , stack size 50 for incoming connections
    if (listen(sockfd, 50) < 0) {
        fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
        return -5;
    }
    printf("[SERVER] Server listening on %s:%s\n", server_config.ip, server_config.port);

    // waiting for connections
    while (true) {
        // accept incoming connections
        connection = (connection_t *) malloc(sizeof (connection_t));
        connection->sockfd = accept(sockfd, &connection->address, &connection->addr_len);
        connection->index = index++;

        if (connection->sockfd <= 0) {
            free(connection);
        } else {
            // start a new thread but do not wait for it
            pthread_create(&thread, 0, thread_process, (void *) connection);
            pthread_detach(thread);
        }
    }

    //free(game0);
    return EXIT_SUCCESS;
}