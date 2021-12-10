/**
 * @file lien.h 
 * @brief Interface Graphique Utilisateur
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef LIEN_H
#define LIEN_H


// Contient les informations d'un Joueur
typedef struct{
    int choix_j1;
    int choix_j2;
    int score_j1;
    int score_j2;
    int nb_round;
    bool is_choice_ok;
    bool is_answer_ok;
    bool is_game_end;
    int le_gagnant;
} Lien;

extern Lien lien;



#endif