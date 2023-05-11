/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <stdio.h>
#include <arpa/inet.h>

#define HASH_SIZE 1160

typedef struct Node {
	unsigned short dstid;
	unsigned char hod;
	float mean_travel_time;
	struct Node *next;
} node_t;

typedef struct {
	node_t *headers_list[HASH_SIZE];
} hash_t;

typedef struct {
	unsigned short srcid;
	long start_pos;
} index_t;

typedef struct {
	unsigned short srcid;
	unsigned short dstid;
	char hod;
} cache_t;

typedef struct {
	int client_fd;
	char client_ip[INET_ADDRSTRLEN];
} client_conn_t;

typedef struct {
	int enqueue;
	int dequeue;
} queue_conn_t;

node_t *new_node();
node_t *push(node_t **head, unsigned short dstid, unsigned char hod, float mean_travel_time);

hash_t *new_hash();
index_t *new_index(unsigned short srcid, long start_pos);
int insert(hash_t *ptr_hash, int srcid, unsigned short dstid, unsigned char hod, float mean_travel_time);
void free_hash(hash_t *ptr_hash);

#endif // _STRUCTURES_H_
