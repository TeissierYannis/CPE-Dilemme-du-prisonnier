#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "headers/configs/configurator.h"
#include "headers/game/core.h"
#include "headers/connectivity/server.h"

int main(int argc, char **argv) {
    // Initialize base variables
    pthread_t server_listening_thread;
    pthread_t user_handler_thread;
    // Initialize the configuration
    server_config server_config = readconfig();
    // Initialize the rules and game
    printf("[MAIN] Initializing the game...\n");
    init_game();
    // Initialize the server commands
    // setup_commands();

    // Create the server
    printf("[MAIN] Creating the server...\n");
    int sockfd = create_server(server_config.ip, atoi(server_config.port));
    // Create the server listening thread
    printf("[MAIN] Creating the server listening thread...\n");
    pthread_create(&server_listening_thread, NULL, listening, (void *) &sockfd);
    // Detach the thread to let it run in the background
    pthread_detach(server_listening_thread);

    // Create the user handler thread
    printf("[MAIN] Creating the user handler thread...\n");
    pthread_create(&user_handler_thread, NULL, handle_clients, (void *) &sockfd);
    // Join the thread to let it finish
    pthread_join(user_handler_thread, NULL);

    // Close the server
    printf("[MAIN] Closing the server...\n");
    close(sockfd);
    printf("[MAIN] Server closed.\n");
    pthread_exit(&server_listening_thread);

    return EXIT_SUCCESS;
}