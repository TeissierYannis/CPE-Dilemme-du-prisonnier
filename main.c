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

int main(int argc, char **argv)
{
    // Initialize the configuration
    server_config server_config = readconfig();

    // Read rules
    read_rules();
  
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
    return EXIT_SUCCESS;
}