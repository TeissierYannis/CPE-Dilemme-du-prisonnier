/**
 * @file affichage.h 
 * @brief Affichage informations sur GUI
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
*/
#include "lien.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void afficher_score(int score_j1, int score_j2);
void afficher_temps_jeux(int temps_j1, int temps_j2);
void afficher_round(int numero);
void afficher_choix_adversaire(int choix_j1, int choix_j2);
void afficher_result(ResultRound result);
void show_restart_button();
void show_end_game();
void show_win();
void show_loose();
void show_egality();


#endif