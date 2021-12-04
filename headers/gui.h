/**
 * @file gui.h 
 * @brief Interface Graphique Utilisateur
 * @version 0.1
 * @date 2021-11-27
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

// Le lien entre GUI et socket client
//#include "lien.h"

#ifndef GUI_H
#define GUI_H


// Contient les informations d'un Joueur
typedef struct{
    int argc;
    char **argv;
} GuiParameter;

// Créer l'interface graphique
void createGui(int argc, char **argv);
//void createGui(int argc, char **argv);
// Action lors d'un clic

Bool are_equals(const char*,char*);
void on_clicked_choice(GtkButton *);
void afficher_score();
void afficher_round();
void result();
void on_quitter_clicked();

#endif