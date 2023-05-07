#ifndef _SOCKET_H_
#define _SOCKET_H_

int create_socket();
int socket_bind_server(int server_fd, unsigned int port);
int socket_connect_client(int client_fd, char *host, unsigned int port);

#endif // !_SOCKET_H_