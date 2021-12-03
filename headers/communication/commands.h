//
// Created by Yannis Teissier on 13/11/2021.
//

#pragma once

#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

typedef void (*command_function)(char *);

typedef struct {
    int party_id;
    int player_id;
    int choice;
    int time;
} answer_struct;

typedef struct {
    int j1_result;
    int j2_result;
    int round_number;
    char status[20];
} round_result;

struct {
    round_result * round;
    int j1_score;
    int j2_score;
} final_result;

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

void init_answer(answer_struct *answer);

/**
 * Add command to the list
 * @param cmd_list command_list struct
 * @param cmd command struct
 */
void add_command(command_list *cmd_list, char *name);

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
command_function call_command(command command);

/**
 * Parse answer from string
 * @brief Parse answer from string
 * @param answer _str string of the answer
 * @param answerStruct answer_struct struct
 */
void parse_answer(char * answer, answer_struct * answerStruct);

/**
 * Debug method to print the command list
 * @brief Debug method to print the command list
 */
void help();

/**
 * Receive message to the client
 * Join a party
 */
void join();
/**
 * Send message to the client
 * Start a party
 * @param party_id
 */
void start(char * party_id);
/**
 * Send message to the client
 * Launch next round
 */
void next_round();
/**
 * Send message to the client
 * End the game
 */
void end_game();

/**
 * Receive message to the client
 * Interpret the answer of the player
 * @param answer
 */
void answer(char * answer);

#endif //SERVER_COMMANDS_H
