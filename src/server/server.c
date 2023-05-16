#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "./server.h"
#include "../search/search.h"
#include "../socket/socket.h"
#include "../logger/logger.h"
#include "../protocol/protocol.h"
#include "../structures/structures.h"

pthread_mutex_t mutex_conns;
int ACTUAL_CONNS = 0;

void create_queue_conns(int queue_fd[2], queue_conn_t *queue_conn)
{
	int queue_status = pipe(queue_fd);
	if (queue_status < 0) {
		perror("CREATE_QUEUE_CONNS: ERROR WHEN CREATE THE QUEUE CONNECTIONS\n");
		exit(EXIT_FAILURE);
	}

	queue_conn->dequeue = queue_fd[0];
	queue_conn->enqueue = queue_fd[1];
}

void enqueue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn)
{
	int queue_status = write(queue_conns->enqueue, client_conn, sizeof(*client_conn));
	if (queue_status < 0) {
		perror("QUEUE: ERROR WHEN WRITING TO THE QUEUE\n");
	}
}

void dequeue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn)
{
	int queue_status = read(queue_conns->dequeue, client_conn, sizeof(*client_conn));
	if (queue_status < 0) {
		perror("QUEUE: ERROR WHEN READING FROM THE QUEUE\n");
	}

	// Log the client connection (is executed by worker thread)
	pthread_mutex_lock(&mutex_conns);
	ACTUAL_CONNS++;
	pthread_mutex_unlock(&mutex_conns);
}

int server_start_listen(int server_fd, int max_conns)
{
	int listen_status = listen(server_fd, max_conns);
	if (listen_status < 0) {
		perror("LISTEN: ERROR WHEN START LISTENING\n");
		exit(EXIT_FAILURE);
	}

	return listen_status;
}

void server_accept_client(int server_fd, client_conn_t *client_conn, queue_conn_t *queue_conns)
{
	struct sockaddr_in client_conf;
	socklen_t socklen = sizeof(client_conf);

	int client_fd = accept(server_fd, (struct sockaddr *)&client_conf, (socklen_t *)&socklen);
	if (client_fd < 0) {
		perror("ACCEPT_CLIENT: THE CLIENT DESCRIPTOR WAS NOT OBTAINED\n");
	}

	// Send the client cache conn to the queue
	client_conn->client_fd = client_fd;

	memset(client_conn->client_ip, 0, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &(client_conf.sin_addr), (client_conn->client_ip), INET_ADDRSTRLEN);
	enqueue_conn(queue_conns, client_conn);

	// Log the client connection
	log_client_connect(client_conn->client_ip);
}

void secure_disconnect_client(client_conn_t *client_conn)
{
	log_client_disconnect(client_conn->client_ip);

	int client_fd = client_conn->client_fd;
	close(client_fd);
	free(client_conn);

	// Log the client disconnection (is disconnected by worker thread)
	pthread_mutex_lock(&mutex_conns);
	ACTUAL_CONNS--;
	pthread_mutex_unlock(&mutex_conns);
}

void *worker_routine(void *args)
{
	client_conn_t *client_conn = (client_conn_t *)args;
	pthread_t self = pthread_self();

	// Send server_conn_confirmation
	secure_send_int(client_conn->client_fd, SERVER_CONN_CONFIRMATION);

	// Receive client_conn_confirmation
	int client_msg;
	secure_recv_int(client_conn->client_fd, &client_msg);
	if (client_msg != CLIENT_CONN_CONFIRMATION) {
		perror("CLIENT_CONN_CONFIRMATION: THE CLIENT DID NOT SEND THE CORRECT MESSAGE\n");
		secure_disconnect_client(client_conn);

		pthread_cancel(self);
		return NULL;
	}

	// Start search process
	cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
	cache->srcid = 0;
	cache->dstid = 0;
	cache->hod = -1;

	int flag = EXIT_SUCCESS;
	while (flag != EXIT_FAILURE) {
		flag = search_actions(client_conn, cache);
	}

	free(cache);
	secure_disconnect_client(client_conn);
	pthread_cancel(self);
	return NULL;
}

void create_worker_thread(client_conn_t *client_conn, pthread_t *worker_thread)
{
	int thread_status = pthread_create(worker_thread, NULL, worker_routine, (void *)client_conn);
	if (thread_status < 0) {
		perror("WORKER: ERROR WHEN CREATING THE WORKER THREAD\n");
		secure_disconnect_client(client_conn);
	}
}

void *scheduler_routine(void *args)
{
	queue_conn_t *queue_conns = (queue_conn_t *)args;

	while (1) {
		client_conn_t *client_conn = (client_conn_t *)malloc(sizeof(client_conn_t));
		dequeue_conn(queue_conns, client_conn);

		if (ACTUAL_CONNS > MAX_CONNS) {
			secure_send_int(client_conn->client_fd, SERVER_CONN_REJECTION);
			secure_disconnect_client(client_conn);
			continue;
		}

		pthread_t *worker_thread = (pthread_t *)malloc(sizeof(pthread_t));
		create_worker_thread(client_conn, worker_thread);
	}

	return NULL;
}

void create_scheduler_thread(queue_conn_t *queue_conns, pthread_t *scheduler_thread)
{
	int thread_status = pthread_create(scheduler_thread, NULL, scheduler_routine, (void *)queue_conns);
	if (thread_status < 0) {
		perror("SCHEDULER: ERROR WHEN CREATING THE SCHEDULER THREAD\n");
		exit(EXIT_FAILURE);
	}
}