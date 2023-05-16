#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

/**
 * The protocol uses hexadecimal numbers to identify the type of message.
 * The size of messages is: int type
 */

#define SERVER_CONN_CONFIRMATION 0x01
#define SERVER_CONN_REJECTION 0x02
#define SERVER_SEND_MESSAGE 0x03
#define SERVER_RECV_MESSAGE 0x04

#define CLIENT_CONN_CONFIRMATION 0x11
#define CLIENT_DISCONNECTION 0x12
#define CLIENT_SEND_MESSAGE 0x13
#define CLIENT_RECV_MESSAGE 0x14

#define FAKE_SIGNAL 0

#define BUFFER_SIZE 1024

#include <stdlib.h>

void secure_send(int socket_fd, const char *string);
void secure_send_int(int socket_fd, int value);
void secure_send_long(int socket_fd, long value);
void secure_send_float(int socket_fd, float value);
void secure_recv_int(int socket_fd, int *value);
void secure_recv_long(int socket_fd, long *value);
void secure_recv_float(int socket_fd, float *value);

#endif // !_PROTOCOL_H_