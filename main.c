#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

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

void on_trahison_clicked(GtkButton *b)
{
    char *numeroRound = "oui";
    gtk_label_set_text(GTK_LABEL(rounde), numeroRound);
}

int main(int argc, char **argv)
{
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
    g_signal_connect(G_OBJECT(trahison), "clicked", G_CALLBACK(on_trahison_clicked), NULL);

    gtk_widget_show(window);
    gtk_main();
    return (EXIT_SUCCESS);
}



void on_collaboration_clicked() {}

void on_quitter_clicked()
{
    gtk_main_quit();
}