//
// Created by Yannis Teissier on 13/11/2021.
//

#pragma once

#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

/**
 * Max commands that can be define in the command_list structure
 * @brief Maximum commands in command_list
 */
#define MAX_COMMANDS 100

/**
 * Command permit to the server to communicate with the client
 * @brief Command structure
 */
typedef struct {
    char *name;
    char *args;
} command;

/**
 * The list of command permit to stack every command the server use to communicate with the client
 * @brief List of commands
 */
typedef struct {
    command *commands;
    size_t size;
} command_list;

/**
 * Initialize the command list
 * @param list command_list struct
 */
void init_command_list(command_list *list);

/**
 * Add command to the list
 * @param cmd_list command_list struct
 * @param cmd command struct
 */
void add_command(command_list *cmd_list, char *name, char *args);

/**
 * Return command from name
 * @param cmd_list command_list struct
 * @param cmd_name name of the command
 * @return null if not found | command struct
 */
command find_command(char *cmd_name);

/**
 * Setup command list and commands
 * @brief Setup command list and commands
 */
void setup_commands();

/**
 * Execute callback function from command
 * @brief Execute callback function from command
 * @param command command struct
 * @param arguments arguments of the command
 */
void call_command(command command, char *arguments);

/**
 * Debug method to print the command list
 * @brief Debug method to print the command list
 */
void help();

void answer(char * arguments);

#endif //SERVER_COMMANDS_H
