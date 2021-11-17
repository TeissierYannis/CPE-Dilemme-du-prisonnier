#include <stdlib.h>
#include <stdio.h>

#include "headers/client.h"
#include "src/client.c"

int main(int argc, char **argv)
{
    // Contient les informations du joueur
    Joueur player;
    // Sert a la communication
    int socket;
    // Contient les informations de la partie
    Game game;

    // Connexion au serveur et création de la socket client (sert à la communication)
    socket = client_connexion();
    // Creation du joueur avec son identifiant
    player = initialise_player(socket);
    // Creation de la partie avec son identifiant et l'id du joueur (possible lorsque 2 joueurs co sur le serveur)
    game = create_game(socket, player);

    // Jouer a la partie
    jouer(socket, game);

    // Recapituler la partie
    game_recap(socket);

    // Continuer à jouer ou quitter ?

    // Fermer le client
    client_fermer(&socket, player);

    return 0;
}