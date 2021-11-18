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
void add_command(command_list *cmd_list, char *name, char *args) {
    // init command
    command new_command;
    // init command name
    new_command.name = name;
    // init command args
    new_command.args = args;

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
    add_command(&COMMAND_LIST, "help", NULL);
    add_command(&COMMAND_LIST, "answer", "userid answer");
}

/**
 * Execute callback function from command
 * @brief Execute callback function from command
 * @param command command struct
 * @param arguments arguments of the command
 */
void call_command(command command, char * arguments) {
    // if command is help
    if (strcmp(command.name, "help") == 0) {
        // print help
        help();
    } else if (strcmp(command.name, "answer") == 0) {
        // print answer
        answer(arguments);
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
 * TODO Comment and method body
 * Parse command
 * @brief Parse command
 * @param command_name
 * @param arguments
 */
void answer(char * arguments) {

    printf("\n[COMMAND][DEBUG] AnswerFunction : %s\n", arguments);

    // split arguments
    char * token = strtok(arguments, " ");
    int user_id = atoi(token);

    // get answer
    token = strtok(NULL, " ");
    char * user_answer = token;

    printf("[COMMAND][DEBUG] User id : %d\n", user_id);
    printf("[COMMAND][DEBUG] Answer : %s\n", user_answer);
}

void logout(char * arguments) {
    printf("[COMMAND][DEBUG] LogoutFunction : %s", arguments);

    char * token = strtok(arguments, " ");
    int user_id = atoi(token);

    printf("[COMMAND][DEBUG] User id : %d", user_id);
}