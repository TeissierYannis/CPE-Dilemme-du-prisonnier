#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <arpa/inet.h>
#include <string.h>

#include "../headers/client.h"
#include "../headers/lien.h"

// Créer une socket
int create_socket() {
    printf("[SOCKET] Creating socket...\n");
    // Socket(Protocole IP, Protocole transmission des données, Port)
    // AF_INET = Domaine d'adresse IPV4
    // SOCK_STREAM = TCP
    int domain = AF_INET;
    int TYPE = SOCK_STREAM;
    int PROTOCOL = 0;
    int socketClient = socket(domain, TYPE, PROTOCOL);

    printf("[SOCKET] Socket created.\n");

    return socketClient;
}


// Creer structure adresse serveur
struct sockaddr_in create_serv_adrr(char *adresse_serv, int port_serveur) {

    printf("[SOCKET] Creating server address...\n");

    // stockaddr_in correspond à une adresse internet (IP et un port)
    struct sockaddr_in addrClient;
    // Indiquer adresse du serveur
    addrClient.sin_addr.s_addr = inet_addr(adresse_serv);
    addrClient.sin_family = AF_INET;
    addrClient.sin_port = htons(port_serveur); //htons converti un entier en port

    printf("[SOCKET] Server address created.\n");

    return addrClient;
}

// Partie client
int client_connexion() {
    int socketClient = create_socket();

    // IP et Port du serveur
    char *adresse_serv = "127.0.0.1";
    int port_serveur = 30000;

    // stockaddr_in correspond à une adresse internet (IP et un port)
    struct sockaddr_in addrClient = create_serv_adrr(adresse_serv, port_serveur);

    // Le client se connecte à l'adresse du serveur
    printf("[CONNEXION] Connecting to server...\n");
    int connexion = connect(socketClient, (const struct sockaddr *) &addrClient, sizeof(addrClient));
    if (connexion == 0) {
        printf("[CONNEXION] Connected to server.\n");
    } else {
        printf("[CONNEXION] Connection failed.\n");
        exit(EXIT_FAILURE);
    }
    return socketClient;
}

// Le client reçoit un id
int * client_recevoir_id(int socketClient, char *title) {
    char * id;
    int id_int = -1, id_player_local = -1;
    char message[255]; // stock le message que le serveur a envoyé
    char *key;    // titre du message
    char *separateur = " "; // separateur entre les champs du message
    int receive;

    // Recevoir message du serveur contenant un identifiant et le nom de ce à quoi correspond l'ID
    // (id du joueur ou id de la partie)
    printf("[RECEIVE] Receiving id from server...\n");
    receive = recv(socketClient, &message, sizeof(char) * 255, 0);
    // Vérifier la réception
    if (receive == -1){
        printf("[RECEIVE] Error reception ID :");
    }
    else{
        printf("[RECEIVE] id received : %s\n", message);
    }
     
    // Récupérer le titre de l'identifiant en l'extrayant de la chaine de caracteres
    key = strtok(message, separateur);

    // Si l'ID correspond au type d'ID demandé on l'enregistre
    if (are_equal(key, title)) {
        // Récuperer la deuxième partie du message (l'id) et le convertir en identifiant
        id = strtok(NULL, " ");

        if (are_equal(title, "id")) {
            id_int = atoi(strtok(id, ":"));
            id_player_local = atoi(strtok(NULL, ":"));
        } else {
            id_int = atoi(id);
        }
    }
    // Sinon on passe sans utiliser l'ID

    int result[2] = {id_int, id_player_local};
    return result;
}

// Initialiser le joueur avec id reçu
Joueur create_player(int socketClient) {
    Joueur player;
    char *type_id = "id"; // A modifier selon valeur du serveur

    printf("[CLIENT] Receiving player id...\n");
    // On récupère l'id du joueur

    int * result = client_recevoir_id(socketClient, type_id);
    int identifiant = result[0];
    int local_id = result[1];
    // Si l'ID récupérer est valide on l'affecte au joueur
    if (is_id_valide(identifiant)) {
        printf("[CLIENT] Player id received.\n");
        player.id = identifiant;
        player.local_id = local_id;
        // Status du joueur "en ligne"
        strcpy(player.status, "online");
    }
        // Si l'id récupéré n'est pas valide on quitte le jeu
    else {
        printf("[CLIENT] Player id not valid.\n");
        exit(EXIT_FAILURE);
    }
    // Renvoyer le joueur créé
    return player;
}


// Recevoir l'identifiant de la partie et créer la partie
Game create_game(int socketClient, Joueur player) {
    Game game;
    int id;
    // Creation du lien entre GUI et communication SOCKET
    create_link();
    // Récupérer l'identifiant de la partie
    printf("[CLIENT] Receiving party id...\n");
    id = client_recevoir_id(socketClient, "party");
    // Si l'identifiant est valide
    if (is_id_valide(id)) {
        printf("[CLIENT] Party id received.\n");
        game.id = id;
        game.player_id = player.id;
    } else {
        printf("[CLIENT] Pargity id not valid.\n");
        exit(EXIT_FAILURE);
    }
    // Affichage
    printf("\n=========== Infos partie ===============\n");
    printf("Game ID : %d\n", game.id);
    printf("Player ID : %d\n", game.player_id);
    printf("==========================\n");

    // A faire creer le lien entre joueur et GUI
    return game;
}

// Recupérer le choix du joueur (trahier ->0 ou colaborer -> 1 ?)
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
    answer.player_id = game.player_id;
    // Valeurs jouées par le joueur
    answer.choice = get_clique();
    answer.time = get_time_clique();

    printf("[CLIENT] Player choice completed.\n");
    return answer;
}

// Envoyer des données (reponses du joueur) au serveur 
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
    envoie = send(socketClient, &answer, sizeof(Answer), 0);

    // Si envoie echoue
    if (envoie == -1) {
        printf("[CLIENT] Answer not sent.\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[CLIENT] Answer sent.\n");
    }
}

// Recuperer les informations du round (resultats J1 et J2 + n° du round)
Round get_round(int socketClient) {
    Round round;
    int recevoir;
    printf("[CLIENT] Waiting for round informations...\n");
    // Recevoir des données du serveur et les stock dans le round
    recevoir = recv(socketClient, &round, sizeof(Round), 0);

    printf("[CLIENT] Round informations received.\n");

    // A SEPARER DANS UNE AUTRE FONCTION
    // On met à jour les infos a transmettre au GUI
    lien.is_choice_ok = false;
    // Le score des deux joueurs
    lien.score_j1 = round.p1_wallet;
    lien.score_j2 = round.p2_wallet;
    lien.nb_round = round.round_number;
    // Le choix des deux joueurs
    lien.choix_j1 = round.p1_result;
    lien.choix_j2 = round.p2_result;
    printf("J1 choice = %d et J2 choice = %d\n", lien.choix_j1, lien.choix_j2);
    lien.is_answer_ok = true;

    printf("Round reçue !\n");
    printf("Numero = %d\n", round.round_number);
    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        printf("[CLIENT] Round not received.\n");
        exit(EXIT_FAILURE);
    }

    return round;
}


// Permet de jouer en communicant avec le serveur (envoie du choix + reception resultat)
void jouer(int socket, Game game) {
    printf("[GAME] Starting game...\n");
    // Contient les informations d'un round de départ
    Round round = create_round(socket);
    printf("[GAME] Round created.\n");
    printf("[GAME] Round number = %d\n", round.round_number);
    // TODO : Afficher le round depuis la com serv ??

    // Tant que le nombre de round n'est pas terminé on continue
    while (game_end(round) != 1) {
        //printf("game end = %s\n", game_end(round) ? "true" : "false");
        // Envoyer le choix du joueur au serveur
        send_answer(socket, game);
        // Le serveur nous renvois les resultat du round
        round = get_round(socket);
        // Afficher sur l'interface graphique le resultat du round
        show_round_result(round);
    }
    // Mettre à jour le nom du gagant
    set_winner_name(socket, game);
}


// Indique si la partie est fini ou continue
int game_end(Round round) {
    bool result = 0;
    
    // Si on reçoit l'indiquateur de fin de partie (via le serveur)
    if (round.status == 1) {
        result = true;
        printf("[GAME] Game finished.\n");
    }
    return result;
}

// Recevoir le recapitulatif de la partie
Recap get_recap(int socketClient) {
    Recap recap;
    int recevoir;
    printf("Reception recap du serveur...\n");
    // Recevoir recapitulatif des choix de chaque joueur a chaque round
    recevoir = recv(socketClient, &recap, sizeof(Recap), 0);

    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        printf("Erreur reception recap...\n");
        exit(EXIT_FAILURE);
    }

    return recap;
}

// Récaptiluer la partie (resultats des deux joueurs à chaque round)
void game_recap(int socketClient) {
    Recap recap;
    recap = get_recap(socketClient);

    // TODO Mettre dans le recap le nombre final de round ?
    //int length_J1 = sizeof(recap.list_answer_J1)/sizeof(recap.list_answer_J1[0]); // TODO à CHANGER
    //int length_J2 = sizeof(recap.list_answer_J1)/sizeof(recap.list_answer_J1[0]); // TODO à CHANGER

    //printf("TAILLE recap = %d\n", length_J1);
    // Afficher l'historique de la partie
    print_recap((Answer *) &recap.list_answer_J1, recap.nb_round);
    print_recap((Answer *) &recap.list_answer_J2, recap.nb_round);
}

// Afficher la recapitulation de la partie pour le joueur indiqué
void print_recap(Answer *answer, int length) {
    printf("========================================================\n");
    printf("len recap = %d\n", length);
    // int id_player = answer[0].game.player_id;

    // Afficher chaque choix du joueur avec le temps qu'il a mis pour faire ce choix
    printf("Recap du joueur %d\n", answer->player_id);
    for (int i = 0; i < length; i++) {
        printf("[%d] choix = %d et temps = %d\n", i, answer[i].choice, answer[i].time);
    }
    printf("========================================================\n");
}


// Relancer une partie
int restart_game(int socketClient, Joueur player) {
    // Par défaut le client quitte la partie
    bool result = 0;
    // Selon le choix du joueur (quitter partie ou relancer partie)
    if (!continue_game()) {
        strcpy(player.status, "disconnect");
    } else {
        strcpy(player.status, "online");
        result = 1;
    }
    // Envoyer le status du joueur au serveur
    send_player_status(socketClient, player);
    return result;
}

// Envoyer le status du joueur pour qu'il soit ajouté dans une nouvelle partie
void send_player_status(int socketClient, Joueur player) {
    int envoie;
    printf("Envoie du status du joueur au serveur...\n");
    // On envoie le status du joueur
    envoie = send(socketClient, &player.status, sizeof(int), 0);

    // Si envoie echoue
    if (envoie == -1) {
        printf("Erreur envoie du status du joueur \n");
        exit(EXIT_FAILURE);
    }
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le numero du carre cliqué
int get_clique() {
    int clique = -1;
    // Indiquer au joueur qu'il peut jouer
    lien.able_click = 1; // autoriser les cliques
    // Aucune information à afficher
    gtk_label_set_text(GTK_LABEL(tools.info), " ");

    printf("Entrez la réponse : \n");
    // Tant que le joueur n'a pas cliqué on attend
    while (lien.is_choice_ok != true) {
        sleep(0.3);
    }
    lien.is_choice_ok = false;
    // Afficher informations que J2 n'a pas encore joué
    gtk_label_set_text(GTK_LABEL(tools.info), "Attente réponse J2...");
  //  lien.able_click = 0;
   // lien.is_choice_ok = false;
    // On récupère le choix du joueur
    clique = lien.choix_j1;
    printf("Reponse choisie = %d\n", clique);

    //printf("Fin de la patience choix = %d\n", clique);
    // Afficher le message
    return clique;
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le temps que le joueur a pris pour faire un choix
int get_time_clique() {
    int time_clique = 5;
    return time_clique;
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le choix si le joueur relance ou pas une partie
bool continue_game() {

    bool result = false;
    // Patienter jusqu'a ce que le joueur est choisie de rejouer ou quitter
    while (lien.is_restart_clicked == false) {
        sleep(0.3);
    }
    result = lien.restart_choice;
    // printf("Voulez vous jouer une nouvelle partie ? [No->0 and Yes->1]\n");
    //scanf("%d", choice);
    // Si le joueur indique qu'il souhaite faire une nouvelle partie ou non
    return result;
}


// Indiquer si un identifiant est valide ou non
bool is_id_valide(int id) {
    if (id == -1) {
        return false;
    } else return true;
}

// Récupérer le status de départ du round
int get_round_status(int socketClient) {
    int status;

    char status_round[255];
    int recevoir;
    printf("Reception status du round...\n");
    // Recevoir le status du round
    recevoir = recv(socketClient, &status_round, sizeof(char) * 255, 0);
 
    strtok(status_round, " ");
    status = atoi(strtok(NULL, " "));
    printf("Avant round = %s\n", status_round);
    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        printf("Erreur reception status round...\n");
        exit(EXIT_FAILURE);
    }

    printf("round récupéré status : %d\n", status);
    return status;
}

// Créer le round de depart
Round create_round(int socketClient) {
    printf("Création du round...\n");
    Round round;
    int round_status;
    char *status = NULL;
    // TODO ATTENDRE LE DEBUT DU ROUND
    // Tant que le round n'a pas commencé on attend
    do {
        round_status = get_round_status(socketClient);
    } while (round_status != 0);

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


// Afficher le résultat du round
void show_round_result(Round round) {
    // Affichage infos du round
    printf("\n======= Resultat du round ===========\n");
    printf("Round N°%d\n", round.round_number);

    printf("Result J1 : %d\n", round.p1_result);
    printf("Result J2 : %d\n", round.p2_result);
    printf("Status : %d\n", round.status);
    printf("==================\n\n");
}

// On ferme le client
void client_fermer(int *socketClient, Joueur player) {
    int fermeture;
    // Fermeture de la socket client
    fermeture = close(*socketClient);
    // Affichage du succès ou echec de la fermeture
    if (fermeture == 0) {
        printf("Client fermé !\n");
    } else if (fermeture == -1) {
        printf("Erreur fermeture client !\n");
        exit(EXIT_FAILURE);
    }
}


// Comparer 2 chaine de caracteres
bool are_equal(char *key, char *name) {
    bool result = false;
    // Si la clé correspond au nom indiqué
    if (strcmp(key, name) == 0) {
        result = true;
    }
    return result;
}

int get_winner(int socket){
    int winner;
    int recevoir;
    printf("[CLIENT] Waiting for winner name's...\n");
    // Recevoir des données du serveur et les stock dans le gagnant
    recevoir = recv(socket, &winner, sizeof(int), 0);

    printf("[CLIENT] Winner name's received.\n");

    // Retourne -1 en cas d'erreur
    if (recevoir == -1) {
        printf("[CLIENT] Winner name's not received.\n");
        exit(EXIT_FAILURE);
    }

    return winner;
}

bool is_game_win(Game game, int winner){
    bool win = false;
    if(game.player_id == winner){
        win = true;
    }
    return win;
}

// Afficher le gagnant
void set_winner_name(int socket, Game game){
    int winner;
    // Récuéperer id du gagnant
    winner = get_winner(socket);
    // Si la partie est gagnée
    if(is_game_win(game, winner)){
        // Afficher partie gagnée !
        lien.is_winner = true;
    }
    // Si la partie est perdue
    else{
        // Afficher partie perdue !
        lien.is_winner = false;
    }
    // indiquer la fin du jeu
    lien.is_game_end = true;
    printf("Partie gagné = %d et fin de partie = %d\n", lien.is_winner, lien.is_game_end);
}


// Programme principal du client
void startGame(void *param) {
    printf("Thread client en cours !\n");
    // Lire les parametres récupérés via le thread
    ClientParameter *client;
    int socket;
    Joueur player;
    // Contient les informations de la partie
    Game game;
    // Lire les parametres du client
    client = (ClientParameter *) param;
    socket = client->socket;
    player = client->player;

    // Contenue du jeu
    // Continuer à jouer ou quitter ?
    // Tant que le client veut continuer à jouer on informe le serveur
    do {
        // Creation de la partie avec son identifiant et l'id du joueur (possible lorsque 2 joueurs co sur le serveur)
        game = create_game(socket, player);
        printf("Partie créée ! \n");
        // Jouer a la partie
        jouer(socket, game);
        // Recapituler la partie
        game_recap(socket);
    } while (restart_game(socket, player)); // Tant que le joueur veut faire une nouvelle partie


    // Fermer le client lorsqu'il ne joue plus
    client_fermer(&socket, player);
    free(client);
}