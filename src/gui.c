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

Bool are_equals(const char *message, char *nom){

    if (strcmp(message, nom) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Créer l'interface graphique
void createGui(int argc, char **argv){ 
    gtk_init(&argc, &argv); // init Gtk
    
    builder = gtk_builder_new_from_file("../glade/glade.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    trahison = GTK_WIDGET(gtk_builder_get_object(builder, "trahison"));
    collaboration = GTK_WIDGET(gtk_builder_get_object(builder, "collaboration"));
    quitter = GTK_WIDGET(gtk_builder_get_object(builder, "quitter"));
    rounde = GTK_WIDGET(gtk_builder_get_object(builder, "rounde"));
    titre = GTK_WIDGET(gtk_builder_get_object(builder, "titre"));
    score1 = GTK_WIDGET(gtk_builder_get_object(builder, "score1"));
    score2 = GTK_WIDGET(gtk_builder_get_object(builder, "score2"));
    
    printf("GUI OK\n");
    gtk_widget_show(window);
    gtk_main();
}

// Lors d'un clic sur bouton
void on_clicked_choice(GtkButton *b)
{
    // Récuperer nom du bouton cliqué
    const char *message = gtk_button_get_label(b);
    // Si on a cliqué sur Trahison
    if (are_equals(message, "Trahison"))
    {
        // Valeur du choix  = 0
        lien.choix = 0;
        lien.is_choice_ok = true; // indiquer que le joueur a fait son choix
        // Afficher resultat du round
        afficher_result();
    }
    // Si on a cliqué sur collaboré
    else if (are_equals(message, "Collaboration"))
    {
        // Valeur du choix  = 1
        lien.choix = 1;
        lien.is_choice_ok = true; // indiquer que le joueur a fait son choix
        // Afficher resultat du round
        afficher_result();
    }
}

// Afficher informations score des joueurs
void afficher_score()
{
    char score_j1[100] ;
    char score_j2[100];
    // Placer entier dans chaine caractere
    sprintf(score_j1, "%d",lien.score_j1);
    sprintf(score_j2, "%d",lien.score_j2);
    // Afficher score des 2 joueurs
    gtk_label_set_text(GTK_LABEL(score1), score_j1);
    gtk_label_set_text(GTK_LABEL(score2), score_j2);
}

// Afficher informations du round
void afficher_round(){
    char nb_round[10];
    // Placer int dans une chaine de caracteres
    sprintf(nb_round, "%d",lien.nb_round);
    printf("numero round GUI = %d\n", lien.nb_round);
    // Mettre le numero du round dans son label
    gtk_label_set_text(GTK_LABEL(rounde), nb_round);
}

// Afficher resultat du round
void afficher_result(){
    // Tant qu'on a pas les resultats du round on attend
    while (lien.is_answer_ok != true)
    {
        sleep(0.3);
        printf("Pas de réponse\n");
    }
    // Afficher informations round
    afficher_round();
    // Afficher informations score
    afficher_score();
    // On passe la reponse suivante a faux pour commencer nouveau round
    lien.is_answer_ok = false;
}

// Quitter la partie
void on_quitter_clicked()
{
    gtk_main_quit();
}
