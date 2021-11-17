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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

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
// Afficher les informations du joueur
void display_player(Joueur player);
// Creer une socket client
int create_socket();

// Creer structure adresse serveur
struct sockaddr_in create_serv_adrr();
#endif