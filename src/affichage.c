#include <stdbool.h>
#include "../headers/affichage.h"
#include "../headers/lien.h"

// Afficher informations score des joueurs
void afficher_score() {
    char score_j1[100];
    char score_j2[100];
    // Placer entier dans chaine caractere
    sprintf(score_j1, "%d", lien.score_j1);
    sprintf(score_j2, "%d", lien.score_j2);
    // Afficher score des 2 joueurs
    gtk_label_set_text(GTK_LABEL(tools.score1), score_j1);
    gtk_label_set_text(GTK_LABEL(tools.score2), score_j2);
}

// Afficher informations du round
void afficher_round() {
    char nb_round[10];
    // Placer int dans une chaine de caracteres
    sprintf(nb_round, "%d", lien.nb_round);
    printf("numero round GUI = %d\n", lien.nb_round);
    // Mettre le numero du round dans son label
    gtk_label_set_text(GTK_LABEL(tools.rounde), nb_round);
}

void afficher_choix_adversaire() {
    char* my_choice;
    char *ad_choice;
    char message[100];
    // Choix adversaire
    if (lien.choix_j2 == 0)
    {
        ad_choice = "trahi";
      //  strcpy(ad_choice, "trahi"); // Meme chose que ad_choice = "trahi"
    }
    else if (lien.choix_j2 == 1)
    {
        ad_choice = "collaborés";
        //(ad_choice, "collaboré"); // Meme chose que ad_choice = "collaboré"
    }

    // Mon choix
    if (lien.choix_j1 == 0)
    {
            my_choice = "trahi";
    //    strcpy(my_choice, "trahi"); // Meme chose que ad_choice = "trahi"
    }
    else if (lien.choix_j1 == 1)
    {
            my_choice = "collaboré";
      //  strcpy(my_choice, "collaboré"); // Meme chose que ad_choice = "collaboré"
    }
    // Phrase a afficher
    sprintf(message, "Vous avez %s et l'adevrse vous a %s",my_choice, ad_choice);
    // Affichage
    gtk_label_set_text(GTK_LABEL(tools.choix_adversaire), message);
}


// Afficher resultat du round
void afficher_result() {
    // Afficher informations round
    afficher_round();
    // Afficher informations score
    afficher_score();
    // Afficher informations sur le choix de l'adversaire
    afficher_choix_adversaire();
    
    // On passe le resultat suivant a faux pour commencer nouveau round
    lien.is_answer_ok = false;
}

// Lorsque la partie est finie
void show_end_game(){
    gtk_label_set_text(GTK_LABEL(tools.info), "Fin de la partie...");
    // Montrer le bouton pour recommencer une partie
    show_restart_button();
    show_winner();
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

// Lors d'un clic sur bouton REJOUER
void on_restart_click(GtkButton *b) {
    // Indiquer qu'il souhaite rejouer
    lien.restart_choice = true;
    // Indiquer que le joueur a fait son choix
    lien.is_restart_clicked = true;
    // Si le choix est rejouer on raffrait les informations de partie en réinitialisant
    // Mettre une fonction pour initialiser tout ça automatiquement au depart ?
    gtk_label_set_text(GTK_LABEL(tools.score1), 0);
    gtk_label_set_text(GTK_LABEL(tools.score2), 0);
    gtk_label_set_text(GTK_LABEL(tools.choix_adversaire), "");
    // On remontre les boutons de jeu et cache les boutons pour rejouer
    gtk_widget_hide(tools.rejouer);
    gtk_widget_hide(tools.label_rejouer);
    gtk_widget_show(tools.trahison);
    gtk_widget_show(tools.collaboration);
   // gtk_widget_show(tools.choix_adversaire);
   // gtk_widget_show(tools.score1);
   // gtk_widget_show(tools.score2);

    printf("[GUI] Restart game\n");
}

// Afficher le gagnant
void show_winner(){
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

}