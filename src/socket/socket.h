/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _SOCKET_H_
#define _SOCKET_H_

int create_socket();
int socket_bind_server(int server_fd, unsigned int port);
int socket_connect_client(int client_fd, char *host, unsigned int port);

#endif // !_SOCKET_H_