//
// Created by Yannis Teissier on 17/11/2021.
//

#include "../../headers/game/core.h"


// Methods

/**
 * Initialize game struct
 * set players_count to 0
 * set parties_count to 0
 */
void init_game(game *game)
{
    game->parties_count = 0;
    game->players_count = 0;

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
void init_player(game *game, player *player, char *ip)
{
    game->players_count += 1;
    int count = game->players_count;
    //player->id = count;
    
    //game->player[game->players_count] = *player;
    //player->id = &ip;
    //player->status = 0;
    //player->wallet = rules.default_wallet;
}