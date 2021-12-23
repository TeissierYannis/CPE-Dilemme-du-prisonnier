/**
 * @file client.h
 * @author REVOL Alexis 
 * @brief Ensemble des actions possibles par le client
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
#include "structures.h"

#ifndef CLIENT_H
#define CLIENT_H

// Programme principal du client
void startGame(void *param);

// Envoyer des données au serveur
void send_answer(int socketClient, Game game);



// Initialiser le joueur lorsqu'il reçoit un id
Joueur create_player(int socketClient);
// Indiquer le début de la partie avec un identifiant
Game create_game(int socketClient, Joueur player);
// Recupérer le choix du joueur
Answer get_answer(Game game);

// Permet de jouer en communicant avec le serveur
void jouer(int socket, Game game);
// Indique si la partie est fini ou continue
int game_end(Round round);


// Relancer une partie
int restart_game(int socketClient, Joueur player);

// Créer le round de depart
Round create_round(int socketClient);
// Afficher le résultat du round
void show_round_result(Round round, Game game);

// Recuperer le numero du carre cliqué
int get_clique();

// Recuperer le choix si le joueur relance ou pas une partie
bool continue_game();

// Recuppérer le gagnant de la partie
int get_winner(int socket);
// Indiquer si la partie est gagnée ou perdue
bool is_game_win(Game game, int winner);
// Afficher le gagnant de la partie
void set_winner_name(int socket, Game game);

// On ferme le client
void client_fermer(int * socketClient, Joueur player);

// Indiquer si un identifiant est valide ou non
bool is_id_valide(int id);



#endif