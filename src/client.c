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
		printf("Erreur connexion client");
		exit(EXIT_FAILURE);
	}	
	return socketClient;
}

// Recevoir des données du serveur
Joueur client_recevoir(int socketClient){
	Joueur user;
	int recevoir;
	printf("Reception de donnees du serveur...\n");
	// Recevoir des données du serveur et les stock dans le Joueur
	recevoir = recv(socketClient, &user, sizeof(user), 0);
	
	// Retourne -1 en cas d'erreur
	if(recevoir == -1){
		printf("Erreur reception client\n");
	} 

	// Afficher les données reçues
	display_player(user);

	return user;
}

// Envoyer des données au serveur
void client_envoyer(int socketClient, Joueur player){
	int envoie;
	printf("Envoie de donnees au serveur...\n");
	// On envoie les elements du joueur contenu dans la structure
	envoie = send(socketClient, &player, sizeof(player), 0);

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