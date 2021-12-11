#include "../headers/board.h"

Tools tools;

// Créer l'interface graphique
void createBoard(int argc, char **argv) {
    gtk_init(&argc, &argv); // init Gtk

    tools.builder = gtk_builder_new_from_file("../glade/glade.glade");
    tools.window = GTK_WIDGET(gtk_builder_get_object(tools.builder, "window"));
    gtk_builder_connect_signals(tools.builder, NULL);

    tools.fixed1 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "fixed1"));
    tools.trahison = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Trahison"));
    tools.collaboration = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Collaboration"));
    tools.quitter = GTK_WIDGET(gtk_builder_get_object(tools.builder, "quitter"));
    tools.rounde = GTK_WIDGET(gtk_builder_get_object(tools.builder, "rounde"));
    tools.titre = GTK_WIDGET(gtk_builder_get_object(tools.builder, "titre"));
    tools.score1 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "score1"));
    tools.score2 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "score2"));
    tools.choix_adversaire = GTK_WIDGET(gtk_builder_get_object(tools.builder, "choix_adversaire"));
    tools.rejouer = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Rejouer"));
    tools.label_rejouer = GTK_WIDGET(gtk_builder_get_object(tools.builder, "labelRejouer"));
    tools.info = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Info"));
    printf("GUI OK\n");
    gtk_widget_show(tools.window);
    gtk_main();
}
