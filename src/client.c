#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <netdb.h>
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
int client_connexion()
{
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


int client_recevoir_id(int socketClient){
	int id;
	recv(socketClient, &id, sizeof(id), 0);
	return id;
}

// Initialiser le joueur
Joueur initialise_player(int socketClient){
	Joueur player;
	printf("Reception id du joueur...\n");
	int identifiant = client_recevoir_id(socketClient);
	player.id = identifiant;
	return player;
}


// Recupérer le choix du joueur
Answer get_answer(Game game){
	int time_clique;
	Answer answer;
	// Le choix du joueur est decrit dans une structure "reponse" qui contient les infos de la partie + le choix du joueur + son temps de reponse
	answer.game = game;
	answer.choice = get_clique();
	answer.time = get_time_clique();
	printf("Recuperation reponse du joueur... \n");
	return answer;
}

// Envoyer des données (reponses du joueur) au serveur 
void send_answer(int socketClient, Game game){
	Answer answer;
	int envoie;

	// Recuperer la reponse du joueur
	answer = get_answer(game);

	printf("Envoie de donnees au serveur...\n");
	// On envoie la reponse du joueur
	envoie = send(socketClient, &answer, sizeof(answer), 0);

	// Si envoie echoue
	if(envoie == -1){
		printf("Erreur envoie des données\n");
	}
}

// On ferme le client
void client_fermer(int * socketClient, Joueur player){
	int fermeture;

	// Envoyer un message de fermeture au serveur ? 
//	disconnect_player(*socketClient, player);

	// Fermeture de la socket client
	fermeture = close(*socketClient);
	// Affichage du succès ou echec de la fermeture
	if(fermeture == 0){
		printf("Client fermé !\n");
	}
	else if(fermeture == -1){
		printf("Erreur fermeture client !\n");
	}
}

// Recevoir l'identifiant de la partie et créer la partie
Game create_game(int socketClient, Joueur player){
	Game game;
	game.id = client_recevoir_id(socketClient);
	game.player_id = player.id;
	printf("Creation partie...\n");
	return game;
}


// Recuperer les informations du round
Round get_round(int socketClient){
	Round round;
	int recevoir;
	printf("Reception round du serveur...\n");
	// Recevoir des données du serveur et les stock dans le round
	recevoir = recv(socketClient, &round, sizeof(round), 0);
	
	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception round\n");
	} 

	return round;
}


// Permet de jouer en communicant avec le serveur
void jouer(int socket, Game game){
	// Contient les informations d'un round
    Round round;
    round.number = "0";

	// Tant que le nombre de round n'est pas terminé on continue
	while(!game_end(round)){
		// Envoyer le choix du joueur au serveur
    	send_answer(socket, game);
    	// Le serveur nous renvois les resultat du round
    	round = get_round(socket);
	}
	printf("Fin de partie ! \n");
}


// Indique si la partie est fini ou continue
bool game_end(Round round){
	bool result = false;
	// Si on reçoit l'indiquateur de fin de partie (via le serveur)
	if(round.number == "end_game"){
		result = true;
	}
	return result;
}

// Recuperer la structure qui recaptilue la partie
Recap get_recap(int socketClient){
	Recap recap;
	int recevoir;
	printf("Reception recap du serveur...\n");
	// Recevoir des données du serveur et les stock dans le round
	recevoir = recv(socketClient, &recap, sizeof(recap), 0);
	
	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception recap\n");
	} 

	return recap;
}

// Récaptiluer la partie
void game_recap(int socketClient){
	Recap recap;
	recap = get_recap(socketClient);
	// Afficher l'historique de la partie
	print_recap(recap.list_answer_J1);
	print_recap(recap.list_answer_J2);
}

// Afficher la recapitulation de la partie du joueur choisi
void print_recap(Answer *answer){
	int len = strlen(answer);
	int id_player = answer[0].game.player_id;
	// Afficher chaque choix du joueur avec le temps qu'il a mis pour faire ce choix
	printf("Recap du joueur %d\n", id_player);
	for(int i = 0; i<len; i++){
		printf("choix = %d et temps = %d\n", answer[i].choice, answer[i].time);
	}
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le numero du carre cliqué
int get_clique(){
	int clique = 1;
	return clique;
}

/* A MODIFIER POUR PRENDRE LA VALEUR DU CARRE CLIQUE*/
// Recuperer le temps que le joueur a pris pour faire un choix
int get_time_clique(){
	int time_clique = 5;
	return time_clique;
}

// Envoyer un message de deconnexion du joueur au serveur
/*void disconnect_player(int socketClient, Joueur player){
	// Envoyer un message de fermeture au serveur ? 
	player.connected = false;
	client_envoyer(socketClient, player);
}*/


// Afficher informations du joueur
void display_player(Joueur player){
	printf("\nInformations joueur...\n");
	// Afficher propriétés
	printf("Nom : %s\n", player.nom);
	printf("Score = %d\n", player.score);
	printf("Identifiant : %d \n", player.id);
	printf("Choix : %d \n", player.choix);
	printf("Connecté = %s \n", player.connected ? "true" : "false");
	printf("\n\n");
}

