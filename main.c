#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "headers/communication/commands.h"
#include "headers/configs/configurator.h"
#include "headers/configs/read_rules.h"
#include "headers/game/core.h"
#include "headers/results/writefile.h"
#include "headers/connectivity/server.h"


int main(int argc, char **argv) {
    pthread_t server_listening_thread;
    pthread_t user_handler_thread;

    // Initialize the configuration
    server_config server_config = readconfig();

    // Initialize the rules and game
    init_game();

    // Initialize the server commands
    setup_commands();

    int sockfd = create_server(server_config.ip, atoi(server_config.port));
    pthread_create(&server_listening_thread, NULL, listening, (void *) &sockfd);
    pthread_detach(server_listening_thread);

    pthread_create(&user_handler_thread, NULL, handle_clients, (void *) &sockfd);
    pthread_join(user_handler_thread, NULL);

    close(sockfd);

    return EXIT_SUCCESS;
}