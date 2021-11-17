#include <stdio.h>
#include <string.h>
#include "../../headers/communication/communication_translater.h"
#include "../../headers/utils/string_utils.h"
#include "../../headers/communication/commands.h"

/**
 * Interpret incoming messages from the client
 * @param message
 */
void decrypting_incoming_message(char *message) {
    // Print base message
    printf("[DEBUG] Message %s\n", message);

    char *command_name;
    char *args;
    // Split message into command and args
    command_name = strtok(message, " ");
    args = strtok(NULL, "\0");

    // remove backslash n to avoid errors
    remchar(command_name, '\n');
    // display command
    printf("[/] %s %s\n", command_name, args);

    // get command
    command cmd = find_command(command_name);

    // if command exists
    if (cmd.name != NULL) {
        call_command(cmd, args);
    } else {
        // if command does not exist
        printf("[ERROR] Command not found\n");
    }
}

