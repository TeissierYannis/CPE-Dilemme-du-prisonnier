/**
 * @file rules.c
 * @author Nicola Piemontese
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include "../../headers/game/core.h"

void updateWallet(int choixJ1, int choixJ2, player * joueur1, player * joueur2)
{
    // 0: Trahison ; 1: Collab
    //2 Trahisons
    if(choixJ1 == choixJ2  && choixJ1 == 0 )
    {
        joueur1->wallet += rules0.trahison_win;
        joueur2->wallet += rules0.trahison_win;
    }
    //2 Collab
    else if(choixJ1 == choixJ2 && choixJ1 == 1)
    {
        joueur1->wallet += rules0.collab_win;
        joueur2->wallet += rules0.collab_win;
    } 
    //1 Trahison, 1 Collab
    else if(choixJ1 != choixJ2)
    {
        if(choixJ1 == 0)
        {
            joueur1->wallet += rules0.trahison_collab_win;
            joueur2->wallet += rules0.trahison_collab_loose;
        }
        else if(choixJ2 == 0)
        {
            joueur2->wallet += rules0.trahison_collab_win;
            joueur1->wallet += rules0.trahison_collab_loose;
        }
    }
}

int winner_round(int choixJ1, int choixJ2)
{
    int result;
    if(choixJ1 != choixJ2)
    {
        if(choixJ1 == 0)
        {
            result = 0;
        }
        else if(choixJ2 == 0)
        {
            result = 1;
        }
    }
    //Egalité
    else
    {
        result = 2;
    }
    return result;
}

int winner(player joueur1, player joueur2)
{
    int result;
    if(joueur1.wallet > joueur2.wallet)
    {
        result = 1;
    }
    else if(joueur1.wallet < joueur2.wallet)
    {
        result = 2;
    }
    else
    {
        result =0;
    }
    return result;
}
