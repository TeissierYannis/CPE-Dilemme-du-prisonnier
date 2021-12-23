/**
 * @file rules.h
 * @author Nicola Piemontese
 * 
 */
#include "core.h"

/**
 * @brief Update the wallets of players
 * Update the wallets of the players
 * @param choixJ1 the choice of the player 1
 * @param choixJ2 the choice of the player 2
 * @param joueur1 player 1
 * @param joueur2 player 2
 */
void updateWallet(int choixJ1, int choixJ2, player *joueur1, player *joueur2);

/**
 * @brief Get the winner of the game
 * @param joueur1 player 1
 * @param joueur2 player 2
 * @return the winner of the game
 */
int winner(player joueur1, player joueur2);