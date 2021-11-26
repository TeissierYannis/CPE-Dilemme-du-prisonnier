/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   srvcxnmanager.h
 * Author: aurelio
 *
 */

#include "../headers/game/core.h"
#pragma once

#ifndef SRVCXNMANAGER_H
#define SRVCXNMANAGER_H

#define BUFFERSIZE 2048
#define MAXSIMULTANEOUSCLIENTS 100


typedef struct {
    int sockfd;
    struct sockaddr address;
    int addr_len;
    int index;
} connection_t;

void init_sockets_array();
void add(connection_t *connection);
void del(connection_t *connection);
void *thread_process(void *ptr);
int create_server_socket() ;
void *thread_party(void *ptr);

#endif /* SRVCXNMANAGER_H */

