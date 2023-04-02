#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

#include <stdio.h>

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
	unsigned long start_pos;
} index_t;

node_t *new_node();
node_t *push(node_t **head, unsigned short dstid, unsigned char hod, float mean_travel_time);

hash_t *new_hash();
index_t *new_index(unsigned short srcid, unsigned long start_pos);
int insert(hash_t *ptr_hash, int srcid, unsigned short dstid, unsigned char hod, float mean_travel_time);
void write_hash(hash_t *ptr_hash, FILE *hash_fp, FILE *list_fp);
long get_pos_by_srcid(FILE *hash_fp, unsigned short srcid);
void free_hash(hash_t *ptr_hash);

#endif // _STRUCTURES_H_
