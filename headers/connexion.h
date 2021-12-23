/**
 * @file connexion.h 
 * @brief Outils pour établir la connexion avec le serveur
 * @version 0.1
 * @date 2021-12-23
 * @author Alexis REVOL
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifndef CONNEXION_H
#define CONNEXION_H

// Créer socket
int create_socket();
// Créer adresse serveur
struct sockaddr_in create_serv_adrr(char *adresse_serv, int port_serveur);
// Se connecter au serveur
int client_connexion();



#endif