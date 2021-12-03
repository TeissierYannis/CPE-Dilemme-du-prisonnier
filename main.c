#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "headers/lien.h"

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *trahison;
GtkWidget *collaboration;
GtkWidget *quitter;
GtkWidget *choix_adversaire;
GtkWidget *rounde;
GtkWidget *titre;
GtkWidget *score1;
GtkWidget *score2;
GtkBuilder *builder;

void afficher_result();
void create_link();
Bool are_equals(const char *, char *);
void on_clicked_choice(GtkButton *);
void afficher_score();
void afficher_round();
void on_quitter_clicked();
void afficher_choix_adversaire();

void create_link()
{
    lien.choix_j1 = -1;
    lien.choix_j2 = 0;
    lien.score_j1 = 0;
    lien.score_j2 = 0;
    lien.nb_round = 0;
    lien.is_answer_ok = true;
    lien.is_choice_ok = false;
}

int main(int argc, char **argv)
{
    create_link();
    gtk_init(&argc, &argv); // init Gtk
    builder = gtk_builder_new_from_file("../glade/glade.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    trahison = GTK_WIDGET(gtk_builder_get_object(builder, "trahison"));
    collaboration = GTK_WIDGET(gtk_builder_get_object(builder, "collaboration"));
    quitter = GTK_WIDGET(gtk_builder_get_object(builder, "quitter"));
    choix_adversaire = GTK_WIDGET(gtk_builder_get_object(builder, "choix_adversaire"));
    rounde = GTK_WIDGET(gtk_builder_get_object(builder, "rounde"));
    titre = GTK_WIDGET(gtk_builder_get_object(builder, "titre"));
    score1 = GTK_WIDGET(gtk_builder_get_object(builder, "score1"));
    score2 = GTK_WIDGET(gtk_builder_get_object(builder, "score2"));
    //g_signal_connect(G_OBJECT(trahison), "clicked", G_CALLBACK(on_trahison_clicked), NULL);

    gtk_widget_show(window);
    gtk_main();
    return (EXIT_SUCCESS);
}

Bool are_equals(const char *message, char *nom)
{

    if (strcmp(message, nom) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void on_clicked_choice(GtkButton *b)
{
    const char *message = gtk_button_get_label(b);
    if (are_equals(message, "Trahison"))
    {
        lien.choix_j1 = 0;
        lien.is_choice_ok = true;
        afficher_result();
    }
    else if (are_equals(message, "Collaboration"))
    {
        lien.choix_j1 = 1;
        lien.is_choice_ok = true;
        afficher_result();
    }
}

void afficher_choix_adversaire()
{
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

void afficher_score()
{
    char score_j1[100];
    char score_j2[100];
    sprintf(score_j1, "%d", lien.score_j1);
    sprintf(score_j2, "%d", lien.score_j2);
    gtk_label_set_text(GTK_LABEL(score1), score_j1);
    gtk_label_set_text(GTK_LABEL(score2), score_j2);
}

void afficher_round()
{
    char nb_round[10];

    sprintf(nb_round, "%d", lien.nb_round);

    gtk_label_set_text(GTK_LABEL(rounde), nb_round);
}

void afficher_result()
{
    while (lien.is_answer_ok != true)
    {
        sleep(1);
    }
    afficher_round();
    afficher_score();
    afficher_choix_adversaire();
}

void on_quitter_clicked()
{
    gtk_main_quit();
}