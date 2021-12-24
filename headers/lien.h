/**
 * @file lien.h 
 * @brief Canal qui fait le lien entre les évenements de clic et la communication client
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef LIEN_H
#define LIEN_H

/**
 * @brief Lien entre les évenements clic et la communication client
 */
typedef struct{
    int able_click;
    int choice;
    bool is_choice_ok; // choix du joueur Fait / en Attente
   
    bool restart_choice; // choix de find de partie Recommencer / Quitter
    bool is_restart_clicked; // choix du joueur de fin de partie Fait / en Attente
    bool is_winner;
} Lien;

/**
 * @brief Résultats à afficher
 */
typedef struct {
    int choix_j1;
    int choix_j2;
    int score_j1;
    int score_j2;
    int temps_j1;
    int temps_j2;
    int nb_round;
} ResultRound;

// Lien global entre GUI et Socket contenant les informations sur le jeu
extern Lien lien;

// Creer le lien entre GUI et communication Socket
void create_link();


#endif