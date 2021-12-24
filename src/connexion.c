/**
 * @file connexion.c
 * @author REVOL Alexis (alexis.revol@cpe.fr)
 * @brief   Fonctionnalités pour se connecter au serveur
 * @version 0.1
 * @date 2021-23-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // a voir si obligatoire
#include <arpa/inet.h>
#include <string.h>
#include "../headers/lien.h"
#include "../headers/configs/configurator.h"
#include "../headers/connexion.h"

/**
 * @brief Créer une socket
 * @details Socket(Protocole IP, Protocole transmission des données, Port) \n
 * Protocole IP utilisé : AF_INET = Domaine d'adresse IPV4 \n
 * Protocole transport : SOCK_STREAM = TCP
 * @return int
 */
int create_socket() {
    printf("[SOCKET] Creating socket...\n");
    // Socket(Protocole IP, Protocole transmission des données, Port)
    // AF_INET = Domaine d'adresse IPV4
    // SOCK_STREAM = TCP
    int domain = AF_INET;
    int TYPE = SOCK_STREAM;
    int PROTOCOL = 0;
    int socketClient = socket(domain, TYPE, 0);
    printf("[SOCKET] Socket created.\n");

    return socketClient;
}


/**
 * @brief Créer une structure adresse serveur
 * @details stockaddr_in correspond à une adresse internet (IP et un port)
 * @param adresse_serv
 * @param port_serveur
 * @return struct sockaddr_in
 */
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

/**
 * @brief Etablir la connexion avec le serveur
 * @details On créer la socket et on lit le fichier de configuration qui contient les informations
 * du serveur (adresse, port) afin de pouvoir construire la structure du serveur \n
 * Ainsi on peut alors se connecter au serveur.
 * @return int
 */
int client_connexion() {
    int socketClient = create_socket();
    // Read config to allow connexion to the server
    server_config server_config = readconfig();

    // stockaddr_in correspond à une adresse internet (IP et un port)
    struct sockaddr_in addrClient = create_serv_adrr(server_config.ip, atoi(server_config.port));

    // Le client se connecte à l'adresse du serveur
    printf("[CONNEXION] Connecting to server...\n");
    int connexion = connect(socketClient, (const struct sockaddr *) &addrClient, sizeof(addrClient));
    if (connexion == 0) {
        printf("[CONNEXION] Connected to server.\n");
    } else {
        perror("[CONNEXION] Connection failed");
        close(socketClient);
        exit(EXIT_FAILURE);
    }
    return socketClient;
}
