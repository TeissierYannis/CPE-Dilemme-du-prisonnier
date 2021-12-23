/**
 * @file outils.c
 * @author REVOL Alexis (alexis.revol@cpe.fr)
 * @brief
 * @version 0.1
 * @date 2021-23-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../headers/outils.h"
 
 /**
 * @brief Comparer 2 chaine de caracteres
 * @return bool
 */
bool are_equal(char *key, char *name) {
    bool result = false;
    // Si la clé correspond au nom indiqué
    if (strcmp(key, name) == 0) {
        result = true;
    }
    return result;
}


