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

void create_link();

// Creer le lien entre GUI et communication Socket
void create_link(){
    lien.choix_j1 = -1;
    lien.choix_j2 = -1;
    lien.score_j1 = 0;
    lien.score_j2 = 0;
    lien.nb_round = 0;
    lien.is_answer_ok = false;
    lien.is_choice_ok = false;
    lien.is_game_end = false;
    lien.restart_choice = false;
}

int main(int argc, char **argv)
{
    // Creation du lien entre GUI et communication SOCKET
    create_link();

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

    // Lancer le GUI pour jouer
    createGui(argc,argv);
 
   return 0;
}





