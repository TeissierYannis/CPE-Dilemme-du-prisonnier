/**
 * @file communication.c
 * @author REVOL Alexis (alexis.revol@cpe.fr)
 * @brief
 * @version 0.1
 * @date 2021-23-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // a voir si obligatoire
#include <string.h>
#include "../headers/communication.h"

/**
 * @brief Le client reçoit des identifiants
 * @details Recevoir message du serveur contenant un identifiant et le nom de ce à quoi correspond l'ID
 * (id du joueur, id du rôle, ou id de jeux). \n
 * Le client reçoit une chaîne de caractères contenant le titre de l'identifiant
 * puis un premier ID (id du joueur ou du jeux) et optionnelement un second ID (rôle du joueur)
 * Format de la chaine reçue : \n 
 * Pour ID de jeux : "party 1" \n 
 * Pour ID du joueur et son rôle : "id 1:1" \n
 * Le rôle du joueur peut être 0 -> J1 ou 1 -> J2
 * @return int *
 */
// Le client reçoit un id
int *get_client_id(int socketClient, char *title) {
    char *id;
    int id_int = -1, id_player_local = -1;

    Buffer_out buffer;
    char *key;    // titre du message
    char *separateur = " "; // separateur entre les champs du message
    int verif;
    // Tableau contenant les ID à renvoyer
    int *result = malloc(sizeof(int) * 2);
    
    // Recevoir message du serveur contenant un identifiant et le nom de ce à quoi correspond l'ID
    // (id du joueur ou id de la partie)
    printf("[RECEIVE] Receiving id from server...\n");
    verif = read(socketClient, &buffer, sizeof(Buffer_out));
    
    // Vérifier la réception
    if (verif < 0) {
        perror("[RECEIVE] Error reception ID :");
        close(socketClient);
        exit(EXIT_FAILURE);
    } else {
        printf("[RECEIVE] id received : %s\n", buffer.out);
    }

    // Récupérer le titre de l'identifiant en l'extrayant de la chaine de caracteres
    key = strtok(buffer.out, separateur);

    printf("[RECEIVE] Key received : %s\n", key);
    // Si l'ID correspond au type d'ID demandé on l'enregistre
    if (are_equal(key, title)) {
        // Récuperer la deuxième partie du message (les id) et le convertir en identifiant
        id = strtok(NULL, " ");
        // Si il y a plusieurs ID a récupérer
        if (strstr(id, ":")) {
            // On récupère le premier id
            id_int = atoi(strtok(id, ":"));
            // On récupère le second id
            id_player_local = atoi(strtok(NULL, ":"));
            printf("[RECEIVE] Id received : %d\n", id_int);
            printf("[RECEIVE] Id player local received : %d\n", id_player_local);
        } 
        // Si il n'y a que l'ID de la partie a récupérer
        else {
            id_int = atoi(id);
        }
    }
    // On enregistre les valeurs lues avant de les renvoyer
    result[0] = id_int;
    result[1] = id_player_local;

    return result;
}


/**
 * @brief Récupérer le status de départ du round
 * @details Recevoir message du serveur contenant le status du round, on extrait le status de 
 * la chaine afin de vérifier sa valeur. \n
 * Exemple "status 0" pour un status de départ et "status 1" pour un status de fin
 * @param socketClient
 * @return int
 */
int get_round_status(int socketClient) {
    int status;
    Buffer_out buffer;
    int recevoir;
    printf("Reception status du round...\n");

    // Recevoir le status du round
    recevoir = read(socketClient, &buffer, sizeof(buffer));
    printf("TAILLE LUE = %d\n", recevoir);
    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        perror("Erreur reception status round");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
    // Extraire le status de la chaine reçue
    strtok(buffer.out, " ");
    status = atoi(strtok(NULL, " "));

    printf("round récupéré status : %d\n", status);
    return status;
}

/**
 * @brief Recuperer les informations du round (resultats J1 et J2 + n° du round)
 * @return Round
 */
Round get_round(int socketClient, Game game) {
    Round round;
    int verif;

    printf("[CLIENT] Waiting for round informations...\n");
    // Recevoir des données du serveur et les stock dans le round
    verif = read(socketClient, &round, sizeof(Round));

    // Retourne -1 en cas d'erreur
    if (verif == -1) {
        perror("[CLIENT] Round not received");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
    printf("[CLIENT] Round informations received.\n");

    return round;
}


/**
 * @brief Envoyer le status du joueur pour qu'il soit ajouté dans une nouvelle partie
 * @param socketClient
 * @param player
 */
void send_player_status(int socketClient, Joueur player) {
    int verif;
    Buffer_out buffer;
    // Copier le status du joueur dans le message à envoyer
    sprintf(buffer.out, "%s", player.status);

    printf("[STATUS] Envoie : %s\n", buffer.out);
    // On envoie le status du joueur
    verif = write(socketClient, &buffer, sizeof(Buffer_out));
    
    // Si envoie echoue
    if (verif == -1) {
        perror("Erreur envoie du status du joueur");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief On récupère l'identifiant du gagnant
 * @param socket
 * @return int
 */
int get_winner(int socket) {
    int winner = 0;
    int recevoir;
    Buffer_out buffer;
    printf("[CLIENT] Waiting for winner name's...\n");
    // Recevoir des données du serveur et les stock dans le gagnant
    // recevoir = recv(socket, &winner, sizeof(int), 0);
    recevoir = read(socket, &buffer, sizeof(char) * 200);
    strtok(buffer.out, " ");
    winner = atoi(strtok(NULL, " "));
    printf("[CLIENT] Winner name's received.\n");

    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        perror("[CLIENT] Winner name's not received");
        close(socket);
        exit(EXIT_FAILURE);
    }
    return winner;
}