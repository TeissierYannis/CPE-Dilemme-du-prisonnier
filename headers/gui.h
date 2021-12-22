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

void result();
void on_quitter_clicked();
void choice_clicked(void *param);

void on_restart_click(GtkButton *b);
void new_party(void *boutton);

#endif