#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "./server.h"
#include "../socket/socket.h"

int server_start_listen(int server_fd, int max_conns)
{
	int listen_status = listen(server_fd, max_conns);
	if (listen_status < 0) {
		perror("LISTEN: ERROR WHEN START LISTENING\n");
		exit(EXIT_FAILURE);
	}

	return listen_status;
}

int server_accept_client(int server_fd)
{
	struct sockaddr_in client_conf;
	socklen_t socklen;

	int client_fd = accept(server_fd, (struct sockaddr *)&client_conf, (socklen_t *)&socklen);
	if (client_fd < 0) {
		perror("CLIENT: THE CLIENT DESCRIPTOR WAS NOT OBTAINED\n");
		exit(EXIT_FAILURE);
	}

	return client_fd;
}
