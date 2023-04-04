#include <stdlib.h>
#include "structures.h"
#include "../file/file.h"

node_t *new_node()
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (node == NULL) {
		perror("CREATE_NODE: NULL POINTER NODE\n");
		exit(EXIT_FAILURE);
	}

	return node;
}

node_t *push(node_t **head, unsigned short dstid, unsigned char hod, float mean_travel_time)
{
	if ((*head) == NULL) {
		*head = new_node();
		(*head)->dstid = dstid;
		(*head)->hod = hod;
		(*head)->mean_travel_time = mean_travel_time;
		(*head)->next = NULL;
		return *head;
	}

	node_t *n_node = new_node();
	n_node->dstid = dstid;
	n_node->hod = hod;
	n_node->mean_travel_time = mean_travel_time;
	n_node->next = NULL;
	n_node->next = *head;
	*head = n_node;

	return n_node;
}

hash_t *new_hash()
{
	hash_t *ptr_hash = (hash_t *)malloc(sizeof(hash_t));
	if (ptr_hash == NULL) {
		perror("CREATE_HASH: NULL POINTER");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < HASH_SIZE; i++) {
		ptr_hash->headers_list[i] = NULL;
	}

	return ptr_hash;
}

int hash(int srcid)
{
	if (srcid < 1 || srcid > HASH_SIZE) {
		printf("srcid: %d\n", srcid);
		perror("HASH: INVALID SRCID");
		exit(EXIT_FAILURE);
	}
	return srcid - 1;
}

int insert(hash_t *ptr_hash, int srcid, unsigned short dstid, unsigned char hod, float mean_travel_time)
{
	if (ptr_hash == NULL) {
		perror("INSERT: NULL POINTER HASH");
		exit(EXIT_FAILURE);
	}

	const int index = hash(srcid);
	push(&(ptr_hash->headers_list[index]), dstid, hod, mean_travel_time);
	return index;
}

index_t *new_index(unsigned short srcid, long start_pos)
{
	index_t *ptr_index = (index_t *)malloc(sizeof(index_t));
	if (ptr_index == NULL) {
		perror("CREATE_INDEX: NULL POINTER");
		exit(EXIT_FAILURE);
	}

	ptr_index->srcid = srcid;
	ptr_index->start_pos = start_pos;
	return ptr_index;
}

void free_hash(hash_t *ptr_hash)
{
	for (int i = 0; i < HASH_SIZE; i++) {
		node_t *head = ptr_hash->headers_list[i];
		node_t *curr_node = head;
		while (curr_node != NULL) {
			node_t *tmp = curr_node;
			curr_node = curr_node->next;
			free(tmp);
		}
	}

	free(ptr_hash);
}