#include <stdbool.h>
#include "../headers/affichage.h"

// Afficher informations score des joueurs
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

// Afficher informations du round
void afficher_round(int numero) {
    char nb_round[10];
    // Placer int dans une chaine de caracteres
    sprintf(nb_round, "%d", numero);
    printf("numero round GUI = %d\n", numero);
    // Mettre le numero du round dans son label
    gtk_label_set_text(GTK_LABEL(tools.rounde), nb_round);
}

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


// Afficher resultat du round
void afficher_result(ResultRound round) {
    // Afficher informations round
    afficher_round(round.nb_round);
    // Afficher informations score
    afficher_score(round.score_j1, round.score_j2);
    // Afficher informations sur le choix de l'adversaire
    afficher_choix_adversaire(round.choix_j1, round.choix_j2);
    
    // On patiente 3 secondes pour voir les scores avant de commencer un nouveau round 
    gtk_label_set_text(GTK_LABEL(tools.info), "Résultat du round");
    gtk_label_set_text(GTK_LABEL(tools.chrono), "Affichage...");
    sleep(3); // Laisser le temps de voir les resultats avant de commencer nouveau round
}

// Lorsque la partie est finie
void show_end_game(){
    gtk_label_set_text(GTK_LABEL(tools.info), "Fin de la partie...");
    // Montrer le bouton pour recommencer une partie
    show_restart_button();
}

// On montre le bouton REJOUER quand la partie est finie
void show_restart_button() {
    // On montre le bouton pour rejouer au joueur
    gtk_widget_show(tools.rejouer);
    gtk_widget_show(tools.label_rejouer);
    gtk_widget_hide(tools.trahison);
    gtk_widget_hide(tools.collaboration);
   // gtk_widget_hide(tools.choix_adversaire);
//    gtk_widget_hide(tools.score1);
  //  gtk_widget_hide(tools.score2);
}



void show_win(){
    gtk_widget_show(tools.gagner);
    gtk_widget_show(tools.image_gagner);
}

void show_loose(){
    gtk_widget_show(tools.perdu);
    gtk_widget_show(tools.image_perdu);
}

void show_egality(){
    gtk_widget_show(tools.egalite);
}

// Afficher le gagnant
/*void show_winner(){
   // char *mssg_win;
    // Si on a gagné
    if(lien.is_winner){
        gtk_widget_show(tools.gagner);
        gtk_widget_show(tools.image_gagner);
      //  mssg_win = "Bravo vous avez gagné !";
    }
    // Si on a perdue
    else{
        
        gtk_widget_show(tools.perdu);
        gtk_widget_show(tools.image_perdu);
    //    mssg_win = "Zut vous avez perdu...";
    }
    // TODO si égalité
    // Message à afficher
   // gtk_label_set_text(GTK_LABEL(tools.winner), mssg_win);
   // gtk_widget_show(tools.winner);

}*/