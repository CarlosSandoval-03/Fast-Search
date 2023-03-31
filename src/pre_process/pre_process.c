#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file/file.h"
#include "../structures/structures.h"
#include "./pre_process.h"

unsigned int write_list(node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_LIST, "ab");

	unsigned int written_nodes = 0;
	node_t *curr_node = head;
	while (curr_node != NULL) {
		fwrite(curr_node, sizeof(node_t), 1, fp);
		written_nodes++;
		curr_node = curr_node->next;
	}

	fclose(fp);
	return written_nodes;
}

unsigned long index_list(unsigned short srcid, node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_HASH, "ab");
	unsigned long start_pos = (unsigned long)ftell(fp);
	index_t *list_index = new_index(srcid, start_pos);

	fwrite(list_index, sizeof(index_t), 1, fp);
	write_list(head);

	return start_pos;
}

void remove_first_line(FILE *fp)
{
	char curr_char = '\0';
	while (curr_char != '\n') {
		curr_char = fgetc(fp);
	}
	fgetc(fp); // remove \n
}

int *clear_int_array(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}

	return array;
}

int *get_numbers(char *buffer, int num_params)
{
	int *values = (int *)malloc(sizeof(int) * num_params);
	clear_int_array(values, num_params);

	char *token = strtok(buffer, (const char *)DELIMITER_CSV_STRING);
	for (int i = 0; i < num_params; i++) {
		if (token == NULL)
			break;

		values[i] = atoi(token);
		token = strtok(NULL, (const char *)DELIMITER_CSV_STRING);
	}
	return values;
}

const char *get_line(FILE *fp, char *buffer, int size_buff)
{
	int i = 0;
	int k = 0;
	while (i < NUM_PARAMS_TO_TAKE || k < size_buff) {
		char curr_char = fgetc(fp);
		if (curr_char == DELIMITER_CSV_CHAR) {
			i++;
		}

		buffer[k] = curr_char;
	}

	buffer[size_buff] = '\0'; // String null terminated

	return buffer;
}

void process_data()
{
	FILE *fp = fopen(DEFAULT_PATH_DATA, "r");
	remove_first_line(fp);

	while (!feof(fp)) {
		// Read line
		char buffer[1024];
		get_line(fp, buffer, 1024);

		// Get numbers
	}
}