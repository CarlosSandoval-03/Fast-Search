#ifndef _SERVER_H_
#define _SERVER_H_

#define MAX_CONNS 32
#define HOST "127.0.0.1"
#define PORT 8080

#define THREAD_POOL_SIZE 8

#include <pthread.h>
#include "../structures/structures.h"

int server_start_listen(int server_fd, int max_conns);
void create_queue_conn(int queue_fd[2], queue_conn_t *queue_conn_struct);
void server_accept_client(int server_fd, queue_conn_t *queue_conns);
pthread_t *create_thread_pool(queue_conn_t *queue_conns);
void join_thread_pool(pthread_t *thread_pool);

#endif // !_SERVER_H_