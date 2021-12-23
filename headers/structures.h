/**
 * @file structures.h 
 * @brief Les structures manipulées par le client
 * @version 0.1
 * @date 2021-12-23
 * @author Alexis REVOL
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#ifndef STRUCTURES_H
#define STRUCTURES_H


/**
 * @brief Contient le message a envoyé ou à recevoir par le serveur
 */
typedef struct{
    char out[256];
} Buffer_out;

/**
 * @brief Contient les informations d'un Joueur
 */
typedef struct{
    int id;
    char status[255];
    int local_id;
} Joueur;

/**
 * @brief Contient les informations de la partie
 */
typedef struct {
    Joueur player;
    int id;
} Game;

/**
 * @brief Contient les informations des actions du clients
 */
typedef struct {
    int party_id;
    int player_id;
    int choice;
    int time;
} Answer;

/**
 * @brief Contient les informations du round
 */
typedef struct {
    // Resultat de chaque joueur
    int p1_result; // choix
    int p1_wallet; // score
    int p2_result; // choix
    int p2_wallet; // score
    // Le temps
    int p1_decision_time;
    int p2_decision_time;
    // Numero du round
    int round_number;
    int status;
} Round;

/**
 * @brief Contient les informations d'un Joueur
 */
typedef struct{
    int socket;
  //  Joueur player;
} ClientParameter;

#endif