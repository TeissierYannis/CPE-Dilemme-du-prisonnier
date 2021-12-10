/**
 * @file main.h
 * @author REVOL Alexis 
 * @brief Lancer la communication client et l'interface graphique
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <gtk/gtk.h>
#include <pthread.h>

#include "headers/client.h"
#include "headers/gui.h"
#include "headers/lien.h"
#include "headers/connexion.h"


/**
 * @brief Coeur de la partie client
 * @param arc
 * @param argv
 * @return int
 */
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
   
    // Ajouter le socket et le joueur dans les parametres de la communication client
    clientParam->socket = socket;

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