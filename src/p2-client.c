#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "./client/client.h"
#include "./socket/socket.h"

int main(int argc, char *argv[])
{
	int client_fd = create_socket();

	// Get the host and port from the command line arguments or use the default values
	char *host = SERVER_HOST;
	unsigned int port = SERVER_PORT;
	if (argc >= 2) {
		host = argv[1];
	}
	if (argc >= 3) {
		char *end_ptr;
		port = (unsigned int)strtol(argv[2], &end_ptr, 10);
	}

	// Connect to the server
	socket_connect_client(client_fd, host, port);

	char buffer[12];
	recv(client_fd, buffer, 12, 0);
	buffer[11] = '\0';

	printf("RECEIVED MESSAGE: %s\n", buffer); // TODO: Remove

	send(client_fd, "Hello world\n", 12, 0);
	printf("SENT MESSAGE\n"); // TODO: Remove

	close(client_fd);
	return EXIT_SUCCESS;
}