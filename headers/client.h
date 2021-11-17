/**
 * @file client.h
 * @author REVOL Alexis 
 * @brief Connexion au serveur et réception de données
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef CLIENT_H
#define CLIENT_H

// Contient les informations d'un Joueur
typedef struct{
    int score;
    int choix;
    int id;
    char nom[30];
    bool connected;
} Joueur;

// Se connecte au serveur et retourne la socket client
int client_connexion();
// Reçoit des données par le serveur
Joueur client_recevoir(int socketClient);
// Envoyer des données au serveur
void client_envoyer(int socketClient, Joueur player);
// On ferme le client
void client_fermer(int * socketClient, Joueur player);
// Deconnecter le joueur
void disconnect_player(int socketClient, Joueur player);

#endif