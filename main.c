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
GtkWidget *rounde;
GtkWidget *titre;
GtkWidget *score1;
GtkWidget *score2;
GtkBuilder *builder;

void afficher_result();
void create_link();
Bool are_equals(const char*,char*);
void on_clicked_choice();
void afficher_score();
void afficher_round();
void on_quitter_clicked();


void create_link()
{
    lien.choix = -1;
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
    //gtk_label_set_text(GTK_LABEL(rounde), message);
    if (are_equals(message, "Trahison"))
    {
        lien.choix = 0;
        lien.is_choice_ok = true;
        afficher_result();
        //gtk_label_set_text(GTK_LABEL(rounde), "0");
    }
    else if (are_equals(message, "Collaboration"))
    {
        lien.choix = 1;
        lien.is_choice_ok = true;
        afficher_result();
        //gtk_label_set_text(GTK_LABEL(rounde), "1");
    }
}

void afficher_score()
{
    char score_j1[100] ;
    char score_j2[100];
    sprintf(score_j1, "%d",lien.score_j1);
    sprintf(score_j2, "%d",lien.score_j2);
   // char j1 = lien.score_j1 + '0';
   // char j2 = lien.score_j2 + '0';
  //  strncat(score_j1, &j1, 1);
  //  strncat(score_j2, &j2, 1);
    gtk_label_set_text(GTK_LABEL(score1), score_j1);
    gtk_label_set_text(GTK_LABEL(score2), score_j2);
}

void afficher_round(){
    char nb_round[10];

    
    sprintf(nb_round, "%d",lien.nb_round);

    gtk_label_set_text(GTK_LABEL(rounde), nb_round);
}

void afficher_result(){
    while (lien.is_answer_ok != true)
    {
        sleep(1);
    }
    afficher_round();
    afficher_score();
}

void on_quitter_clicked()
{
    gtk_main_quit();
}