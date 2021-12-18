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


// Quitter la partie (INDIQUER AU SERVEUR QUE LE JOUEUR EST PARTI)
void on_quitter_clicked() {
    printf("[GUI] Leaving GUI\n");
    lien.restart_choice = false;
    // Indiquer que le joueur a fait son choix
    lien.is_restart_clicked = true;
    gtk_main_quit();
}
