/**
 * @file core.h
 * @author Teissier Yannis
 * @brief This file is the core of the game logic
 * @version 0.1
 * @date 2021-11-17
 * @copyright Copyright (c) 2021
 */

#include <stdlib.h>
#include <stdio.h>
#include "../../headers/game/core.h"
#include "../../headers/configs/read_rules.h"

// Methods

/**
 * @brief Initialize the game struct
 * Initialize game struct
 * set players_count to 0
 * set parties_count to 0
 */
void init_game() {
    // Initialize game struct
    game0.parties_count = 0;
    game0.players_count = 0;
    game0.player = malloc(sizeof(player) * 20);
    game0.parties = malloc(sizeof(party) * 20);

    read_rules(&rules0);
}


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
void init_player(player *player0, int socket) {
    game0.players_count += 1;
    int count = game0.players_count;
    player0->id = count;
    player0->status = 0;
    player0->wallet = rules0.default_wallet;
    player0->socket = socket;
    game0.player[count] = *player0;
}

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
void init_party(party *party0, player player1, player player2) {
    game0.parties_count += 1;
    int count = game0.parties_count;

    party0->id = count;
    party0->round_count = 0;

    party0->player_game = malloc(sizeof(player) * 20);
    party0->player_game[0] = player1;
    party0->player_game[1] = player2;
    game0.parties[count] = *party0;
}

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
                int round_count, int p1Wallet, int p2Wallet) {
    round->p1_result = p1_result;
    round->p2_result = p2_result;

    round->p1_decision_time = p1_decision_time;
    round->p2_decision_time = p2_decision_time;

    round->p1_wallet = p1Wallet;
    round->p2_wallet = p2Wallet;

    // Pas besoin d'envoyer le temps de décision au client
    round->status = status;
    round->round_number = round_count;

}

/**
 * @brief add round to party
 * Add round to party
 * @param party party to update
 * @param round round to add
 */
void add_round_to_party(party *party, round *round0) {
    int count = party->round_count;
    //init_round(party->round[count], round0->p1_result, round0->p1_decision_time, round0->p2_result, round0->p2_decision_time, round0->status, round0->round_number);
    party->round[count] = *round0;
    party->round_count += 1;
}

/**
 * @brief Generating recapitulation of the party
 * Generating recapitulation of the party
 * @brief Generating recapitulation of the party
 * @param party party to generate recap
 * @return recap of the party
 */
recap generating_recap(party *party) {
    recap recap;

    printf("========================================================\n");

    // 3:P1{1,0,10;2,1,25;3,0,2},P2{1,0,10;2,1,25;3,0,2}

    for (int i = 0; i < party->round_count; i++) {

        printf("Round %d\n", i + 1);
        printf("Player 1 : %d\n", party->round[i].p1_result);
        printf("en %d secondes\n", party->round[i].p1_decision_time);
        printf("Player 2 : %d\n", party->round[i].p2_result);
        printf("en %d secondes\n", party->round[i].p2_decision_time);
        printf("\n");

        answer_struct answer_p1 = {party->id, party->player_game->id, party->round[i].p1_result,
                                   party->round[i].p1_decision_time};
        answer_struct answer_p2 = {party->id, party->player_game->id, party->round[i].p2_result,
                                   party->round[i].p2_decision_time};

        recap.list_answer_J1[i] = answer_p1;
        recap.list_answer_J2[i] = answer_p2;
    }
    recap.nb_round = party->round_count;
    printf("========================================================\n");
    return recap;
}

/**
 * @brief Initialize answer struct
 * Initialize answer struct
 * @param answer answer to initialize
 */
void init_answer(answer_struct *answer) {
    answer->player_id = 0;
    answer->choice = 0;
    answer->time = 0;
}