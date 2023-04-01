#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../file/file.h"
#include "./pre_process.h"
#include "../structures/structures.h"

typedef struct {
	unsigned short srcid;
	unsigned short dstid;
	unsigned char hod;
	float mean_travel_time;
} raw_t;

raw_t *new_raw()
{
	raw_t *raw = (raw_t *)malloc(sizeof(raw_t));
	if (raw == NULL) {
		perror("NEW_RAW: NULL POINTER RAW");
		exit(EXIT_FAILURE);
	}

	return raw;
}

void clear_buffer(char *buffer, int size_buff)
{
	for (int i = 0; i < size_buff; i++) {
		buffer[i] = '\0';
	}
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
	buffer[size_buff - 1] = '\0'; // String null terminated

	// Skip to next line
	int curr_char = 0;
	while (curr_char != EOF && curr_char != '\n') {
		curr_char = fgetc(fp);
	}

	return buffer;
}

raw_t *parse_data(char *buffer)
{
	raw_t *raw = new_raw();
	int i = 0;
	char *token = strtok(buffer, DELIMITER_CSV_STRING);
	while (i < NUM_PARAMS_TO_TAKE && token != NULL) {
		switch (i) {
		case 0:
			raw->srcid = (unsigned short)atoi(token);
			break;
		case 1:
			raw->dstid = (unsigned short)atoi(token);
			break;
		case 2:
			raw->hod = (unsigned char)atoi(token);
			break;
		case 3:
			raw->mean_travel_time = (float)atof(token);
			break;
		default:
			break;
		}

		token = strtok(NULL, DELIMITER_CSV_STRING);
		i++;
	}

	return raw;
}

void process_line(char *buffer, hash_t *ptr_hash)
{
	if (buffer == NULL) {
		return;
	}
	raw_t *raw = parse_data(buffer);

	if (raw->srcid == 0 || raw->dstid == 0) {
		return;
	}

	insert(ptr_hash, raw->srcid, raw->dstid, raw->hod, raw->mean_travel_time);
}

int main()
{
	FILE *data_fp = open_file(DEFAULT_PATH_DATA, "r");
	FILE *list_fp = open_file(DEFAULT_PATH_LIST, "wb");
	FILE *hash_fp = open_file(DEFAULT_PATH_HASH, "wb");

	remove_line(data_fp);

	hash_t *hash_ptr = new_hash();
	char buffer[BUFFER_SIZE];

	printf("Processing data...\n");
	while (get_data(data_fp, buffer, BUFFER_SIZE) != NULL) {
		process_line(buffer, hash_ptr);
	}

	write_hash(hash_ptr, hash_fp, list_fp);
	printf("Done!\n");

	free_hash(hash_ptr);
	fclose(data_fp);
	fclose(list_fp);
	fclose(hash_fp);

	return EXIT_SUCCESS;
}