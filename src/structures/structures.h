#pragma once
#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <stdio.h>

#define TOTAL_DESTINY_ID 1159

typedef struct Node {
	unsigned short dstid;
	unsigned char hod;
	float mean_travel_time;
	struct Node *next;
} node_t;

typedef struct {
	node_t *headers_list[TOTAL_DESTINY_ID];
} hash_t;

typedef struct {
	unsigned short srcid;
	unsigned long start_pos;
} index_t;

node_t *new_node(unsigned short dstid, unsigned char hod, float mean_travel_time);
void free_list(node_t *head);
node_t *push(node_t **head, node_t *node);

hash_t *new_hash();
int hash(int srcid);
int insert(hash_t *ptr_hash, int srcid, node_t *node);

index_t *new_index(unsigned short srcid, unsigned long start_pos);

#endif // _STRUCTURES_H_
