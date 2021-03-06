/**
 * @file board.c
 * @author SAGLAMER Tarik (tarik.saglamer@cpe.fr)
 * @brief
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "../headers/board.h"

Tools tools;

/**
 * @brief Créer l'interface graphique
 * @param argc
 * @param argv
 */
void createBoard(int argc, char **argv)
{
  gtk_init(&argc, &argv); // init Gtk
  // Outils principaux
  tools.builder = gtk_builder_new_from_file("./client_config/glade.glade");
  tools.window = GTK_WIDGET(gtk_builder_get_object(tools.builder, "window"));
  gtk_builder_connect_signals(tools.builder, NULL);

  // Création des élements de jeu
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
  // Informations sur la communication client / serveur
  tools.info = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Info"));
  //  tools.winner = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Winner"));
  tools.image_gagner = GTK_WIDGET(gtk_builder_get_object(tools.builder, "image_gagner"));
  tools.image_perdu = GTK_WIDGET(gtk_builder_get_object(tools.builder, "image_perdu"));
  tools.gagner = GTK_WIDGET(gtk_builder_get_object(tools.builder, "gagner"));
  tools.perdu = GTK_WIDGET(gtk_builder_get_object(tools.builder, "perdu"));
  tools.egalite = GTK_WIDGET(gtk_builder_get_object(tools.builder, "egalite"));
  // Compte à rebours d'un round
  tools.chrono = GTK_WIDGET(gtk_builder_get_object(tools.builder, "label_sec"));
  // Temps de jeux
  tools.time_1 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Temps_j1"));
  tools.time_2 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Temps_j2"));
  tools.temps_j1 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Time_1"));
  tools.temps_j2 = GTK_WIDGET(gtk_builder_get_object(tools.builder, "Time_2"));
  // Informations sur la partie à afficher
  gtk_label_set_text(GTK_LABEL(tools.info), "Chargement de la partie...");
  printf("GUI OK\n");
  gtk_widget_show(tools.window);
  gtk_main();
}
