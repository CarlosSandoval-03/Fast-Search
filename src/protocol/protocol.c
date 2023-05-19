/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>
#include "./protocol.h"

/**
 * @brief This function converts an integer to a string, and stores it in a buffer
 * @param value Integer to be converted
 * @param buffer Buffer where the string will be stored
 * @param buffer_size Size of the buffer
 */
void int_to_string(int value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%d", value);
}

/**
 * @brief This function converts a long to a string, and stores it in a buffer
 * @param value Long to be converted
 * @param buffer Buffer where the string will be stored
 * @param buffer_size Size of the buffer
 */
void long_to_string(long value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%ld", value);
}

/**
 * @brief This function converts a float to a string, and stores it in a buffer
 * @param value Float to be converted
 * @param buffer Buffer where the string will be stored
 * @param buffer_size Size of the buffer
 */
void float_to_string(float value, char *buffer, size_t buffer_size)
{
	snprintf(buffer, buffer_size, "%f", value);
}

/**
 * @brief This function send a string through a socket
 * @param socket_fd Socket file descriptor
 * @param string String to be sent
 * @note First, the function sends the size of the string, in network byte order,
 * and then it sends the string itself.
 * @warning The string must be null-terminated.
 */
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

/**
 * @brief This function send an integer through a socket
 * @param socket_fd Socket file descriptor
 * @param value Integer to be sent
 * @note First, the function converts the integer to a string, and then it sends
 * the string through the socket.
 */
void secure_send_int(int socket_fd, int value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

/**
 * @brief This function send an long through a socket
 * @param socket_fd Socket file descriptor
 * @param value Long to be sent
 * @note First, the function converts the long to a string, and then it sends
 * the string through the socket.
 */
void secure_send_long(int socket_fd, long value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	long_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

/**
 * @brief This function send an float through a socket
 * @param socket_fd Socket file descriptor
 * @param value Float to be sent
 * @note First, the function converts the float to a string, and then it sends
 * the string through the socket.
 */
void secure_send_float(int socket_fd, float value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	float_to_string(value, buffer, BUFFER_SIZE);

	secure_send(socket_fd, buffer);
}

/**
 * @brief This function receives a string through a socket
 * @param socket_fd Socket file descriptor
 * @param buffer Buffer where the string will be stored
 * @param size_buffer Size of the buffer
 * @note First, the function receives the size of the string, in network byte order,
 * and then it receives the string itself.
 */
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

/**
 * @brief This function receives an integer through a socket
 * @param socket_fd Socket file descriptor
 * @param value Integer to be received
 * @note First, the function receives the string through the socket, and then
 * it converts the string to an integer.
 */
void secure_recv_int(int socket_fd, int *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);

	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atoi(buffer);
}

/**
 * @brief This function receives an long through a socket
 * @param socket_fd Socket file descriptor
 * @param value Long to be received
 * @note First, the function receives the string through the socket, and then
 * it converts the string to an long.
 */
void secure_recv_long(int socket_fd, long *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atol(buffer);
}

/**
 * @brief This function receives an float through a socket
 * @param socket_fd Socket file descriptor
 * @param value Float to be received
 * @note First, the function receives the string through the socket, and then
 * it converts the string to an float.
 */
void secure_recv_float(int socket_fd, float *value)
{
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	secure_recv_string(socket_fd, buffer, BUFFER_SIZE);
	*value = atof(buffer);
}