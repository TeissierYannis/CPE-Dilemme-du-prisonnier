#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <arpa/inet.h>
#include <string.h>

#include "../headers/client.h"

// Créer une socket
int create_socket(){
	// Socket(Protocole IP, Protocole transmission des données, Port)
	// AF_INET = Domaine d'adresse IPV4
	// SOCK_STREAM = TCP
	int DOMAIN = AF_INET;
	int TYPE = SOCK_STREAM;
	int PROTOCOL = 0;
	int socketClient = socket(DOMAIN, TYPE, PROTOCOL);

	return socketClient;
}


// Creer structure adresse serveur
struct sockaddr_in create_serv_adrr(char *adresse_serv, int port_serveur){

	// stockaddr_in correspond à une adresse internet (IP et un port)
	struct sockaddr_in addrClient;
	// Indiquer adresse du serveur
	addrClient.sin_addr.s_addr = inet_addr(adresse_serv);
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port_serveur); //htons converti un entier en port

	return addrClient;
}

// Partie client
int client_connexion(){
	int socketClient = create_socket();

	// IP et Port du serveur
	char *adresse_serv = "127.0.0.1";
	int port_serveur = 30000;

	// stockaddr_in correspond à une adresse internet (IP et un port)
	struct sockaddr_in addrClient = create_serv_adrr(adresse_serv, port_serveur);
	
	// Le client se connecte à l'adresse du serveur
	int connexion;
	connexion = connect(socketClient, (const struct sockaddr *)& addrClient, sizeof(addrClient));
	if(connexion == 0){
		printf("Connexion réussie !\n");
	}
	else if (connexion == -1){
		printf("Erreur connexion client \n");
		exit(EXIT_FAILURE);
	}	
	return socketClient;
}

// Le client reçoit un id
int client_recevoir_id(int socketClient, char *title){
	int id;
    char message[2048]; // stock le message que le serveur a envoyé
	char *key;	// titre du message
	char *separateur = " "; // separateur entre les champs du message

	// Recevoir message du serveur contenant un identifiant et le nom de ce à quoi correspond l'ID
	// (id du joueur ou id de la partie)
    recv(socketClient, &message, sizeof(message), 0);
	// Récupérer le titre de l'identifiant
    key = strtok(message, separateur);
	
    // Si l'ID correspond au type d'ID demandé on l'enregistre
	if (are_equal(key,title)) {
        // Récuperer la deuxième partie du message (l'id) et le convertir en identifiant
		id = atoi(strtok(NULL, " "));
    } 
	// Sinon on passe sans utiliser l'ID
	else {
		id = -1;
    }
	
	return id;
}

// Initialiser le joueur avec id reçu
Joueur create_player(int socketClient){
	Joueur player;
	char *type_id = "id"; // A modifier selon valeur du serveur

	printf("Reception id du joueur...\n");
	// On récupère l'id du joueur
	int identifiant = client_recevoir_id(socketClient, type_id);
	// Si l'ID récupérer est valide on l'affecte au joueur
	if(is_id_valide(identifiant)){
		player.id = identifiant;
		// Status du joueur "en ligne"
		strcpy(player.status, "online");
	}
	// Si l'id récupéré n'est pas valide on quitte le jeu
	else{
		printf("Erreur récupération id du joueur...\n");
		exit(EXIT_FAILURE);
	}
	// Renvoyer le joueur créé
	return player;
}


// Recevoir l'identifiant de la partie et créer la partie
Game create_game(int socketClient, Joueur player){
	Game game;
	int id;
	char * type_id;
	// Récupérer l'identifiant de la partie
	type_id = "party";
	id = client_recevoir_id(socketClient, type_id);

	// Si l'identifiant est valide
	if(is_id_valide(id)){
		game.id = id;
		game.player_id = player.id;
	}
	else{
		printf("Erreur réception id de la partie...\n");
		exit(EXIT_FAILURE);
	}
	// Affichage
	printf("\n=========== Infos partie ===============\n");
    printf("Game ID : %d\n", game.id);
    printf("Player ID : %d\n", game.player_id);
    printf("==========================\n");

	return game;
}

// Recupérer le choix du joueur (trahier ->0 ou colaborer -> 1 ?)
Answer get_answer(Game game){
	int time_clique; // TODO TIMER
	Answer answer;
	// Le choix du joueur est decrit dans une structure "reponse" qui contient les infos de la partie 
	// + le choix du joueur + son temps de reponse
	printf("Recuperation reponse du joueur... \n");

	// Infos sur le joueur et la partie
	answer.party_id = game.id;
	answer.player_id = game.player_id;
	// Valeurs jouées par le joueur
	answer.choice = get_clique();
	answer.time = get_time_clique();

	return answer;
}

// Envoyer des données (reponses du joueur) au serveur 
void send_answer(int socketClient, Game game){
	Answer answer;
	int envoie = -2;

	// Recuperer la reponse du joueur
	answer = get_answer(game);

	// Affichage
    printf("====================\n");
    printf("Answer : %i\n", answer.choice);
    printf("Time : %i\n", answer.time);
	printf("Game ID : %i\n", answer.party_id);
    printf("Player ID : %i\n", answer.player_id);
    printf("====================\n");

	printf("Envoie de donnees au serveur...\n");
	// On envoie la reponse du joueur
	envoie = write(socketClient, &answer, sizeof(answer));

	// Si envoie echoue
	if(envoie == -1){
		printf("Erreur envoie des données\n");
		exit(EXIT_FAILURE);
	}
}

// Recuperer les informations du round (resultats J1 et J2 + n° du round)
Round get_round(int socketClient){
	Round round1;

    // Score de départ
    round1.p1_result = 0;
    round1.p1_decision_time = 0;
    round1.p2_result = 0;
    round1.p2_decision_time = 0;
    round1.round_number = 1;
    round1.status = -1;

    int receive = -2;

    void *buffer = malloc(sizeof(Round));

	printf("Reception round du serveur...\n");
	// Recevoir des données du serveur et les stock dans le round
	receive = recv(socketClient, buffer, sizeof(Round), 0);
    memcpy(&round1, buffer, sizeof(Round));

    printf("\n=========== Infos round ===============\n");
    printf("receive : %d\n", receive);

	// Retourne -1 en cas d'erreur
	if(receive == -1){
		printf("Erreur reception round\n");
	}

	return round1;
}


// Permet de jouer en communicant avec le serveur (envoie du choix + reception resultat)
void jouer(int socket, Game game){

    int round_status;
    // TODO ATTENDRE LE DEBUT DU ROUND
    // Tant que le round n'a pas commencé on attend
    do{
        round_status = get_round_status(socket);
    }while(round_status != 0);

    Round rnd;
    do {
        // TODO : Afficher le round depuis la com serv ??
        // Tant que le nombre de round n'est pas terminé on continue
        //printf("game end = %s\n", game_end(round) ? "true" : "false");
        // Envoyer le choix du joueur au serveur
        send_answer(socket, game);
        // Le serveur nous renvois les resultat du round
        rnd = get_round(socket);
        // Afficher sur l'interface graphique le resultat du round
        show_round_result(rnd);
    } while (!game_end(rnd));

}


// Indique si la partie est fini ou continue
bool game_end(Round round){
	bool result = false;

	// Si on reçoit l'indiquateur de fin de partie (via le serveur)
	if(round.status == 1){
		result = true;
		printf("Fin de partie ! \n");
	}
	return result;
}

// Recevoir le recapitulatif de la partie
Recap get_recap(int socketClient){
	Recap recap;
	int recevoir;
	printf("Reception recap du serveur...\n");
	// Recevoir recapitulatif des choix de chaque joueur a chaque round
	recevoir = recv(socketClient, &recap, sizeof(recap), 0);
	
	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception recap...\n");
		exit(EXIT_FAILURE);
	} 

	return recap;
}

// Récaptiluer la partie (resultats des deux joueurs à chaque round)
void game_recap(int socketClient){
	Recap recap;
	recap = get_recap(socketClient);
	// Afficher l'historique de la partie
	print_recap(recap.list_answer_J1);
	print_recap(recap.list_answer_J2);
}

// Afficher la recapitulation de la partie pour le joueur indiqué
void print_recap(Answer answer[]){
	// TODO
	// Mettre dans recap le nombre de round pour connaitre la taille ?
	int len = sizeof(*answer)/sizeof(answer[0]); // PAS OK
	printf("len recap = %d\n", len);
	// int id_player = answer[0].game.player_id;

	// Afficher chaque choix du joueur avec le temps qu'il a mis pour faire ce choix
	printf("Recap du joueur %d\n", answer->player_id);
	for(int i = 0; i<len; i++){
		printf("choix = %d et temps = %d\n", answer[i].choice, answer[i].time);
	}
}


// Relancer une partie
bool restart_game(int socketClient, Joueur player){
	// Par défaut le client quitte la partie
	bool result = false;
	// Selon le choix du joueur (quitter partie ou relancer partie)
	if(!continue_game()){
		strcpy(player.status, "disconnect");
	}
	else {
		strcpy(player.status, "online");
		result = true;
	}
	// Envoyer le status du joueur au serveur
	send_player_status(socketClient, player);
	return result;
}

// Envoyer le status du joueur pour qu'il soit ajouté dans une nouvelle partie
void send_player_status(int socketClient, Joueur player){
	int envoie;
	printf("Envoie du status du joueur au serveur...\n");
	// On envoie le status du joueur
	envoie = send(socketClient, &player.status, sizeof(player.status), 0);

	// Si envoie echoue
	if(envoie == -1){
		printf("Erreur envoie du status du joueur \n");
		exit(EXIT_FAILURE);
	}
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le numero du carre cliqué
int get_clique(){
	int clique = 1;
    printf("Entrez la réponse : \n");
    scanf("%d", &clique);
	return clique;
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le temps que le joueur a pris pour faire un choix
int get_time_clique(){
	int time_clique = 5;
	return time_clique;
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le choix si le joueur relance ou pas une partie
bool continue_game(){
	int choice;
	bool result = false;
	printf("Voulez vous jouer une nouvelle partie ? [No->0 and Yes->1]\n");
	scanf("%d", choice);
	// Si le joueur indique qu'il souhaite faire une nouvelle partie
	if(choice == 1){
		result = true;
	}
	return result;
}


// Indiquer si un identifiant est valide ou non
bool is_id_valide(int id){
	if(id == -1){
		return false;
	}
	else return true;
}

// Récupérer le status de départ du round
int get_round_status(int socketClient){
	char status_round[100];
	int receive;
	// Recevoir le status du round
	receive = recv(socketClient, status_round, sizeof(char) * 100, 0);
	// Retourne -1 en cas d'erreur
	if(receive == -1){
		printf("Erreur reception status round...\n");
		exit(EXIT_FAILURE);
	}

    strtok(status_round, " ");
    int status = atoi(strtok(NULL, " "));

	return status;
}

// Créer le round de depart
Round create_round(int socketClient){
	Round round;
	int round_status;
    // TODO ATTENDRE LE DEBUT DU ROUND
	// Tant que le round n'a pas commencé on attend
    do{
		round_status = get_round_status(socketClient);
	}while(round_status != 0);

    round.status = round_status;

	// Score de départ
	round.p1_result = 0;
    round.p1_decision_time = 0;
	round.p2_result = 0;
    round.p2_decision_time = 0;
	round.round_number = 1;

	return round;
}


// Afficher le résultat du round
void show_round_result(Round round){
	// Affichage infos du round
    printf("======= Resultat du round ===========\n");
    printf("Round N°%d\n", round.round_number);
    printf("Result J1 : %d\n", round.p1_result);
    printf("Result J2 : %d\n", round.p2_result);
    printf("Status : %d\n", round.status);
    printf("==================\n\n");
}

// On ferme le client
void client_fermer(const int * socketClient, Joueur player){
	int fermeture;
	// Fermeture de la socket client
	fermeture = close(*socketClient);
	// Affichage du succès ou echec de la fermeture
	if(fermeture == 0){
		printf("Client fermé !\n");
	}
	else if(fermeture == -1){
		printf("Erreur fermeture client !\n");
		exit(EXIT_FAILURE);
	}
}


// Comparer 2 chaine de caracteres
bool are_equal(char *key, char *name){
	bool result = false;
	// Si la clé correspond au nom indiqué
	if(strcmp(key, name) == 0){
		result = true;
	}
	return result;
}
