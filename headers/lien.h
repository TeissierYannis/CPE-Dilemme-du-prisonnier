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
    int choix;
    int score;
    bool is_choice_ok;
    bool is_answer_ok;
} Lien;

extern Lien lien;



#endif