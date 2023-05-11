#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "./menu/menu.h"
#include "./client/client.h"
#include "./socket/socket.h"
#include "./protocol/protocol.h"

int main(int argc, char *argv[])
{
	int client_fd = create_socket();

	// Get the host and port from the command line arguments or use the default values
	char *host = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
	unsigned int port = SERVER_PORT;
	strcpy(host, SERVER_HOST);
	if (argc >= 2) {
		strncpy(host, argv[1], INET_ADDRSTRLEN);
	}
	if (argc >= 3) {
		char *end_ptr;
		port = (unsigned int)strtol(argv[2], &end_ptr, 10);
	}

	// Connect to the server
	socket_connect_client(client_fd, host, port);

	// Wait server conn confirmation
	int server_msg;
	secure_recv_int(client_fd, &server_msg);
	if (server_msg != SERVER_CONN_CONFIRMATION) {
		perror("CLIENT: ERROR WHEN CONNECTING TO THE SERVER\n");
		exit(EXIT_FAILURE);
	}

	// Send client conn confirmation
	server_msg = CLIENT_CONN_CONFIRMATION;
	secure_send_int(client_fd, server_msg);

	// Show main menu
	main_menu(client_fd);

	close(client_fd);
	free(host);
	return EXIT_SUCCESS;
}