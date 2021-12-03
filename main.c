#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <pthread.h>

#include "headers/client.h"
#include "headers/gui.h"
#include "headers/lien.h"

/*GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *trahison;
GtkWidget *collaboration;
GtkWidget *quitter;
GtkWidget *rounde;
GtkWidget *titre;
GtkWidget *score1;
GtkWidget *score2;
GtkBuilder *builder;*/





int main(int argc, char **argv)
{
    lien.choix = -1;
    lien.score = -1;
    lien.is_choice_ok = false;
    lien.is_answer_ok = false;

   // createGui(argc, argv);
    // Contient les parametres de la communication Client
    ClientParameter *clientParam;
    clientParam = malloc(sizeof(ClientParameter));

    // Contient les informations du joueur
    Joueur player;
    // Sert a la communication
    int socket;

    // Connexion au serveur et création de la socket client (sert à la communication)
    socket = client_connexion();
    // Creation du joueur avec son identifiant
    player = create_player(socket);
    // Ajouter le socket et le joueur dans les parametres de la communication client
    clientParam->socket = socket;
    clientParam->player = player;

    
    // Lancer la communication client sous forme de thread
    pthread_t threadClient;
    int result = 0;
    result = pthread_create(&threadClient, NULL, startGame,(void *) clientParam);
   // pthread_join(threadClient, NULL);
    printf("Apres thread client \n");
    if (result){
        printf("ERROR; return code from pthread_create() Client is %d\n", result);
        exit(-1);
    }

   // Lancer le gui sous forme de thread
    GuiParameter *guiParam;
    guiParam = malloc(sizeof(GuiParameter));
    guiParam->argc = argc;
    guiParam->argv = argv;

    pthread_t threads;
    int res = 0;
    res = pthread_create(&threads, NULL, createGui,(void *) guiParam);
    pthread_join(threads, NULL); // Le programme se fermera lorsque le joueur fermera l'interface
    printf("Apres thread GUI \n");
    if (res){
        printf("ERROR; return code from pthread_create() GUI is %d\n", res);
        exit(-1);
    } 

 
   return 0;
}





