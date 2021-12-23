/**
 * @file affichage.h 
 * @brief Affichage informations sur GUI
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
//#include <pthread.h>
#include <stdio.h>
#include "board.h"
#include "lien.h"

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void afficher_score(int score_j1, int score_j2);
void afficher_round(int numero);
void afficher_choix_adversaire(int choix_j1, int choix_j2);
void afficher_result(ResultRound result);
void show_restart_button();
//void show_winner();
void show_end_game();
void show_win();
void show_loose();
void show_egality();


#endif