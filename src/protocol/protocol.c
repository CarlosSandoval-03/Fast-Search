#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "./protocol.h"

void secure_send_int(int socket_fd, int value)
{
	int32_t net_num = htonl(value);
	char *buffer = (char *)&net_num;
	ssize_t bytes_sent = send(socket_fd, buffer, sizeof(net_num), 0);
	if (bytes_sent < 0) {
		perror("SEND: ERROR WHEN SENDING DATA\n");
	}
}

void secure_recv_int(int socket_fd, int *value)
{
	int32_t net_num;
	char *buffer = (char *)&net_num;
	int recv_status = recv(socket_fd, buffer, sizeof(net_num), 0);
	if (recv_status < 0) {
		perror("RECV: ERROR WHEN RECEIVING DATA\n");
	}

	*value = ntohl(net_num);
}
