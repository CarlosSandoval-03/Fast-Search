#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file/file.h"
#include "../structures/structures.h"
#include "./pre_process.h"

long write_list(node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_LIST, "ab");
	long start_pos = ftell(fp);

	node_t *curr_node = head;
	while (curr_node != NULL) {
		fwrite(curr_node, sizeof(node_t), 1, fp);
		curr_node = curr_node->next;
	}

	fclose(fp);
	return start_pos;
}

long write_index(index_t *ptr_index)
{
	FILE *fp = open_file(DEFAULT_PATH_HASH, "ab");
	long start_pos = ftell(fp);

	fwrite(ptr_index, sizeof(index_t), 1, fp);
	fclose(fp);
	return start_pos;
}

void write_hash(hash_t *ptr_hash)
{
	for (int i = 0; i < TOTAL_DESTINY_ID; i++) {
		node_t *head = ptr_hash->headers_list[i];
		long start_pos = (unsigned long)write_list(head);

		index_t *ptr_index = new_index(i, start_pos);
		write_index(ptr_index);

		printf("Index: %d, Start: %lu\n", i, ptr_index->start_pos);
	}
}

void clear_buffer(char *buffer, int size_buff)
{
	for (int i = 0; i < size_buff; i++) {
		buffer[i] = '\0';
	}
}

void process_line(char *buffer, hash_t *ptr_hash)
{
	unsigned short srcid = 0;
	unsigned short dstid = 0;
	unsigned char hod = 0;
	float mean_travel_time = 0.0;

	int i = 0;
	char *token = strtok(buffer, DELIMITER_CSV_STRING);
	while (i < NUM_PARAMS_TO_TAKE && token != NULL) {
		switch (i) {
		case 0:
			srcid = (unsigned short)atoi(token);
			printf("SRCID: %d\n", srcid);
			break;
		case 1:
			dstid = (unsigned short)atoi(token);
			printf("DSTID: %d\n", dstid);
			break;
		case 2:
			hod = (unsigned char)atoi(token);
			printf("HOD: %d\n", hod);
			break;
		case 3:
			mean_travel_time = (float)atof(token);
			printf("MEAN_TRAVEL_TIME: %f\n", mean_travel_time);
			break;
		default:
			break;
		}

		token = strtok(NULL, DELIMITER_CSV_STRING);
		i++;
	}

	node_t *line_node = new_node(dstid, hod, mean_travel_time);
	if (line_node == NULL) {
		perror("PROCESS_LINE: NULL POINTER NODE");
		exit(EXIT_FAILURE);
	}

	insert(ptr_hash, srcid, line_node);
}

const char *get_data(FILE *fp, char *buffer, int size_buff)
{
	if (feof(fp)) {
		return NULL;
	}

	int i = 0;
	int k = 0;
	clear_buffer(buffer, size_buff);
	while (i < NUM_PARAMS_TO_TAKE && k < size_buff) {
		char curr_char = fgetc(fp);
		if (curr_char == DELIMITER_CSV_CHAR) {
			i++;
		}

		buffer[k] = curr_char;
		k++;
	}

	buffer[size_buff] = '\0'; // String null terminated
	return buffer;
}

void process_data()
{
	FILE *fp = open_file(DEFAULT_PATH_DATA, "r");
	remove_line(fp);

	// Hash table
	hash_t *ptr_hash = new_hash();

	char buffer[BUFFER_SIZE];
	while (get_data(fp, buffer, BUFFER_SIZE) != NULL) {
		clear_buffer(buffer, BUFFER_SIZE);
		process_line(buffer, ptr_hash);
	}

	write_hash(ptr_hash);
}