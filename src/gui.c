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



// Créer l'interface graphique
void createGui(void* param){
//void createGui(int argc, char **argv){ 
    // Lire les parametres récupérés via le thread
    GuiParameter *gui;
    gui = (GuiParameter *)param;
    int argc = gui->argc;
    char **argv = gui->argv;
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
    gtk_widget_show_all(window);
    gtk_main();
    free(param);
}


void on_button_clicked(GtkButton *b)
{
    int choix;
    char message[50];
    char *mssgScore = "Votre score :";
    strcpy(message, mssgScore);

    // Récupérer texte du bouton
    const char *text = gtk_button_get_label (b);

    // Valeur du message selon bouton cliqué
    if(strcmp(text, "Trahison") == 0){
      //  strcpy(message, "Vous avez trahi !");
        choix = 0;
    }
    else if (strcmp(text, "Collaboration") == 0){
        // strcpy(message, "Vous avez collaboré !");
         choix = 1;
    }

    // On indique que le joueur a fait son choix
    lien.choix = choix;
    lien.is_choice_ok = true;
    printf("Choix OK\n");
    printf("Gui link = %d \n",lien.choix);
    
    // Si le joueur a joué on attent le resultat
    while(lien.is_answer_ok != true){
        sleep(1);
    }
    
    char score = lien.score + '0';
    // Ajouter le score à la fin du message à afficher
    strncat(message, &score, 1);
    // strcpy(message, "Vous avez collaboré !");
    // Afficher le message
    gtk_label_set_text(GTK_LABEL(rounde), message);

    // Afficher le message
    //gtk_label_set_text(GTK_LABEL(rounde), message);
}

void on_collaboration_clicked() {}

void on_quitter_clicked()
{
    gtk_main_quit();
}
