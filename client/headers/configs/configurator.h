//
// Created by Yannis Teissier on 12/11/2021.
//

#ifndef CLIENT_CONFIGURATOR_H
#define CLIENT_CONFIGURATOR_H

typedef struct {
    char * port;
    char * ip;
} server_config;

/**
 * Initialize server config struct
 * @param server_config  server config struct
 */
void init_config(server_config * config);

/**
 * Initialize json parsing to key:value
 * @brief Initialize json parsing to key:value
 * @param server_config config file
 */
void parse_json(char * search_key, char * to_assign, FILE * config_file);

/**
 * Read config json file and setup server struct
 * @return server config struct
 */
server_config readconfig();
#endif //CLIENT_CONFIGURATOR_H
