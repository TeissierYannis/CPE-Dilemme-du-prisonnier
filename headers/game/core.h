/**
 * @file core.h
 * @author Teissier Yannis
 * @brief This file is the core of the game logic
 * @version 0.1
 * @date 2021-11-17
 * @copyright Copyright (c) 2021
 */

#ifndef SERVER_CORE_H
#define SERVER_CORE_H

#pragma once

/**
 * @brief Contains the rules of the game
 * Contains the rules of the game
 */
typedef struct {
    int nb_round;
    int default_wallet;
    int trahison_win;
    int trahison_loose;
    int collab_win;
    int collab_loose;
    int trahison_collab_win;
    int trahison_collab_loose;
} rules;

/**
 * @brief Contains the player informations
 * Contains the player informations
 */
typedef struct {
    int id;
    int status;
    int wallet;
    int socket;
} player;

/**
 * @brief Contains round informations
 * Contains round informations
 */
typedef struct {
    // Resultat de chaque joueur
    int p1_result; // choix
    int p1_wallet; // score
    int p2_result; // choix
    int p2_wallet; // score
    // Le temps
    int p1_decision_time;
    int p2_decision_time;
    //  int p2_choice;
    // Numero du round
    int round_number;
    int status;
} round;

/**
 * @brief Contains party informations
 * Contains party informations
 */
typedef struct {
    int id;
    player *player_game;
    round round[100];
    int round_count;
} party;

/**
 * Contains the game informations
 */
typedef struct {
    player *player;
    int players_count;
    party *parties;
    int parties_count;
} game;

/**
 * @brief Contains answer informations
 * Contains answer informations
 */
typedef struct {
    int party_id;
    int player_id;
    int choice;
    int time;
} answer_struct;

/**
 * @brief Contains recap informations
 * Contains recap informations
 */
typedef struct {
    int nb_round;
    answer_struct list_answer_J1[10];
    answer_struct list_answer_J2[10];
} recap;

// Test debug
typedef struct {
    char out[256];
} Buffer_out;

extern rules rules0;
extern game game0;

/**
 * @brief Initialize the game struct
 * Initialize game struct
 * set players_count to 0
 * set parties_count to 0
 */
void init_game();

/**
 * @brief Initialize player struct
 * Initialize player struct
 * set id to (struct game) players_count + 1
 * and add it to the game (struct)
 * set ip to the ip of the client
 * set status to 0 (waiting for a player)
 * @param p structure player
 * @param ip ip of the client
 */
void init_player(player *player, int socket);

/**
 * @brief Initialize party struct
 * Initialize party struct
 * set id to (struct game) party_count + 1
 * add it to the game (struct)
 * add players to party
 * set round_count to 0
 * @param party party to initialize
 * @param player1 p1
 * @param player2 p2
 */
void init_party(party *party0, player player1, player player2);

/**
 * @brief Initialize round struct
 * Initialize round struct
 * @param round round to initialize
 * @param p1_result (0 or 1)
 * @param p1_decision_time time of p1 decision (timestamp)
 * @param p2_result (0 or 1)
 * @param p2_decision_time time of p2 decision (timestamp)
 */
void init_round(round *round, int p1_result, int p1_decision_time, int p2_result, int p2_decision_time, int status,
                int round_number, int p1Wallet, int p2Wallet);

/**
 * @brief add round to party
 * Add round to party
 * @param party party to update
 * @param round round to add
 */
void add_round_to_party(party *party, round *round);

/**
 * @brief Generating recapitulation of the party
 * Generating recapitulation of the party
 * @brief Generating recapitulation of the party
 * @param party party to generate recap
 * @return recap of the party
 */
recap generating_recap(party *party);

/**
 * @brief Initialize answer struct
 * Initialize answer struct
 * @param answer answer to initialize
 */
void init_answer(answer_struct *answer);

#endif //SERVER_CORE_H