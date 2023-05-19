/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include "./server/server.h"
#include "./socket/socket.h"

int main(int argc, char *argv[])
{
	// Get the port from the command line arguments or use the default value
	unsigned int port = PORT;
	if (argc >= 2) {
		char *end_ptr;
		port = (unsigned int)strtol(argv[1], &end_ptr, 10);
	}

	// Create queue of connections
	int queue_fd[2];
	queue_conn_t *queue_conn = (queue_conn_t *)malloc(sizeof(queue_conn_t));
	create_queue_conns(queue_fd, queue_conn);

	// Create the server socket and bind it to the port
	int server_fd = create_socket();
	socket_bind_server(server_fd, port);

	// Start listening for connections
	server_start_listen(server_fd, MAX_CONNS);

	// Create a scheduler thread to handle the queue of connections
	pthread_t *scheduler_thread = (pthread_t *)malloc(sizeof(pthread_t));
	create_scheduler_thread(queue_conn, scheduler_thread);
	while (1) {
		client_conn_t *client_conn = (client_conn_t *)malloc(sizeof(client_conn_t));
		server_accept_client(server_fd, client_conn, queue_conn);
	}
}