/**
 * @file client.c
 * @author REVOL Alexis (alexis.revol@cpe.fr)
 * @brief
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../headers/client.h"
#include "../headers/connexion.h"
#include "../headers/communication.h"
#include "../headers/lien.h"

#include "../headers/affichage.h"


 /**
 * @brief Indiquer si un identifiant est valide ou non
 * @param id
 * @return bool
 */
bool is_id_valide(int id) {
    if (id == -1) {
        return false;
    } else return true;
}



 /**
 * @brief Initialiser les informations du joueur
 * @param socketClient
 * @return Joueur
 */
Joueur create_player(int socketClient) {
    Joueur player;
    int identifiant;
    int local_id;
    char *type_id = "id"; // Clé du message à récupérer

    printf("[CLIENT] Receiving player id...\n");
    // On récupère l'id du joueur
    int *result = get_client_id(socketClient, type_id);
    identifiant = result[0];
    local_id = result[1];

    // Si l'ID récupérer est valide on l'affecte au joueur
    if (is_id_valide(identifiant)) {
        printf("[CLIENT] Player id received.\n");
        // On enregistre les informations lues
        player.id = identifiant;
        player.local_id = local_id;
        // Status du joueur "en ligne"
        strcpy(player.status, "online");
    } // Si l'id récupéré n'est pas valide on quitte le jeu
    else {
        printf("[CLIENT] Player id not valid.\n");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
    // Renvoyer le joueur créé
    return player;
}

 /**
 * @brief Recevoir l'identifiant de la partie et créer la partie
 * @param socketClient
 * @param player
 * @return Game
 */
Game create_game(int socketClient, Joueur player) {
    Game game;
    int id;
    // Creation du lien entre GUI et communication SOCKET
    create_link();

    // Récupérer l'identifiant de la partie
    printf("[CLIENT] Receiving party id...\n");
    int *result = get_client_id(socketClient, "party"); // L'identifiant contient "id/role" -> role pas nécessaire pour game
    id = result[0];
    // Si l'identifiant est valide
    if (is_id_valide(id)) {
        printf("[CLIENT] Party id received.\n");
        game.id = id;
        game.player = player;
    } else {
        printf("[CLIENT] Party id not valid.\n");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
    // Affichage
    printf("\n=========== Infos partie ===============\n");
    printf("Game ID : %d\n", game.id);
    printf("Player ID : %d\n", game.player.id);
    printf("Role : %d\n", game.player.local_id);
    printf("==========================\n");

    // A faire creer le lien entre joueur et GUI
    return game;
}


 /**
 * @brief Recupérer le choix du joueur (trahier ->0 ou colaborer -> 1 )
 * @param game
 * @return Answer
 */
Answer get_answer(Game game) {
    int time_clique;
    Answer answer;
    // Le choix du joueur est decrit dans une structure "reponse" qui contient les infos de la partie
    // + le choix du joueur + son temps de reponse
    printf("[CLIENT] Waiting for player choice...\n");
    // Indiquer que la reponse n'a pas encore etait reçue
    //lien.is_answer_ok = false;
    // Infos sur le joueur et la partie
    answer.party_id = game.id;
    answer.player_id = game.player.id;

    int time_start = time(NULL), time_end;
    // Valeurs jouées par le joueur
    answer.choice = get_clique();
    time_end = time(NULL);
    answer.time = time_end - time_start;

    printf("[CLIENT] Player choice completed.\n");
    return answer;
}

/**
 * @brief Envoyer des données (reponses du joueur) au serveur 
 * @param socketClient
 * @param game
 */
void send_answer(int socketClient, Game game) {
    Answer answer;
    int envoie;

    // Recuperer la reponse du joueur
    answer = get_answer(game);

    // Affichage
    printf("====================\n");
    printf("Answer : %i\n", answer.choice);
    printf("Time : %i\n", answer.time);
    printf("Game ID : %i\n", answer.party_id);
    printf("Player ID : %i\n", answer.player_id);
    printf("====================\n");

    printf("[CLIENT] Sending answer to the server...\n");
    // On envoie la reponse du joueur
    //   envoie = send(socketClient, &answer, sizeof(Answer), 0);
    envoie = write(socketClient, &answer, sizeof(Answer));
    // Si envoie echoue
    if (envoie == -1) {
        perror("[CLIENT] Answer not sent");
        close(socketClient);
        exit(EXIT_FAILURE);
    } else {
        printf("[CLIENT] Answer sent.\n");
    }
}

/**
 * @brief Permet de jouer en communicant avec le serveur (envoie du choix + reception resultat)
 * @param socket
 * @param game
 */
void jouer(int socket, Game game) {
    Round round;
    printf("[GAME] Starting game...\n");

    // Contient les informations d'un round de départ
    round = create_round(socket);
    printf("[GAME] Round created.\n");
    printf("[GAME] Round number = %d\n", round.round_number);

    // Tant que le nombre de round n'est pas terminé on continue
    do {
        // Envoyer le choix du joueur au serveur
        send_answer(socket, game);
        // Le serveur nous renvois les resultat du round
        round = get_round(socket, game);
        // Afficher sur l'interface graphique le resultat du round
        show_round_result(round, game);
    } while (game_end(round) != 1); // Tant que le jeux n'est pas fini

    // Mettre le nom du gagnant quand la partie est finie
    set_winner_name(socket, game);
}


/**
 * @brief  Indique si la partie est fini ou continue
 * @param round
 * @return int
 */
int game_end(Round round) {
    int result = 1;
    // Si on reçoit l'indiquateur de fin de partie (via le serveur)
    if (round.status != 1) {
        result = 0;
        printf("[GAME] Game continue.\n");
    } else if (round.status == 1) {
        result = 1;
        printf("[GAME] Game finished.\n");
    }
    printf("[DD] Result = %d\n", result);
    return result;
}

/**
 * @brief  Relancer une partie en indiquant au serveur que l'on souhaite continuer à jouer
 * @param socketClient
 * @param player
 * @return int
 */
int restart_game(int socketClient, Joueur player) {
    // Par défaut le client quitte la partie
    int result = 0;
    // Selon le choix du joueur (quitter partie ou relancer partie)
    if (continue_game() == false) {
        strcpy(player.status, "disconnect");
    } else {
        strcpy(player.status, "online");
        result = 1;
    }
    // Envoyer le status du joueur au serveur
    send_player_status(socketClient, player);
    return result;
}

/**
 * @brief Recuperer le choix du clique du joueur
 * @details Toutes les 0.2s ont regarde si le joueur à joué \n
 * Si il a joué on enregistre son choix afin de l'envoyer au serveur
 * Si le joueur n'a pas joué au bout de 60 secondes une réponse sera choisie automatiquement
 * @return int
 */
int get_clique() {
    int clique = -1, time_start, time_end, time_diff;
    int duree, compteur;
    char valeur[10]; // Valeur du temps en chaîne de caractère

    // Indiquer au joueur qu'il peut jouer
    lien.able_click = 1; // autoriser les cliques

    // Aucune information à afficher
    gtk_label_set_text(GTK_LABEL(tools.info), " ");

    duree = 60; // Temps que l'on a pour choisir une réponse
    compteur = 0; // Compte le temps écoulé

    // TODO FAIRE UNE FONCTION REFRESH CHRONO
    // Tant que le joueur n'a pas cliqué on attend
    while (lien.is_choice_ok != true) {
        compteur += 2; // Compte les milisecondes (2 -> 0.2 sec)
       
        // Si 1 seconde s'est écoulée
        if (compteur > 10) {
            // Afficher la valeur du chrono
            sprintf(valeur, "%ds", duree);
            gtk_label_set_text(GTK_LABEL(tools.chrono), valeur);
            // Patienter 1 sec avant d'afficher la valeur suivante
            duree = duree - 1;
            compteur = 0; // On remet le compteur de secondes à 0
        }

        // Si le compte à rebours et fini et qu'on a pas reçue de reponse du joueur
        if (duree < 0) {
            lien.choice = 0; // Choisir aléatoirement le choix du joueur
            lien.is_choice_ok = true;
            break;
        }
        // Sleep en micro seconde (us)
        usleep(200000); // Rafraichissement de la verification du clique toutes les 0.2s
    }
    // Une fois le choix du joueur effectué 
    // On repasse les autorisations de clique à 0
    lien.is_choice_ok = false;
    lien.able_click = 0;
    gtk_label_set_text(GTK_LABEL(tools.chrono), "Envoie...");
    // Afficher informations que J2 n'a pas encore joué
    gtk_label_set_text(GTK_LABEL(tools.info), "Attente réponse J2...");
    
    // On récupère le choix du joueur
    clique = lien.choice;

    return clique;
}


/**
 * @brief Recuperer le choix si le joueur relance ou pas une partie
 * @details Toutes les 0.2s ont regarde si le joueur à fait son choix \n
 * Une fois qu'il a fait son choix : quitter ou rejouer, on l'enregistre
 * afin d'indiquer au serveur si le client quitte la connexion ou souhaite refaire une partie
 * @return bool
 */
bool continue_game() {
    bool result = false;
    // Patienter jusqu'a ce que le joueur est choisie de rejouer ou quitter
    while (lien.is_restart_clicked == false) {
        usleep(200000); // Dormir 0.2 secondes
    }
    result = lien.restart_choice;

    // Si le joueur indique qu'il souhaite faire une nouvelle partie ou non
    return result;
}


/**
 * @brief Créer le round de depart
 * @details On initalise les valeurs du round une fois que le serveur nous indique que 
 * le round a commencé
 * @return Round
 */
// Créer le round de depart
Round create_round(int socketClient) {
    printf("Création du round...\n");
    Round round;
    int round_status;

    // Tant que le round n'a pas commencé on attend
    round_status = get_round_status(socketClient);

    // Score de départ
    round.p1_wallet = 0;
    round.p2_wallet = 0;
    // Choix par défaut des joueurs
    round.p1_result = -1;
    round.p2_result = -1;
    // Status de départ
    round.status = round_status;
    round.round_number = 1;

    round.p1_decision_time = -1;
    round.p2_decision_time = -1;

    return round;
}

/**
 * @brief Afficher le résultat du round
 * @details On met à jour les informations du GUI afin qu'il affiche le résultat du round
 * @param round
 * @param game
 */
// TODO afficher_result sans passer par liens
void show_round_result(Round round, Game game) {
    ResultRound result;
    // Affichage infos du round
    printf("\n======= Resultat du round ===========\n");
    printf("Round N°%d\n", round.round_number);
    printf("Result J1 : %d\n", round.p1_result);
    printf("Result J2 : %d\n", round.p2_result);
    printf("Status : %d\n", round.status);
    printf("ID RESULT : %d\n", game.player.local_id);
    printf("==================\n\n");

    // On met à jour les infos a transmettre au GUI
    lien.is_choice_ok = false;

    // Choix de l'ordre des informations à enregistrer selon rôle du joueur
    // Si on est J2
    if (game.player.local_id % 2 == 0) {
        printf("J2 \n");
        // Le score des deux joueurs
        result.score_j1 = round.p2_wallet;
        result.score_j2 = round.p1_wallet;
        // Le choix des deux joueurs
        result.choix_j1 = round.p2_result;
        result.choix_j2 = round.p1_result;
    }
    // Si on est J1
    else {
        printf("J1\n");
        // Le score des deux joueurs
        result.score_j1 = round.p1_wallet;
        result.score_j2 = round.p2_wallet;
        // Le choix des deux joueurs
        result.choix_j1 = round.p1_result;
        result.choix_j2 = round.p2_result;
    }

    result.nb_round = round.round_number;

    // Afficher les resultats sur GUI
    afficher_result(result);
}

/**
 * @brief On ferme le client
 * @param socketClient
 * @param player
 */
void client_fermer(int *socketClient, Joueur player) {
    int fermeture;
    // Fermeture de la socket client
    fermeture = close(*socketClient);
    // Affichage du succès ou echec de la fermeture
    if (fermeture == 0) {
        printf("Client fermé !\n");
    } else if (fermeture == -1) {
        perror("Erreur fermeture client");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief Détermine si la partie est gagnée ou perdue selon id du gagnant et id du joueur
 * @param game
 * @param winner
 * @return bool
 */
bool is_game_win(Game game, int winner) {
    bool win = false;
    if (game.player.local_id == winner) {
        win = true;
    }
    return win;
}

/**
 * @brief Afficher le nom gagnant
 * @param socket
 * @param game
 */
void set_winner_name(int socket, Game game) {
    int winner;
    // Récuéperer id du gagnant
    winner = get_winner(socket);
    // Si la partie est gagnée
    if (is_game_win(game, winner)) {
        // Afficher partie gagnée !
        show_win();
    }
        // Si la partie est perdue ou égalité
    else {
        if (winner == 0) {
            show_egality();
        } else {
            show_loose();
        }
    }
    // Afficher sur GUI les informations de fins de partie
    show_end_game();
}


/**
 * @brief Programme principal du client
 * @details Le client créer son joueur et créer la partie à partir des informations fournies
 * par le serveur. \n
 * Le client peut alors jouer au jeu et il continue de jouer tant qu'il indique qu'il souhaite
 * relance une partie. \n
 * Si le joueur quitte la partie on ferme la connexion.
 * @param param
 */
void startGame(void *param) {
    printf("Thread client en cours !\n");
    // Lire les parametres récupérés via le thread
    ClientParameter *client = malloc(sizeof(ClientParameter));
    int socket;
    Joueur player;
    // Contient les informations de la partie
    Game game;
    // Lire les parametres du client
    client = (ClientParameter *) param;
    socket = client->socket;

    // Contenue du jeu
    // Tant que le client veut continuer à jouer on informe le serveur
    do {
        // TODO : Séparer ou mettre direct dans les fonctions de créations ?
        // Initialiser le joueur
        memset(&player, 0, sizeof(Joueur));
         // Initialiser le jeu
        memset(&game, 0, sizeof(Game));

        player = create_player(socket);
        // Creation de la partie avec son identifiant et l'id du joueur (possible lorsque 2 joueurs co sur le serveur)
        game = create_game(socket, player);
        printf("Partie créée ! \n");
        // Jouer a la partie
        jouer(socket, game);
        printf("Finito\n");
    } while (restart_game(socket, player)); // Tant que le joueur veut faire une nouvelle partie

    // Fermer le client lorsqu'il ne joue plus
    client_fermer(&socket, player);
    free(client);
    pthread_exit(0);
}