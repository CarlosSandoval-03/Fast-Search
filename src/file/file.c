/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./file.h"
#include "../structures/structures.h"
#include "../pre_process/pre_process.h"

/**
 * @brief This function opens a file in a specified mode
 * @param path_file The path of the file to open
 * @param mode The mode in which to open the file (e.g. "r", "w", "a", etc.)
 * @return Returns a pointer to the opened file
 * @note If the file cannot be opened, the function will print an error message
 * using perror() and exit the program with failure status
 */
FILE *open_file(char const *path_file, char const *mode)
{
	FILE *file = fopen(path_file, mode);
	if (file == NULL) {
		perror("FILE: ERROR OPEN THE FILE");
		exit(EXIT_FAILURE);
	}

	return file;
}

/**
 * @brief This function removes a line from a file
 * @param fp A pointer to the file to remove a line from
 * @note This function reads the file character by character until it reaches
 * the end of the current line (indicated by a newline character)
 */
void remove_line(FILE *fp)
{
	char curr_char = '\0';
	while (curr_char != '\n') {
		curr_char = fgetc(fp);
	}
}

/**
 * @brief This function writes a linked list to a file
 * @param head A pointer to the head node of the linked list to write
 * @param fp A pointer to the file to write the linked list to
 * @return Returns the starting position in the file where the linked list was written
 * @note This function writes each node of the linked list to the file using fwrite().
 * The size of each node is determined by sizeof(node_t).
 */
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

/**
 * @brief This function writes the hash table to file
 * @param ptr_hash A pointer to the hash table to write to file
 * @param hash_fp A pointer to the file to write the hash table index
 * @param list_fp A pointer to the file to write the linked lists
 * @note This function iterates over each header in the hash table and writes the
 * corresponding linked list to the list file. It then creates a new index with the
 * source ID and starting position of the linked list in the list file, and writes
 * this index to the hash file using fwrite().
 */
void write_hash(hash_t *ptr_hash, FILE *hash_fp, FILE *list_fp)
{
	for (int i = 0; i < HASH_SIZE; i++) {
		// Write list in file
		node_t *head = ptr_hash->headers_list[i];
		if (head == NULL) {
			continue;
		}

		// Save srcid and start_pos in file
		long start_pos = write_list(head, list_fp);
		const unsigned short srcid = i + 1;
		index_t *index = new_index(srcid, start_pos);
		fwrite(index, sizeof(index_t), 1, hash_fp);
		free(index);
	}
}

/**
 * @brief This function retrieves the starting position of a linked list in the list file
 * given a source ID from the hash file
 * @param srcid The source ID to search for in the hash file
 * @return Returns the starting position of the linked list in the list file if found, or -1 if not found
 * @note This function opens the hash file for reading and searches for an index with the
 * provided source ID. If found, it returns the starting position of the corresponding
 * linked list in the list file. If not found, it returns -1.
 */
long get_pos_by_srcid(unsigned short srcid)
{
	FILE *hash_fp = open_file(DEFAULT_PATH_HASH, "rb");

	if (hash_fp == NULL) {
		perror("READ_HASH: NULL POINTER FILE HASH");
		exit(EXIT_FAILURE);
	}

	index_t *index = (index_t *)malloc(sizeof(index_t));
	if (index == NULL) {
		perror("READ_HASH: NULL POINTER INDEX");
		exit(EXIT_FAILURE);
	}

	// Search in list file
	while (!feof(hash_fp)) {
		fread(index, sizeof(index_t), 1, hash_fp);

		if (index->srcid == srcid) {
			long start_pos = index->start_pos;

			free(index);
			fclose(hash_fp);

			return start_pos;
		}
	}

	free(index);
	fclose(hash_fp);
	return -1;
}

/**
 * @brief This function calculates the mean travel time for a specific cache
 * @param cache A pointer to the cache to calculate the mean travel time for
 * @return Returns the mean travel time for the specified cache, or -1.0 if the cache cannot be found
 * @note This function retrieves the starting and ending positions of the linked list for the
 * specified cache using the get_pos_by_srcid() function. It then searches the linked list
 * in the list file for the cache, and if found, returns the mean travel time for the cache.
 * If the cache cannot be found, the function returns -1.0.
 */
float get_mean_time(cache_t *cache)
{
	unsigned short srcid = cache->srcid;
	unsigned short next_srcid = srcid + 1;
	long start_pos = get_pos_by_srcid(srcid);
	long end_pos = get_pos_by_srcid(next_srcid) - 1;

	if (start_pos == -1) {
		return -1.0;
	}

	if (end_pos < 0) {
		while (end_pos < 0) {
			next_srcid++;
			end_pos = get_pos_by_srcid(next_srcid) - 1;

			if (next_srcid == HASH_SIZE)
				return -1.0;
		}
	}

	// Set cursor on first element of the list
	FILE *list_fp = open_file(DEFAULT_PATH_LIST, "rb");
	fseek(list_fp, start_pos, SEEK_SET);

	// Search
	unsigned short required_hod = cache->hod;
	unsigned short required_dstid = cache->dstid;

	node_t *node = new_node();
	float mean_time = -1.0;
	while (start_pos <= end_pos) {
		fread(node, sizeof(node_t), 1, list_fp);
		start_pos += sizeof(node_t);

		unsigned short dstid = node->dstid;
		unsigned short hod = node->hod;

		if (dstid != required_dstid)
			continue;
		if (hod != required_hod)
			continue;

		// Found
		mean_time = node->mean_travel_time;

		free(node);
		return mean_time;
	}

	free(node);
	fclose(list_fp);
	return mean_time;
}