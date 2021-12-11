/**
 * @file gui.h 
 * @brief Interface Graphique Utilisateur
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "board.h"

#ifndef GUI_H
#define GUI_H

// Créer l'interface graphique
void createGui(int argc, char **argv);
//void createGui(int argc, char **argv);
// Action lors d'un clic

int are_equals(const char*,char*);
void on_clicked_choice(GtkButton *);
void afficher_score();
void afficher_round();
void result();
void on_quitter_clicked();
void afficher_result();
void choice_clicked(void *param);

#endif