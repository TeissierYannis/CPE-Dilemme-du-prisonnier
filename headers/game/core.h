//
// Created by Yannis Teissier on 17/11/2021.
//

// TODO : Modifier les regles avec de l'argent (un wallet)

#ifndef SERVER_CORE_H
#define SERVER_CORE_H

typedef struct 
{
    int nb_round;
    int default_wallet;
    int trahison_win;
    int trahison_loose;
    int collab_win;
    int collab_loose;
    int trahison_collab_win;
    int trahison_collab_loose;

} rules;


typedef struct {
    int id;
    int status;
    int wallet;
    int ip;
} player;

typedef struct {
    int p1_result;
    int p1_decision_time;
    int p2_result;
    int p2_decision_time;
} round;

typedef struct {
    int id;
    player * player;
    round * round;
    int round_count;
} party;

typedef struct {
    player * player;
    int players_count;
    party * parties;
    int parties_count;
} game;



/**
 * Initialize game struct
 * set players_count to 0
 * set parties_count to 0
 */
void init_game(game *game);

/**
 * Initialize player struct
 * set id to (struct game) players_count + 1
 * and add it to the game (struct)
 * set ip to the ip of the client
 * set status to 0 (waiting for a player)
 * @param p structure player
 * @param ip ip of the client
 */
void init_player(game *game, player *player, char * ip);

/**
 * Initialize party struct
 * set id to (struct game) party_count + 1
 * add it to the game (struct)
 * add players to party
 * set round_count to 0
 * @param party party to initialize
 * @param player1 p1
 * @param player2 p2
 */
void init_party(party * party, player player1, player player2);

/**
 * Initialize round struct
 * @param round round to initialize
 * @param p1_result (0 or 1)
 * @param p1_decision_time time of p1 decision (timestamp)
 * @param p2_result (0 or 1)
 * @param p2_decision_time time of p2 decision (timestamp)
 */
void init_round(round * round, int p1_result, int p1_decision_time, int p2_result,  int p2_decision_time);

/**
 * Add round to party
 * @param party party to update
 * @param round round to add
 */
void add_round_to_party(party * party, round round);

/**
 * Destroy player struct when player is leaving
 * Remove player from game struct
 * Remove player struct
 * @param player player who is leaving
 */
void destroy_player(player * player);

/**
 * Destroy party struct when party is finished
 * @param party party to remove
 */
void destroy_party(party * party);

/**
 * Destroy game struct when server will be closed
 */
void destroy_game();

#endif //SERVER_CORE_H
