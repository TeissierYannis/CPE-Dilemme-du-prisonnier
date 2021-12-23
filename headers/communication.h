/**
 * @file communication.h 
 * @brief Fonctionnalités pour communiquer avec le serveur
 * @version 0.1
 * @date 2021-12-23
 * @author Alexis REVOL
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include "structures.h"
#include "outils.h"

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

// Récupérer des identifiants
int *get_client_id(int socketClient, char *title);

// Récupérer le status de départ du round
int get_round_status(int socketClient);

// Recuperer les informations du round (resultats J1 et J2 + n° du round)
Round get_round(int socketClient, Game game);

// Envoyer le status du joueur pour qu'il soit ajouté dans une nouvelle partie
void send_player_status(int socketClient, Joueur player);

// On récupère l'identifiant du gagnant
int get_winner(int socket);

#endif