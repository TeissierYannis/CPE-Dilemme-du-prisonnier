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

#include "board.h"

#ifndef CLIENT_H
#define CLIENT_H


// Test debug
typedef struct{
    char out[256];
} Buffer_out;

// Contient les informations d'un Joueur
typedef struct{
    int id;
    char status[255];
    int local_id;
} Joueur;

// Contient les informations de la partie
typedef struct {
    Joueur player;
    int id;
} Game;

// Contient les informations avec reponses du clients
typedef struct {
    int party_id;
    int player_id;
    int choice;
    int time;
} Answer;


// Contient les informations du round
typedef struct {
    // Resultat de chaque joueur
    int p1_result; // choix
    int p1_wallet; // score
    int p2_result; // choix
    int p2_wallet; // score
    // Le temps
    int p1_decision_time;
    int p2_decision_time;
  //  int p2_choice;
    // Numero du round
    int round_number;
    int status;
} Round;

// Récapitule la partie
typedef struct {
    // Contient la liste des reponses de chaque joueur
    int nb_round;
    Answer list_answer_J1[10];
    Answer list_answer_J2[10];
} Recap;

// Contient les informations d'un Joueur
typedef struct{
    int socket;
  //  Joueur player;
} ClientParameter;


// Programme principal du client
void startGame(void *param);
// Se connecte au serveur et retourne la socket client
int client_connexion();
// Envoyer des données au serveur
void send_answer(int socketClient, Game game);
// On ferme le client
void client_fermer(int * socketClient, Joueur player);
// Deconnecter le joueur
void disconnect_player(int socketClient, Joueur player);
// Creer une socket client
int create_socket();
// Recevoir un identifiant (du joueur ou de la partie selon le choix)
int* client_recevoir_id(int socketClient, char *title);
// Initialiser le joueur lorsqu'il reçoit un id
Joueur create_player(int socketClient);
// Indiquer le début de la partie avec un identifiant
Game create_game(int socketClient, Joueur player);
// Recupérer le choix du joueur
Answer get_answer(Game game);
// Recuperer les informations du round
Round get_round(int socket, Game game);
// Permet de jouer en communicant avec le serveur
void jouer(int socket, Game game);
// Indique si la partie est fini ou continue
int game_end(Round round);
// Récaptiluer la partie
void game_recap(int socketClient);
// Recuperer la structure qui recaptilue la partie
Recap get_recap(int socketClient);
// Afficher la recapitulation de la partie
void print_recap(Answer answer[], int length);

// Relancer une partie
int restart_game(int socketClient, Joueur player);
// Envoyer le status du joueur pour qu'il soit ajouté dans une nouvelle partie
void send_player_status(int socketClient, Joueur player);

// Creer structure adresse serveur
struct sockaddr_in create_serv_adrr();

// Récupérer le status de départ du round
int get_round_status(int socketClient);
// Créer le round de depart
Round create_round(int socketClient);
// Afficher le résultat du round
void show_round_result(Round round, Game game);

// Recuperer le numero du carre cliqué
int get_clique();
// Recuperer le temps que le joueur a pris pour faire un choix
int get_time_clique();
// Recuperer le choix si le joueur relance ou pas une partie
bool continue_game();

// Comparer 2 chaine de caracteres
bool are_equal(char *a, char *b);
// Indiquer si un identifiant est valide ou non
bool is_id_valide(int id);
// Recuppérer le gagnant de la partie
int get_winner(int socket);
// Indiquer si la partie est gagnée ou perdue
bool is_game_win(Game game, int winner);
// Afficher le gagnant de la partie
void set_winner_name(int socket, Game game);
// Compte à rebours du temps de jeu
void start_countdown();
void countdown(void *param);

#endif