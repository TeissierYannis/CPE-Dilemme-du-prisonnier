//
// Created by Yannis Teissier on 12/11/2021.
//

// TODO REMOVE THIS FILE

#pragma once

#ifndef CLIENT_COMMUNICATION_TRANSLATER_H
#define CLIENT_COMMUNICATION_TRANSLATER_H

/**
 * Interpret incoming messages from the client
 * @param message
 */
void decrypting_incoming_message(char *message);

/**
 * Send message to the client
 * @param message message to send
 */
void sending_message(char *message, int client_socket);

#endif //CLIENT_CONFIGURATOR_H