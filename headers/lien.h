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
#include <stdint.h>

#ifndef LIEN_H
#define LIEN_H


// Contient les informations d'un Joueur
typedef struct{
    int choix_j1;
    int choix_j2;
    int score_j1;
    int score_j2;
    int nb_round;
    
    int is_choice_ok; // choix du joueur Fait / en Attente
    int is_answer_ok; // Resultat du round Reçue / en Attente
    int is_game_end; // Partie terminée Oui / Non
    int restart_choice; // choix de find de partie Recommencer / Quitter
    int is_restart_clicked; // choix du joueur de fin de partie Fait / en Attente
} Lien;

// Lien global entre GUI et Socket contenant les informations sur le jeu
extern Lien lien;

// Creer le lien entre GUI et communication Socket
void create_link();


#endif