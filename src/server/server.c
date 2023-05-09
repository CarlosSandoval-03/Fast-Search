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
#include "../logger/logger.h"

int server_start_listen(int server_fd, int max_conns)
{
	int listen_status = listen(server_fd, max_conns);
	if (listen_status < 0) {
		perror("LISTEN: ERROR WHEN START LISTENING\n");
	}

	return listen_status;
}

int server_accept_client(int server_fd)
{
	struct sockaddr_in client_conf;
	socklen_t socklen = sizeof(client_conf);

	int client_fd = accept(server_fd, (struct sockaddr *)&client_conf, (socklen_t *)&socklen);
	if (client_fd < 0) {
		perror("ACCEPT_CLIENT: THE CLIENT DESCRIPTOR WAS NOT OBTAINED\n");
	}

	char client_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(client_conf.sin_addr), client_ip, INET_ADDRSTRLEN);
	log_client_connect(client_ip);

	return client_fd;
}
