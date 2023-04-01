#include <stdlib.h>
#include "structures.h"
#include "../pre_process/pre_process.h"
#include "../file/file.h"

node_t *new_node(unsigned short dstid, unsigned char hod, float mean_travel_time)
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (node == NULL) {
		perror("CREATE_NODE: NULL POINTER NODE\n");
		exit(EXIT_FAILURE);
	}

	node->dstid = dstid;
	node->hod = hod;
	node->mean_travel_time = mean_travel_time;
	return node;
}

void free_list(node_t *head)
{
	while (head != NULL) {
		node_t *next_node = head->next;
		free(next_node);

		head = head->next;
	}
}

node_t *push(node_t **head, node_t *node)
{
	if (head == NULL) {
		perror("PUSH: NULL POINTER HEAD");
		exit(EXIT_FAILURE);
	}

	if (node == NULL) {
		perror("PUSH: NULL POINTER NODE");
		exit(EXIT_FAILURE);
	}

	node->next = *head;
	*head = node;

	return node;
}

hash_t *new_hash()
{
	hash_t *ptr_hash = (hash_t *)malloc(sizeof(hash_t));
	if (ptr_hash == NULL) {
		perror("CREATE_HASH: NULL POINTER");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < TOTAL_DESTINY_ID; i++) {
		ptr_hash->headers_list[i] = NULL;
	}

	return ptr_hash;
}

int hash(int srcid)
{
	return srcid - 1;
}

int insert(hash_t *ptr_hash, int srcid, node_t *node)
{
	if (ptr_hash == NULL) {
		perror("INSERT: NULL POINTER HASH");
		exit(EXIT_FAILURE);
	}

	if (node == NULL) {
		perror("INSERT: NULL POINTER NODE");
		exit(EXIT_FAILURE);
	}

	const int index = hash(srcid);
	node_t *head_list = (node_t *)ptr_hash->headers_list[index];

	if (head_list == NULL) {
		ptr_hash->headers_list[index] = node;
		return index;
	}

	push(&head_list, node);
	return index;
}

index_t *new_index(unsigned short srcid, unsigned long start_pos)
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
