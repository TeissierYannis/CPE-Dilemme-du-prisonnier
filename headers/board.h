/**
 * @file board.h 
 * @brief Plateau de jeu (fabrication des outils pour jouer)
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <gtk/gtk.h>


#ifndef BOARD_H
#define BOARD_H

// Contient les élements pour fabriquer le jeu
typedef struct {
    GtkWidget *window;
    GtkWidget *fixed1;
    GtkWidget *trahison;
    GtkWidget *collaboration;
    GtkWidget *quitter;
    GtkWidget *rounde;
    GtkWidget *titre;
    GtkWidget *score1;
    GtkWidget *score2;
    GtkBuilder *builder;
    GtkWidget *choix_adversaire;
    GtkWidget *rejouer;
    GtkWidget *label_rejouer;
    GtkWidget *info;
 //   GtkWidget *winner;
    // Les images
    GtkWidget *image_gagner;
    GtkWidget *image_perdu;
    // Les messages de fin de partie (supprimer winner)
    GtkWidget *perdu;
    GtkWidget *gagner;
    GtkWidget *egalite;
    // Compte à rebours de la partie
    GtkWidget *chrono;
} Tools;


// Les outils de création du jeu sont globals pour que le jeu (GUI) et la communication (client)
// y accède
extern Tools tools;

// Créer l'interface graphique
void createBoard(int argc, char **argv);

#endif