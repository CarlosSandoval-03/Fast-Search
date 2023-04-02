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

long write_list(node_t *head, FILE *fp)
{
	long start_pos = ftell(fp);
	node_t *curr_node = head;

	while (curr_node != NULL) {
		fwrite(curr_node, sizeof(node_t), 1, fp);
		curr_node = curr_node->next;
	}

	return start_pos;
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

void write_hash(hash_t *ptr_hash, FILE *hash_fp, FILE *list_fp)
{
	for (int i = 0; i < HASH_SIZE; i++) {
		// Write list in file
		long start_pos = ftell(list_fp);
		node_t *head = ptr_hash->headers_list[i];
		if (head != NULL) {
			write_list(head, list_fp);
		}

		// Save srcid and start_pos in file
		const unsigned short srcid = i + 1;
		index_t *index = new_index(srcid, start_pos);
		fwrite(index, sizeof(index_t), 1, hash_fp);
		free(index);
	}
}

long get_pos_by_srcid(FILE *hash_fp, unsigned short srcid)
{
	if (hash_fp == NULL) {
		perror("READ_HASH: NULL POINTER FILE HASH");
		exit(EXIT_FAILURE);
	}

	while (!feof(hash_fp)) {
		index_t *index = (index_t *)malloc(sizeof(index_t));
		if (index == NULL) {
			perror("READ_HASH: NULL POINTER INDEX");
			exit(EXIT_FAILURE);
		}

		fread(index, sizeof(index_t), 1, hash_fp);
		if (index->srcid == srcid) {
			unsigned short start_pos = index->start_pos;
			return start_pos;
		}

		free(index);
	}

	return -1;
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