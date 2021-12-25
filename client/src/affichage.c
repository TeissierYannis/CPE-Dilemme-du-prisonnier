/**
 * @file client.c
 * @author SAGLAMER Tarik
 * @brief Affichage des informations sur GUI
 * @version 0.1
 * @date 2021-12-23
 * @copyright Copyright (c) 2021
 */
#include <gtk/gtk.h>
#include "../headers/board.h"
#include "../headers/affichage.h"

/**
 * @brief Afficher informations score des joueurs
 * @param score_1
 * @param score_2
 */
void afficher_score(int score_1, int score_2) {
    char score_j1[100];
    char score_j2[100];
    // Placer entier dans chaine caractere
    sprintf(score_j1, "%d", score_1);
    sprintf(score_j2, "%d", score_2);
    // Afficher score des 2 joueurs
    gtk_label_set_text(GTK_LABEL(tools.score1), score_j1);
    gtk_label_set_text(GTK_LABEL(tools.score2), score_j2);
}

/**
 * @brief Afficher informations temps de jeu
 * @param score_1
 * @param score_2
 */
void afficher_temps_jeux(int time_j1, int time_j2) {
    char temps_j1[100];
    char temps_j2[100];
    // Placer entier dans chaine caractere
    sprintf(temps_j1, "%ds", time_j1);
    sprintf(temps_j2, "%ds", time_j2);
    // Afficher score des 2 joueurs
    gtk_label_set_text(GTK_LABEL(tools.temps_j1), temps_j1);
    gtk_label_set_text(GTK_LABEL(tools.temps_j2), temps_j2);
}

/**
 * @brief Afficher informations du round
 * @param numero
 */
void afficher_round(int numero) {
    char nb_round[10];
    // Placer int dans une chaine de caracteres
    sprintf(nb_round, "%d", numero);
    printf("numero round GUI = %d\n", numero);
    // Mettre le numero du round dans son label
    gtk_label_set_text(GTK_LABEL(tools.rounde), nb_round);
}

/**
 * @brief Afficher les choix effectués par le joueur et l'adversaire
 * @param choix_j1
 * @param choix_j2
 */
void afficher_choix_adversaire(int choix_j1, int choix_j2) {
    char my_choice[20];
    char ad_choice[20];
    char message[100];
    int len;
    // Choix adversaire
    if (choix_j2 == 0)
    {
        strcpy(ad_choice, "trahi");
    }
    else if (choix_j2 == 1)
    {
        strcpy(ad_choice, "collaboré");
    }

    // Mon choix
    if (choix_j1 == 0)
    {
        strcpy(my_choice, "trahi");
    }
    else if (choix_j1 == 1)
    {
        strcpy(my_choice, "collaboré");
    }

    // Phrase a afficher
    sprintf(message, "Vous avez %s et l'adversaire a %s",my_choice, ad_choice);
    // Affichage
    gtk_label_set_text(GTK_LABEL(tools.choix_adversaire), message);
}


/**
 * @brief Afficher resultat du round
 * @param round
 */
void afficher_result(ResultRound round) {
    // Afficher informations round
    afficher_round(round.nb_round);
    // Afficher informations score
    afficher_score(round.score_j1, round.score_j2);
    // Afficher informations sur le choix de l'adversaire
    afficher_choix_adversaire(round.choix_j1, round.choix_j2);
    // Afficher les temps mis pour jouer
    afficher_temps_jeux(round.temps_j1, round.temps_j2);
    // On patiente 3 secondes pour voir les scores avant de commencer un nouveau round 
    gtk_label_set_text(GTK_LABEL(tools.info), "Résultat du round");
    gtk_label_set_text(GTK_LABEL(tools.chrono), "Affichage...");
    sleep(3); // Laisser le temps de voir les resultats avant de commencer nouveau round
}

/**
 * @brief Montrer que la partie est finie
 */
void show_end_game(){
    gtk_label_set_text(GTK_LABEL(tools.info), "Fin de la partie...");
    // Montrer le bouton pour recommencer une partie
    show_restart_button();
}

/**
 * @brief On montre le bouton REJOUER quand la partie est finie
 */
void show_restart_button() {
    // On montre le bouton pour rejouer au joueur
    gtk_widget_show(tools.rejouer);
    gtk_widget_show(tools.label_rejouer);
    gtk_widget_hide(tools.trahison);
    gtk_widget_hide(tools.collaboration);
}

/**
 * @brief On montre que la partie est gagnée
 */
void show_win(){
    gtk_widget_show(tools.gagner);
    gtk_widget_show(tools.image_gagner);
}

/**
 * @brief On montre que la partie est perdue
 */
void show_loose(){
    gtk_widget_show(tools.perdu);
    gtk_widget_show(tools.image_perdu);
}

/**
 * @brief On montre qu'il y a égalité
 */
void show_egality(){
    gtk_widget_show(tools.egalite);
}
