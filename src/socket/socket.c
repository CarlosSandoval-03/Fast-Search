#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./socket.h"
#include "../server/server.h"

int create_socket()
{
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		perror("SOCKET: FAILED TO CREATE THE SOCKET\n");
		exit(EXIT_FAILURE);
	}

	return socket_fd;
}

int socket_bind_server(int server_fd, unsigned int port)
{
	// Enable option SO_REUSEADDR
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