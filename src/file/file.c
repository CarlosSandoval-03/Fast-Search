#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./file.h"
#include "../structures/structures.h"
#include "../pre_process/pre_process.h"

FILE *open_file(char const *path_file, char const *mode)
{
	FILE *file = fopen(path_file, mode);
	if (file == NULL) {
		perror("FILE: ERROR OPEN THE FILE");
		exit(EXIT_FAILURE);
	}

	return file;
}

void remove_line(FILE *fp)
{
	char curr_char = '\0';
	while (curr_char != '\n') {
		curr_char = fgetc(fp);
	}
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

float get_mean_time(cache_t *cache)
{
	unsigned short srcid = cache->srcid;
	long start_pos = get_pos_by_srcid(srcid);
	long end_pos = get_pos_by_srcid(srcid + 1) - 1;

	if (start_pos == -1 || end_pos == -1) {
		return -1.0;
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