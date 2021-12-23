/**
 * @file core.h
 * @author Teissier Yannis
 * @brief This file is the core of the game logic
 * @version 0.1
 * @date 2021-11-17
 * @copyright Copyright (c) 2021
 */

#ifndef SERVER_FILES_UTILS_H
#define SERVER_FILES_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

/**
 * Initialize json parsing to key:value
 * @brief Initialize json parsing to key:value
 * @param server_config config file
 */
void parse_json(char *search_key, char *to_assign, FILE *config_file);

#endif //SERVER_FILES_UTILS_H
