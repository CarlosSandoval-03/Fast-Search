#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include "./client.h"
#include "../protocol/protocol.h"

void forced_disconnection_handler(const int signal, void *sock_conn)
{
	static int *client_fd = NULL;

	if (client_fd == NULL)
		client_fd = (int *)sock_conn;
	if (signal == FAKE_SIGNAL)
		return;

	int disconnection_signal = CLIENT_CONNECTION;
	send(*client_fd, &disconnection_signal, sizeof(disconnection_signal), 0);
	printf("DISCONNECTING...\n");

	close(*client_fd);
	exit(EXIT_FAILURE);
}