//
// Created by Yannis Teissier on 17/11/2021.
//

#include <stdlib.h>
#include "../../headers/game/core.h"

// Methods

/**
 * Initialize game struct
 * set players_count to 0
 * set parties_count to 0
 */
void init_game(game * game0)
{
    game0->parties_count = 0;
    game0->players_count = 0;
    game0->player = malloc(sizeof(player) *20);
    game0->parties = malloc(sizeof(party) * 20);

}


/**
 * Initialize player struct
 * set id to (struct game) players_count + 1
 * and add it to the game (struct)
 * set ip to the ip of the client
 * set status to 0 (waiting for a player)
 * @param p structure player
 * @param ip ip of the client
 */
void init_player(game *game0, player *player0, char *ip0, rules * rules0)
{
    game0->players_count += 1;
    int count = game0->players_count;
    player0->id = count;
    player0->status = 0;
    player0->wallet = rules0->default_wallet;
    player0->ip = ip0;
    game0->player[count] = *player0;
}

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
void init_party(game *game0, party * party0, player player1, player player2)
{
    game0->parties_count +=1;
    int count = game0->parties_count;

    party0->id = count;
    party0->round_count = 0;

    party0->player_game = malloc(sizeof(player)*20);
    party0->player_game[0] = player1;
    party0->player_game[1] = player2;
    game0->parties[count] = *party0;
}

