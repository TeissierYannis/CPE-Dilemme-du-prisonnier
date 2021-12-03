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
	int port_serveur = 3000;

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
	char *type_id;
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
	int time_clique;
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

	printf("Envoie de donnees au serveur...\n");
	// On envoie la reponse du joueur
	envoie = send(socketClient, &answer, sizeof(answer), 0);

	// Si envoie echoue
	if(envoie == -1){
		printf("Erreur envoie des données\n");
		exit(EXIT_FAILURE);
	}
}

// Recuperer les informations du round (resultats J1 et J2 + n° du round)
Round get_round(int socketClient){
	Round round;
	int recevoir;
	printf("Reception round du serveur...\n");
	// Recevoir des données du serveur et les stock dans le round
	recevoir = recv(socketClient, &round, sizeof(round), 0);
	
	// On met à jour les infos a transmettre au GUI
	lien.score = round.j1_result;
	lien.is_choice_ok = false;
	lien.choix = -1;
	lien.is_answer_ok = true;

	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception round\n");
		exit(EXIT_FAILURE);
	} 

	return round;
}


// Permet de jouer en communicant avec le serveur (envoie du choix + reception resultat)
void jouer(int socket, Game game){
	printf("on joue !\n");
	// Contient les informations d'un round de départ
    Round round = create_round(socket);
	printf("Debut du round : %s", round.status);
    // TODO : Afficher le round depuis la com serv ??

	// Tant que le nombre de round n'est pas terminé on continue
	while(game_end(round) != true){
		//printf("game end = %s\n", game_end(round) ? "true" : "false");
		// Envoyer le choix du joueur au serveur
    	send_answer(socket, game);
    	// Le serveur nous renvois les resultat du round
    	round = get_round(socket);
		// Afficher sur l'interface graphique le resultat du round
		show_round_result(round);
	}
}


// Indique si la partie est fini ou continue
bool game_end(Round round){
	bool result = false;
	char *finish = "finished";

	// Si on reçoit l'indiquateur de fin de partie (via le serveur)
//	if(strcmp(round.status, finish) == 0){
	if(are_equal(round.status, finish)){
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
	int clique = -1;
    printf("Entrez la réponse : \n");
    //scanf("%d", &clique);
	while(lien.is_choice_ok != true){
		sleep(1);
	}
	clique = lien.choix;
	printf("Reponse choisie = %d\n", clique);
	//sleep(2);
//	printf("lien choix : %d\n", lien.is_choice_ok);
	// On patiente tant que le joueur n'a pas joué
	/*while(lien.is_choice_ok != true){
		sleep(1);
		printf("On patiente ...\n");
	}*/
	// Récupérer le choix du joueur
//	clique = lien.choix;
	//clique = 5;
	printf("Fin de la patience choix = %d\n", clique);

	// Afficher le message
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
	int choice = 0;
	bool result = false;
	printf("Voulez vous jouer une nouvelle partie ? [No->0 and Yes->1]\n");
	//scanf("%d", choice);
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
char *get_round_status(int socketClient){
	char *status;
	char status_round[2048];
	int recevoir;
	// Recevoir le status du round
	recevoir = recv(socketClient, status_round, sizeof(status_round), 0);
	printf("round récup = %s\n", status_round);
	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception status round...\n");
		exit(EXIT_FAILURE);
	} 
	strcpy(status, status_round);
	printf("round récupéré status : %s\n", status);
	return status;

}

// Créer le round de depart
Round create_round(int socketClient){
	printf("Création du round...\n");
	Round round;
	char *round_status;
	char *start = "start";
    // TODO ATTENDRE LE DEBUT DU ROUND
	// Tant que le round n'a pas commencé on attend
	do{
		round_status = get_round_status(socketClient);
	}while(!are_equal(round_status, start));
	
	// Score de départ
	round.j1_result = 0;
	round.j2_result = 0;
	// Status de départ
	strcpy(round.status, start);
	round.round_number = 1;

	return round;
}


// Afficher le résultat du round
void show_round_result(Round round){
	// Affichage infos du round
    printf("\n======= Resultat du round ===========\n");
    printf("Round N°%d\n", round.round_number);
    printf("Result J1 : %d\n", round.j1_result);
    printf("Result J2 : %d\n", round.j2_result);
    printf("Status : %s\n", round.status);
    printf("==================\n\n");
}

// On ferme le client
void client_fermer(int * socketClient, Joueur player){
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


// Programme principal du client
void startGame(void *param){
	printf("Thread client en cours !\n");
    // Lire les parametres récupérés via le thread
    ClientParameter *client;
    int socket;
    Joueur player;
    // Contient les informations de la partie
    Game game;
    // Lire les parametres du client
    client = (ClientParameter *)param;
    socket = client->socket;
    player = client->player;

    // Contenue du jeu
    // Continuer à jouer ou quitter ?
    // Tant que le client veut continuer à jouer on informe le serveur
    do{
        // Creation de la partie avec son identifiant et l'id du joueur (possible lorsque 2 joueurs co sur le serveur)
        game = create_game(socket, player);
		printf("Partie créée ! \n");
        // Jouer a la partie
        jouer(socket, game);
        // Recapituler la partie
        game_recap(socket);
    }while(restart_game(socket, player)); // Tant que le joueur veut faire une nouvelle partie


    // Fermer le client lorsqu'il ne joue plus
    client_fermer(&socket, player);
    free(client);
}
