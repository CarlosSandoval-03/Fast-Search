/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdlib.h>
#include "structures.h"
#include "../file/file.h"

/**
 * @brief Creates a new node
 * @return node_t* a pointer to the newly created node
 */
node_t *new_node()
{
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (node == NULL) {
		perror("CREATE_NODE: NULL POINTER NODE\n");
		exit(EXIT_FAILURE);
	}

	return node;
}

/**
 * @brief Add a new node to the beginning of a linked list.
 * @param head Pointer to a pointer to the head of the linked list.
 * @param dstid The destination ID of the new node.
 * @param hod The hour of day of the new node.
 * @param mean_travel_time The mean travel time of the new node.
 * @return node_t* Pointer to the new node.
 */
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

/**
 * @brief Creates a new hash table.
 * @return A pointer to the newly created hash table.
 * @warning If the allocation fails, the function exits the program with an error message.
 */
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

/**
 * @brief Calculates the hash value for a given source ID.
 * @param srcid The source ID to hash.
 * @return The hash value.
 * @warning If the source ID is less than 1 or greater than the size of the hash table, the program will exit with EXIT_FAILURE.
 */
int hash(int srcid)
{
	if (srcid < 1 || srcid > HASH_SIZE) {
		printf("srcid: %d\n", srcid);
		perror("HASH: INVALID SRCID");
		exit(EXIT_FAILURE);
	}
	return srcid - 1;
}

/**
 * @brief Inserts a new node with the given parameters to the hash table.
 * @param ptr_hash Pointer to the hash table.
 * @param srcid The source id of the new node.
 * @param dstid The destination id of the new node.
 * @param hod The hour of the day of the new node.
 * @param mean_travel_time The mean travel time of the new node.
 * @return The index in the hash table where the new node was inserted.
 */
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

/**
 * @brief Creates a new index_t struct and returns a pointer to it.
 * @param srcid The source ID for the index.
 * @param start_pos The starting position for the index.
 * @return index_t* A pointer to the new index_t struct.
 */
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

/**
 * @brief Frees the memory allocated for the hash table and all its nodes.
 * @param ptr_hash A pointer to the hash table.
 */
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