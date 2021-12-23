/**
 * @file core.h
 * @author Teissier Yannis
 * @brief This file is the core of the game logic
 * @version 0.1
 * @date 2021-11-13
 * @copyright Copyright (c) 2021
 */
 
#include <string.h>


/**
 * Remove char from string
 * @param str  string
 * @param ch   char to remove
 */
void remchar(char *str, char ch) {
    int i, j, len;

    len = strlen(str);

    for (i = 0; i < len; i++)
        if (str[i] == ch) {
            for (j = i; j < len; j++)
                str[j] = str[j + 1];
            len--;
            i--;
        }
}