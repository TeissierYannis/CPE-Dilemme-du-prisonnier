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

void read_rules()
{
    printf("Read rules:\n");
    if( access( "../config/rules_config.json", F_OK ) != -1)
    {
        FILE * file_rule = fopen("../config/rules_config.json", "r");

        char * test = malloc(sizeof(char) * 20);
        parse_json("betrayals_win", test, file_rule);
        printf("Test :%s\n", test); 
        /*
        char * nb_round = malloc(sizeof(char) * 20);
        parse_json("nb_round", nb_round, file_rule);
        printf("test%s\n", nb_round);
        //free(nb_round);
        */

        fclose(file_rule);
        
    }
    else
    {
        printf("Error: rules_config.json not found\n");
        exit(1);
    }
    

    /*

    // (test);

    free(ip_address);
    free(test);
    fclose(file_p);
    */
}