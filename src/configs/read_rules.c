/**
 * @file read_rules.c
 * @author Nicola Piemontese
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../headers/configs/read_rules.h"
#include "../../headers/utils/files_utils.h"
#include "../../headers/game/core.h"

/**
 * @brief initialize struct rules with rules_config.json
 * 
 */
void read_rules()
{
    //printf("Read rules:\n");
    if( access( "../config/rules_config.json", F_OK ) != -1)
    {
        rules rules;
        FILE * file_rule = fopen("../config/rules_config.json", "r");
        
        char * nb_round = malloc(sizeof(char) * 20);
        parse_json("nb_round", nb_round, file_rule);
        rules.nb_round = atoi(nb_round);

        char * default_wallet = malloc(sizeof(char) * 20);
        parse_json("default_wallet", default_wallet, file_rule);
        rules.default_wallet = atoi(default_wallet);

        char * trahison_win = malloc(sizeof(char) * 20);
        parse_json("trahison_win", trahison_win, file_rule);
        rules.trahison_win = atoi(trahison_win);

        char * trahison_loose = malloc(sizeof(char) * 20);
        parse_json("trahison_loose", trahison_loose, file_rule);
        rules.trahison_loose = atoi(trahison_loose);

        char * collab_win = malloc(sizeof(char) * 20);
        parse_json("collab_win", collab_win, file_rule);
        rules.collab_win = atoi(collab_win);

        char * collab_loose = malloc(sizeof(char) * 20);
        parse_json("collab_loose", collab_loose, file_rule);
        rules.collab_loose = atoi(collab_loose);

        char * trahison_collab_win = malloc(sizeof(char) * 20);
        parse_json("trahison_collab_win", trahison_collab_win, file_rule);
        rules.trahison_collab_win = atoi(trahison_collab_win);

        char * trahison_collab_loose = malloc(sizeof(char) * 20);
        parse_json("trahison_collab_loose", trahison_collab_loose, file_rule);
        rules.trahison_collab_loose = atoi(trahison_collab_loose);

        /*
        printf("1 : %d\n", rules.nb_round);
        printf("2 : %d\n", rules.trahison_win);
        printf("3 : %d\n", rules.trahison_loose);
        printf("4 : %d\n", rules.collab_win);
        printf("5 : %d\n", rules.collab_loose);
        printf("6 : %d\n", rules.trahison_collab_win);
        printf("7 : %d\n", rules.trahison_collab_loose);
        */
        
        free(nb_round);
        free(trahison_win);
        free(trahison_loose);
        free(collab_win);
        free(collab_loose);
        free(trahison_collab_win);
        free(trahison_collab_loose);
        fclose(file_rule);

    }
    else
    {
        printf("Error: rules_config.json not found\n");
        exit(1);
    }
}