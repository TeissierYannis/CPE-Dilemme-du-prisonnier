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
#include "../../headers/configs/read_rules.h"
#include "../../headers/utils/files_utils.h"

void read_rules()
{
    FILE * file_p = fopen("../config/rules_config_temp.json", "r");
    
    char * ip_address = malloc(sizeof(char) * 20);
    parse_json("ip_address", ip_address, file_p);
    printf("ip:%s\n", ip_address);

    char * test = malloc(sizeof(char) * 20);
    parse_json("betrayals_win", test, file_p);
    printf("Test :%s\n", test); 
    // (test);

    free(ip_address);
    free(test);
    fclose(file_p);
}