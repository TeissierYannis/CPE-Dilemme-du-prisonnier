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
    int id;
    char *status;

    /***** a supprimer***/
    int score;
    char nom[30];
    bool connected;
    int choix;
} Joueur;

// Contient les informations de la partie
typedef struct {
    int player_id;
    int id;
} Game;

// Contient les informations avec reponses du clients
typedef struct {
    Game game;
    int choice;
    int time;
} Answer;


// Contient les informations du round
typedef struct {
    // Resultat de chaque joueur
    int J1_result;
    int J2_result;
    // Numero du round
    char *number;
} Round;

// Récapitule la partie
typedef struct {
    // Contient la liste des reponses de chaque joueur
    Answer list_answer_J1[100];
    Answer list_answer_J2[100];
    Joueur J1;
    Joueur J2;
} Recap;

// Se connecte au serveur et retourne la socket client
int client_connexion();
// Envoyer des données au serveur
void send_answer(int socketClient, Game game);
// On ferme le client
void client_fermer(int * socketClient, Joueur player);
// Deconnecter le joueur
void disconnect_player(int socketClient, Joueur player);
// Afficher les informations du joueur
void display_player(Joueur player);
// Creer une socket client
int create_socket();
// Recevoir id du joueur pour initialiser le joueur
int client_recevoir_id(int socketClient);
// Initialiser le joueur lorsqu'il reçoit un id
Joueur initialise_player(int socketClient);
// Indiquer le début de la partie avec un identifiant
Game create_game(int socketClient, Joueur player);
// Recupérer le choix du joueur
Answer get_answer(Game game);
// Recuperer les informations du round
Round get_round(int socket);
// Permet de jouer en communicant avec le serveur
void jouer(int socket, Game game);
// Indique si la partie est fini ou continue
bool game_end(Round round);
// Récaptiluer la partie
void game_recap(int socketClient);
// Recuperer la structure qui recaptilue la partie
Recap get_recap(int socketClient);
// Afficher la recapitulation de la partie
void print_recap(Answer *answer);

// Creer structure adresse serveur
struct sockaddr_in create_serv_adrr();

// Recuperer le numero du carre cliqué
int get_clique();
// Recuperer le temps que le joueur a pris pour faire un choix
int get_time_clique();
#endif