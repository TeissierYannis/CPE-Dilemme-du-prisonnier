//
// Created by Yannis Teissier on 12/11/2021.
//

#pragma once

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
 * Read config json file and setup server struct
 * @return server config struct
 */
server_config readconfig();
#endif //CLIENT_CONFIGURATOR_H
