/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _SERVER_H_
#define _SERVER_H_

#define MAX_CONNS 32
#define HOST "127.0.0.1"
#define PORT 8080

#include <pthread.h>
#include "../structures/structures.h"

void create_queue_conns(int queue_fd[2], queue_conn_t *queue_conn);
void enqueue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn);
void dequeue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn);
int server_start_listen(int server_fd, int max_conns);
void server_accept_client(int server_fd, client_conn_t *client_conn, queue_conn_t *queue_conns);
void secure_disconnect_client(client_conn_t *client_conn);
void *worker_routine(void *args);
void create_worker_thread(client_conn_t *client_conn, pthread_t *worker_thread);
void *scheduler_routine(void *args);
void create_scheduler_thread(queue_conn_t *queue_conns, pthread_t *scheduler_thread);

#endif // !_SERVER_H_
