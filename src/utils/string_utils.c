//
// Created by Yannis Teissier on 13/11/2021.
//
#include <string.h>


/**
 * Remove char from string
 * @param str  string
 * @param ch   char to remove
 */
void remchar(char *str, char ch)
{
    int i, j, len;

    len = strlen(str);

    for(i = 0; i < len; i++)
        if(str[i] == ch)
        {
            for(j = i; j < len; j++)
                str[j] = str[j + 1];
            len--;
            i--;
        }
}