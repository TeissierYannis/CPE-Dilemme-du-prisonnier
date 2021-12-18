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

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void afficher_score();
void afficher_round();
void afficher_choix_adversaire();
void afficher_result();
void show_restart_button();
void show_winner();
void show_end_game();



#endif