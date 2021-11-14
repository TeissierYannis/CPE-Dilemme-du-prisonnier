//
// Created by Yannis Teissier on 12/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/configurator.h"
#include "../headers/string_utils.h"

/**
 * Read config json file and setup server struct
 * @return server config struct
 */
server_config readconfig() {
     // Read config file
    FILE * file_p = fopen("../config/server_config.json", "r");

    server_config server_config;
    init_config(&server_config);

    // Check if file exists
    if (file_p == NULL) {
        printf("Error opening configuration file!\n");
        exit(1);
    }

    printf("\nReading configuration file...\n\n");

    key_value("ip_address", server_config.ip, file_p);
    key_value("port", server_config.port, file_p);

    // Print config to debug
    printf("========== Configuration ==========\n");
    printf("\tPort: \t\t\t%s\n", server_config.port);
    printf("\tServer ip: \t\t%s\n", server_config.ip);
    printf("===================================\n\n");

    printf("Configuration file read!\n\n");

    // Close file
    fclose(file_p);

    // Return config
    return server_config;
}

/**
 * Initialize json parsing to key:value
 * @brief Initialize json parsing to key:value
 * @param server_config config file
 */
void parse_json(char * search_key, char * to_assign, FILE * config_file) {

    char * buffer = malloc(sizeof(char) * 100), * key = malloc(sizeof(char) * 20), * value = malloc(sizeof(char) * 20);
    int i = 0;

    // Read file word by word
    while (fscanf(config_file, " %1023s", buffer) == 1) {
        if (strcmp(buffer, "{") == 0 || strcmp(buffer, "}") == 0)
            continue;

        // Get key
        if (i == 0) {
            // copy buffer to key
            strcpy(key, buffer);
            // Remove '"'
            remchar(key, '"');
            // Remove ':'
            remchar(key, ':');
            i++;
        } else if (i == 1) {
            // copy buffer to value
            strcpy(value, buffer);
            // Remove quotes
            remchar(value, '"');
            // Remove comma
            remchar(value, ',');
            // Check for key value pair
            if (strcmp(key, search_key) == 0) {
                // Set port
                strcpy(to_assign, value);
            }
            // Reset
            i--;
        }
    }
    // Reset file pointer
    rewind(config_file);
    // Free memory
    free(buffer);
    free(key);
    free(value);
}

/**
 * Initialize server config struct
 * @param server_config  server config struct
 */
void init_config(server_config * config) {
    config->port = malloc(sizeof(char) * 20);
    config->ip = malloc(sizeof(char) * 20);
}