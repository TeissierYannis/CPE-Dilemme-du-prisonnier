#include <stdbool.h>
#include "../headers/gui.h"
#include "../headers/lien.h"

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

int are_equals(const char *message, char *nom) {

    if (strcmp(message, nom) == 0) {
        return true;
    } else {
        return false;
    }
}

// Créer l'interface graphique
void createGui(int argc, char **argv) {
    gtk_init(&argc, &argv); // init Gtk

    builder = gtk_builder_new_from_file("../glade/glade.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    trahison = GTK_WIDGET(gtk_builder_get_object(builder, "Trahison"));
    collaboration = GTK_WIDGET(gtk_builder_get_object(builder, "Collaboration"));
    quitter = GTK_WIDGET(gtk_builder_get_object(builder, "quitter"));
    rounde = GTK_WIDGET(gtk_builder_get_object(builder, "rounde"));
    titre = GTK_WIDGET(gtk_builder_get_object(builder, "titre"));
    score1 = GTK_WIDGET(gtk_builder_get_object(builder, "score1"));
    score2 = GTK_WIDGET(gtk_builder_get_object(builder, "score2"));
    choix_adversaire = GTK_WIDGET(gtk_builder_get_object(builder, "choix_adversaire"));
    rejouer = GTK_WIDGET(gtk_builder_get_object(builder, "Rejouer"));
    label_rejouer = GTK_WIDGET(gtk_builder_get_object(builder, "labelRejouer"));
    info = GTK_WIDGET(gtk_builder_get_object(builder, "Info"));
    printf("GUI OK\n");
    gtk_widget_show(window);
    gtk_main();
}

// Lors d'un clic sur bouton
void on_clicked_choice(GtkButton *b) {
    // Si le clique est autorisé
    if(lien.able_click == 1){
        printf("Clique autorisé !\n ");
        lien.able_click = 0; // bloquer le clique suivant
        gtk_label_set_text(GTK_LABEL(info), "Vous pouvez jouer !");
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
        gtk_label_set_text(GTK_LABEL(info), "Patientez un peu...");
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
    gtk_label_set_text(GTK_LABEL(score1), score_j1);
    gtk_label_set_text(GTK_LABEL(score2), score_j2);
}

// Afficher informations du round
void afficher_round() {
    char nb_round[10];
    // Placer int dans une chaine de caracteres
    sprintf(nb_round, "%d", lien.nb_round);
    printf("numero round GUI = %d\n", lien.nb_round);
    // Mettre le numero du round dans son label
    gtk_label_set_text(GTK_LABEL(rounde), nb_round);
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
    gtk_label_set_text(GTK_LABEL(choix_adversaire), message);
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
        gtk_widget_show(rejouer);
        gtk_widget_show(label_rejouer);
        gtk_widget_hide(trahison);
        gtk_widget_hide(collaboration);
        gtk_widget_hide(choix_adversaire);
        gtk_widget_hide(score1);
        gtk_widget_hide(score2);
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
    gtk_label_set_text(GTK_LABEL(score1), 0);
    gtk_label_set_text(GTK_LABEL(score2), 0);
    gtk_label_set_text(GTK_LABEL(choix_adversaire), "");
    // On remontre les boutons de jeu et cache les boutons pour rejouer
    gtk_widget_hide(rejouer);
    gtk_widget_hide(label_rejouer);
    gtk_widget_show(trahison);
    gtk_widget_show(collaboration);
    gtk_widget_show(choix_adversaire);
    gtk_widget_show(score1);
    gtk_widget_show(score2);

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
