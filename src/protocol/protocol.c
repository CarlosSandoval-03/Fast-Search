#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include "./protocol.h"

void int_to_string(int value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%d", value);
}

void long_to_string(long value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%ld", value);
}

void float_to_string(float value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%f", value);
}

void secure_send(int socket_fd, const char *string)
{
	size_t size = strlen(string) + 1;
	size_t net_size = htonl(size);

	if (send(socket_fd, &net_size, sizeof(net_size), 0) < 0) {
		perror("SEND: ERROR WHEN SENDING THE SIZE OF THE STRING\n");
		return;
	}

	if (send(socket_fd, string, size, 0) < 0) {
		perror("SEND: ERROR WHEN SENDING THE STRING\n");
		return;
	}
}

void secure_send_int(int socket_fd, int value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

void secure_send_long(int socket_fd, long value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	long_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

void secure_send_float(int socket_fd, float value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	float_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

void secure_recv_string(int socket_fd, char *buffer, size_t size_buffer)
{
	size_t net_size;
	if (recv(socket_fd, &net_size, sizeof(net_size), 0) < 0) {
		perror("RECV: ERROR WHEN RECEIVING THE SIZE OF THE STRING\n");
		return;
	}

	size_t size = ntohl(net_size);
	if (size > size_buffer) {
		perror("RECV: ERROR WHEN RECEIVING THE STRING\n");
		return;
	}

	if (recv(socket_fd, buffer, size, 0) < 0) {
		perror("RECV: ERROR WHEN RECEIVING THE STRING\n");
		return;
	}
}

void secure_recv_int(int socket_fd, int *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atoi(buffer);
}

void secure_recv_long(int socket_fd, long *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atol(buffer);
}

void secure_recv_float(int socket_fd, float *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atof(buffer);
}