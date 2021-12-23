//
// Created by Yannis Teissier on 12/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "../../headers/configs/configurator.h"

/**
 * Read config json file and setup server struct
 * @return server config struct
 */
server_config readconfig() {
     // Read config file
    FILE * file_p = fopen("../config/config.json", "r");

    // Initialize server config struct
    server_config server_config;
    init_config(&server_config);

    // Check if file exists
    if (file_p == NULL) {
        printf("[CONFIGURATOR] Error opening configuration file!\n");
        exit(1);
    }

    // Trace
    printf("\n[CONFIGURATOR] Reading configuration file...\n\n");

    // Read file
    parse_json("ip_address", server_config.ip, file_p);
    parse_json("port", server_config.port, file_p);

    // Print config to debug
    printf("========== Configuration ==========\n");
    printf("\tPort: \t\t\t%s\n", server_config.port);
    printf("\tServer ip: \t\t%s\n", server_config.ip);
    printf("===================================\n\n");

    // Trace
    printf("[CONFIGURATOR] Configuration file read!\n\n");

    // Close file
    fclose(file_p);

    // Return config
    return server_config;
}

/**
 * Initialize server config struct
 * @param server_config  server config struct
 */
void init_config(server_config * config) {
    config->port = malloc(sizeof(char) * 20);
    config->ip = malloc(sizeof(char) * 20);
}