/**
 * @file server.h
 * @author Teissier Yannis
 * @brief This file contains server management functions and game loop
 * @version 0.1
 * @date 2021-11-26
 * @copyright Copyright (c) 2021
 */

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "../game/core.h"

/**
 * @brief Structure containing the list of players.
 * Structure containing the list of players.
 */
typedef struct {
    player *clients;
    int client_count;
} clients_list;

extern clients_list clientsList;

/**
 * @brief Initialize the server.
 * Initialize the server.
 * @param ip Listening IP
 * @param port Listening port
 * @return socket of the server
 */
int create_server(char *ip, int port);

/**
 * @brief Listening loop, waiting for new connections.
 * Listening loop, waiting for new connections.
 * @param socketfd Socket of the server
 */
void *listening(void *socketfd);

/**
 * @brief Initialize client list
 * Initialize client list
 * @param clients List of clients
 */
void init_client_list(clients_list *clients);

/**
 * @brief Add a client to the list
 * Add a client to the list
 * @param clients List of clients
 * @param client Client to add
 */
void add_client(clients_list *clients, player client);

/**
 * @brief Remove a client from the list
 * Remove a client from the list
 * @param clients List of clients
 * @param socket fd Socket of the client
 */
void remove_client(clients_list *clients, int socket);

/**
 * @brief Randomize pair of players from the global player list
 * Randomize pair of players from the global player list
 * @return Pair of players
 */
int *randomize_pairs();

/**
 * @brief Monitor pair of players and launch party from the pair
 * Monitor pair of players and launch party from the pair
 */
void *handle_clients();

/**
 * @brief This is the core of the game, it's the main loop of the game
 * This is the core of the game, it's the main loop of the game
 * Game logic, results monitoring
 * @param ptr Player pair as void pointer
 */
void *thread_party(void *ptr);

/**
 * @brief Check if the players want to play again
 * @param p1 First player
 * @param p2 Second player
 */
void player_wanted_replay(player p1, player p2);

#endif //SERVER_SERVER_H
