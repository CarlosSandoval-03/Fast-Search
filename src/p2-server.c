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

	// Create the server socket and bind it to the port
	int server_fd = create_socket();
	socket_bind_server(server_fd, port);

	// Start queue for connections
	int queue_fd[2];
	queue_conn_t *queue_conns = (queue_conn_t *)malloc(sizeof(queue_conn_t));
	create_queue_conn(queue_fd, queue_conns);

	// Start listening for connections
	printf("START TO LISTEN IN PORT: %u\n", port); // TODO: Remove
	server_start_listen(server_fd, MAX_CONNS);

	// Create thread pool
	pthread_t *thread_pool = create_thread_pool(queue_conns);

	while (1) {
		server_accept_client(server_fd, queue_conns);
	}

	// Join thread pool
	join_thread_pool(thread_pool);

	close(server_fd);
	free(queue_conns);
	return EXIT_SUCCESS;
}