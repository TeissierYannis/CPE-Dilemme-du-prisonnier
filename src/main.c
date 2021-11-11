#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


// Contient les informations d'un Joueur
typedef struct{
    int score;
    char nom[30];
} Joueur;


// Partie client
int main()
{
	// Socket(Protocole IP, Protocole transmission des données, Port)
	// AF_INET = Domaine d'adresse IPV4
	// SOCK_STREAM = TCP
	int DOMAIN = AF_INET;
	int TYPE = SOCK_STREAM;
	int PROTOCOL = 0;
	int socketClient = socket(DOMAIN, TYPE, PROTOCOL);

	// stockaddr_in correspond à une adresse internet (IP et un port)
	struct sockaddr_in addrClient;
	// Indiquer adresse du serveur
	addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrClient.sin_family = DOMAIN;
	addrClient.sin_port = htons(30000); //htons converti un entier en port

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

	// Recevoir des données du serveur et les stock dans le Joueur
	Joueur user;
	recv(socketClient, &user, sizeof(user), 0);

	// Afficher les données reçues
	printf("Nom : %s\n", user.nom);
	printf("Score = %d\n", user.score);

	// On ferme le client
	close(socketClient);

	return 0;
}