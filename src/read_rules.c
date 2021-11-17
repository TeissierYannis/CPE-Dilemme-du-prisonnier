/**
 * @file read_rules.c
 * @author Nicola Piemontese
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/read_rules.h"
#include "../headers/string_utils.h"

#include <string.h>


/**
 * Initialize json parsing to key:value
 * @brief Initialize json parsing to key:value
 * @param server_config config file
 * @author Yannis Teissier
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
    //free(value);
}



void read_rules()
{
    FILE * file_p = fopen("../config/rules_config_temp.json", "r");
    
    char * ip_address = malloc(sizeof(char) * 20);
    parse_json("ip_address", ip_address, file_p);
    printf("ip:%s\n", ip_address);

    char * test = malloc(sizeof(char) * 20);
    parse_json("betrayals_win", test, file_p);
    printf("Test :%s\n", test); 
    free(test);

    free(ip_address);
    free(file_p);
}