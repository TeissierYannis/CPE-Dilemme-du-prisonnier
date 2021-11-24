//
// Created by Yannis Teissier on 13/11/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../headers/communication/commands.h"

command_list COMMAND_LIST;

/**
 * Add command to the command list
 * @brief add command to the command list
 * @param cmd_list
 * @param name
 * @param args
 */
void add_command(command_list *cmd_list, char *name) {
    // init command
    command new_command;
    // init command name
    new_command.name = name;

    // add command to the list
    cmd_list->commands[cmd_list->size] = new_command;
    // increase size
    cmd_list->size++;
}

/**
 * Initialize command list
 * @brief Initialize command list
 * @param cmd_list
 * @param command
 * @return
 */
void init_command_list(command_list *command_list) {
    // init command list
    command_list->commands = malloc(sizeof(command_list) * MAX_COMMANDS);
    // init size
    command_list->size = 0;
}
/**
 * Return command from name
 * @brief Return command from name
 * @param cmd_list command_list struct
 * @param cmd_name name of the command
 * @return null if not found | command struct
 */
command find_command(char *cmd_name) {
    // loop through commands
    for (int i = 0; i < COMMAND_LIST.size; i++) {
        // if command name (from client) is equal to the command name (struct)
        if (strcmp(COMMAND_LIST.commands[i].name, cmd_name) == 0) {
            // return command
            return COMMAND_LIST.commands[i];
        }
    }
    // return null if not found
    return COMMAND_LIST.commands[COMMAND_LIST.size + 2];
}

/**
 * Setup command list and commands
 * @brief Setup command list and commands
 */
void setup_commands() {
    // init command list
    init_command_list(&COMMAND_LIST);
    // register commands
    add_command(&COMMAND_LIST, "help");
    add_command(&COMMAND_LIST, "answer");
    add_command(&COMMAND_LIST, "join");
}

/**
 * Execute callback function from command
 * @brief Execute callback function from command
 * @param command command struct
 * @param arguments arguments of the command
 */
void call_command(command command) {
    // if command is help
    if (strcmp(command.name, "help") == 0) {
        // print help
        help();
    } else if (strcmp(command.name, "answer") == 0) {
        // print answer
        answer();
    }
}


/**
 * Print help
 * @brief Print help
 */
void help() {
    printf("\n=================================\n");
    printf("|\t\tHelp Commands\t\t\t|\n");
    printf("|\t\tNo help\t\t\t\t\t|\n");
    printf("=================================\n\n");
}

// join
// answer <userId> <answer>
// logout <userId>
// allow connexion
// deny connexion
// start <partyId> <roundId>
// result <partyId> <roundId> <result>
// results <partyId> <result>

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
void start(int party_id) {
    printf("\n=================================\n");
    printf("|\t\tStart Party\t\t\t|\n");
    printf("|\t\tParty id: %d\t\t\t\t|\n", party_id);
    printf("=================================\n\n");
}
/**
 * Send message to the client
 * Launch next round
 */
void next_round() {
    printf("\n=================================\n");
    printf("|\t\tNext Round\t\t\t|\n");
    printf("=================================\n\n");
}
/**
 * Send message to the client
 * End the game
 */
void end_game() {
    printf("\n=================================\n");
    printf("|\t\tEnd Game\t\t\t|\n");
    printf("=================================\n\n");
}

/**
 * Receive message to the client
 * Interpret the answer of the player
 * @param answer
 */
void answer(answer_struct answer) {
    printf("\n=================================\n");
    printf("|\t\tAnswer\t\t\t\t|\n");
    printf("|\t\tUser id: %d\t\t\t\t|\n", answer.player_id);
    printf("|\t\tAnswer: %s\t\t\t\t|\n", answer.answer == 1 ? "betray" : "cooperate");
    printf("=================================\n\n");
}