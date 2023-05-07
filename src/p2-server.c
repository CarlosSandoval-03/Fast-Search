#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

	// Create the server socket and bind it to the port
	int server_fd = create_socket();
	socket_bind_server(server_fd, port);

	// Start listening for connections
	printf("START TO LISTEN IN PORT: %u\n", port); // TODO: Remove
	server_start_listen(server_fd, MAX_CONNS);

	while (1) {
		int client_fd = server_accept_client(server_fd);
		printf("ACCEPTED CLIENT\n"); // TODO: Remove

		send(client_fd, "Hello world\n", 12, 0);
		printf("SENT MESSAGE\n"); // TODO: Remove

		char buffer[12];
		recv(client_fd, buffer, 12, 0);
		buffer[11] = '\0';

		printf("RECEIVED MESSAGE: %s\n", buffer); // TODO: Remove

		close(client_fd);
	}

	close(server_fd);
	printf("END SERVER\n"); // TODO: Remove
	return EXIT_SUCCESS;
}