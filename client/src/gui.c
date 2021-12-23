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

    printf("Clique autorisé !\n ");
    // Prévoir le prochain round
    lien.able_click = 0;

    // Récuperer nom du bouton cliqué
    const char *message = gtk_button_get_label(b);

    printf("[GUI] choice : %s\n", message);

    // Si on a cliqué sur Trahison
    if (are_equals(message, "Trahison")) {
        // Valeur du choix  = 0
        lien.choix_j1 = 0;
        lien.is_choice_ok = true; // indiqquer que le joueur a fait son choix
        // Afficher resultat du round
        //  afficher_result();
    }
        // Si on a cliqué sur collaboré
    else if (are_equals(message, "Collaboration")) {
        // Valeur du choix  = 1
        lien.choix_j1 = 1;
        lien.is_choice_ok = true; // indiquer que le joueur a fait son choix
        // Afficher resultat du round
    //    afficher_result();
    }
    pthread_exit(0);
}

// Lors d'un clic sur bouton
void on_clicked_choice(GtkButton *b) {
     // Si le clique est autorisé
    if(lien.able_click == 1){
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
    
}


void new_party(void *boutton){
    GtkButton *b;
    // Lire les parametres du client
    b = (GtkButton *) boutton;
    
    // Si le choix est rejouer on raffrait les informations de partie en réinitialisant
    // Mettre une fonction pour initialiser tout ça automatiquement au depart ?
    gtk_label_set_text(GTK_LABEL(tools.score1), 0);
    gtk_label_set_text(GTK_LABEL(tools.score2), 0);
    gtk_label_set_text(GTK_LABEL(tools.rounde), 0);
    gtk_label_set_text(GTK_LABEL(tools.choix_adversaire), "");
    gtk_label_set_text(GTK_LABEL(tools.chrono), "");
    
    gtk_label_set_text(GTK_LABEL(tools.info), "Chargement de la partie...");

    // On remontre les boutons de jeu et cache les boutons pour rejouer
    gtk_widget_hide(tools.rejouer);
    gtk_widget_hide(tools.label_rejouer);
    gtk_widget_hide(tools.gagner);
    gtk_widget_hide(tools.perdu);
    gtk_widget_hide(tools.egalite);

    gtk_widget_hide(tools.image_gagner);
    gtk_widget_hide(tools.image_perdu);

    gtk_widget_show(tools.trahison);
    gtk_widget_show(tools.collaboration);
   // gtk_widget_show(tools.choix_adversaire);
   // gtk_widget_show(tools.score1);
   // gtk_widget_show(tools.score2);


    printf("[GUI] New game en approche\n");

    pthread_exit(0);

}

// Lors d'un clic sur bouton REJOUER
void on_restart_click(GtkButton *b){
    printf("RESTART CLIQUE\n");
     
    // Lancer l'affichage du clique sous forme de thread pour ne pas bloquer GTK
    // En ayant le monopole de l'utilisation ici
    pthread_t threadRestart;
    int result = 0;
    result = pthread_create(&threadRestart, NULL, new_party, (void *) b);
    pthread_detach(threadRestart);
    printf("Apres thread restart \n");
    if (result) {
        printf("ERROR; return code from pthread_create() Restart is %d\n", result);
        exit(-1);
    }
    // Indiquer qu'il souhaite rejouer
    lien.restart_choice = true;
    // Indiquer que le joueur a fait son choix
    lien.is_restart_clicked = true;
}

// Quitter la partie (INDIQUER AU SERVEUR QUE LE JOUEUR EST PARTI)
void on_quitter_clicked() {
    printf("[GUI] Leaving GUI\n");
    lien.restart_choice = false;
    // Indiquer que le joueur a fait son choix
    lien.is_restart_clicked = true;
    gtk_main_quit();
}
