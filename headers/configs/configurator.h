/**
 * @file configurator.h
 * @author Teissier Yannis
 * @brief This file contains the configurations methods.
 * @version 0.1
  * @date 2021-11-12
 * @copyright Copyright (c) 2021
 */


#ifndef CLIENT_CONFIGURATOR_H
#define CLIENT_CONFIGURATOR_H

/**
 * @brief Server configuration (ip, port)
 * Server configuration
 */
typedef struct {
    char *port;
    char *ip;
} server_config;

/**
 * Initialize server config struct
 * @param server_config  server config struct
 */
void init_config(server_config *config);

/**
 * Initialize json parsing to key:value
 * @brief Initialize json parsing to key:value
 * @param server_config config file
 */
void parse_json(char *search_key, char *to_assign, FILE *config_file);

/**
 * Read config json file and setup server struct
 * @return server config struct
 */
server_config readconfig();

#endif //CLIENT_CONFIGURATOR_H
