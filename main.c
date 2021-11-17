#include <stdlib.h>
#include <stdio.h>

#include "headers/client.h"
#include "src/client.c"

int main(int argc, char **argv)
{
    // Contient les informations du joueur
    Joueur player;
    int socket;
    // Connexion au serveur et création de la socket client (sert à la communication)
    socket = client_connexion();
    // Recevoir des informations du serveur à propos du joueur
    player = client_recevoir(socket);

    
    player.score = 547;
    // Envoyer des données concernant le joueur au serveur
    client_envoyer(socket, player);

    //player = client_recevoir(socket);

    // Fermer le client
    client_fermer(&socket, player);

    return 0;
}