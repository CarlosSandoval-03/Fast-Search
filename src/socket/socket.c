/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./socket.h"
#include "../server/server.h"

/**
 * @brief Create a socket object
 * @return int File descriptor of the socket
 */
int create_socket()
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("SOCKET: FAILED TO CREATE THE SOCKET\n");
		exit(EXIT_FAILURE);
	}

	return socket_fd;
}

/**
 * @brief Bind a server socket to a port
 * @param server_fd File descriptor of the socket
 * @param port Port to bind the socket
 * @return int Status of the bind
 */
int socket_bind_server(int server_fd, unsigned int port)
{
	// Enable option SO_REUSEADDR - Avoids the error "Address already in use"
	int optval = 1;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	struct sockaddr_in server_conf;
	server_conf.sin_family = AF_INET;
	server_conf.sin_port = htons(port);
	server_conf.sin_addr.s_addr = INADDR_ANY;
	bzero(server_conf.sin_zero, sizeof(server_conf.sin_zero));

	int bind_status = bind(server_fd, (struct sockaddr *)&server_conf, sizeof(struct sockaddr));
	if (bind_status < 0) {
		perror("BIND: ERROR PERFORMING THE BIND\n");
		exit(EXIT_FAILURE);
	}

	return bind_status;
}

/**
 * @brief Configure the socket to connect to a server
 * @param client_fd File descriptor of the socket
 * @param host Host to connect
 * @param port Port to connect
 * @return int Status of the connection
 */
int socket_connect_client(int client_fd, char *host, unsigned int port)
{
	struct sockaddr_in client_conf;
	client_conf.sin_family = AF_INET;
	client_conf.sin_port = htons(port);
	inet_aton(host, &client_conf.sin_addr);
	bzero(client_conf.sin_zero, sizeof(client_conf.sin_zero));

	int connect_status = connect(client_fd, (struct sockaddr *)&client_conf, (socklen_t)sizeof(struct sockaddr));
	if (connect_status < 0) {
		perror("CONNECTION: ERROR WHILE CONNECTING THE CLIENT\n");
		exit(EXIT_FAILURE);
	}

	return connect_status;
}