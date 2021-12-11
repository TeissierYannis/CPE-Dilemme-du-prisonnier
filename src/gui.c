#include <stdbool.h>
#include "../headers/gui.h"
#include "../headers/lien.h"


int are_equals(const char *message, char *nom) {

    if (strcmp(message, nom) == 0) {
        return true;
    } else {
        return false;
    }
}

// Créer l'interface graphique
void createGui(int argc, char **argv) {
    createBoard(argc, argv); // init Gtk
}

// Thread pour afficher les infos sur le jeux
void choice_clicked(void *boutton){
    GtkButton *b;
     // Lire les parametres du client
    b = (GtkButton *) boutton;

    // Si le clique est autorisé
    if(lien.able_click == 1){
        printf("Clique autorisé !\n ");
        // Prévoir le prochain round
        lien.able_click = 0;
    
       // gtk_label_set_text(GTK_LABEL(tools.info), "Vous pouvez jouer !");
        // Récuperer nom du bouton cliqué
        const char *message = gtk_button_get_label(b);

        printf("[GUI] choice : %s\n", message);

        // Si on a cliqué sur Trahison
        if (are_equals(message, "Trahison")) {
            // Valeur du choix  = 0
            lien.choix_j1 = 0;
            lien.is_choice_ok = true; // indiqquer que le joueur a fait son choix
            // Afficher resultat du round
            afficher_result();
        }
            // Si on a cliqué sur collaboré
        else if (are_equals(message, "Collaboration")) {
            // Valeur du choix  = 1
            lien.choix_j1 = 1;
            lien.is_choice_ok = true; // indiquer que le joueur a fait son choix
            // Afficher resultat du round
            afficher_result();
        }
    }
    else if(lien.able_click == 0){
        printf("Attendre pour clique !\n ");
        //gtk_label_set_text(GTK_LABEL(tools.info), "Patientez un peu...");
    }
}

// Lors d'un clic sur bouton
void on_clicked_choice(GtkButton *b) {
    // Lancer l'affichage du clique sous forme de thread pour ne pas bloquer GTK
    // En ayant le monopole de l'utilisation ici
    pthread_t threadClick;
    int result = 0;
    result = pthread_create(&threadClick, NULL, choice_clicked, (void *) b);
    pthread_detach(threadClick);
    printf("Apres thread clique \n");
    if (result) {
        printf("ERROR; return code from pthread_create() Click is %d\n", result);
        exit(-1);
    }

    
}

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
    // Tant qu'on a pas les resultats du round on attend
    while (lien.is_answer_ok != true) {
        sleep(0.3);
    }
    // Afficher informations round
    afficher_round();
    // Afficher informations score
    afficher_score();
    // Afficher informations sur le choix de l'adversaire
    afficher_choix_adversaire();
    // Montrer le bouton pour recommencer une partie
    show_restart_button();
    // On passe la reponse suivante a faux pour commencer nouveau round
    lien.is_answer_ok = false;
}

// On montre le bouton REJOUER quand la partie est finie
void show_restart_button() {
    // Si la partie est finie
    if (lien.is_game_end) {
        // On montre le bouton pour rejouer au joueur
        gtk_widget_show(tools.rejouer);
        gtk_widget_show(tools.label_rejouer);
        gtk_widget_hide(tools.trahison);
        gtk_widget_hide(tools.collaboration);
        gtk_widget_hide(tools.choix_adversaire);
        gtk_widget_hide(tools.score1);
        gtk_widget_hide(tools.score2);
    }
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
    gtk_widget_show(tools.choix_adversaire);
    gtk_widget_show(tools.score1);
    gtk_widget_show(tools.score2);

    printf("[GUI] Restart game\n");
}


// Quitter la partie (INDIQUER AU SERVEUR QUE LE JOUEUR EST PARTI)
void on_quitter_clicked() {
    printf("[GUI] Leaving GUI\n");
    lien.restart_choice = false;
    // Indiquer que le joueur a fait son choix
    lien.is_restart_clicked = true;
    gtk_main_quit();
}
