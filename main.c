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


int main(int argc, char **argv) {
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
   // player = create_player(socket);
    // Ajouter le socket et le joueur dans les parametres de la communication client
    clientParam->socket = socket;
  //  clientParam->player = player;

    // Lancer la communication client sous forme de thread
    pthread_t threadClient;
    int result = 0;
    result = pthread_create(&threadClient, NULL, startGame, clientParam);
    pthread_detach(threadClient);
    printf("Apres thread client \n");
    if (result) {
        printf("ERROR; retuurn code from pthread_create() Client is %d\n", result);
        exit(-1);
    }

    // Lancer le GUI pour jouer
    createGui(argc, argv);
    free(clientParam);
    return 0;
}





