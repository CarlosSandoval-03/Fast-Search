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
#include "../file/file.h"
#include "./pre_process.h"
#include "../structures/structures.h"

// Raw info
typedef struct {
	unsigned short srcid;
	unsigned short dstid;
	unsigned char hod;
	float mean_travel_time;
} raw_t;

/**
 * @brief Creates a new instance of raw_t struct.
 * @return raw_t* A pointer to the newly allocated memory for raw_t struct.
 * @note This function allocates memory for a new instance of the raw_t struct using the malloc function.
 * The function then returns a pointer to the newly allocated memory for raw_t struct.
 * @warning If the allocation fails, the function exits the program with an error message.
 */
raw_t *new_raw()
{
	raw_t *raw = (raw_t *)malloc(sizeof(raw_t));
	if (raw == NULL) {
		perror("NEW_RAW: NULL POINTER RAW");
		exit(EXIT_FAILURE);
	}

	return raw;
}

/**
 * @brief Clears the contents of a char buffer
 * @param buffer The buffer to clear
 * @param size_buff The size of the buffer
 */
void clear_buffer(char *buffer, int size_buff)
{
	for (int i = 0; i < size_buff; i++) {
		buffer[i] = '\0';
	}
}

/**
 * @brief Reads data from a CSV file, storing it in a buffer.
 * @param fp The file pointer to the CSV file to read from
 * @param buffer The buffer where the data will be stored
 * @param size_buff The size of the buffer
 * @return A pointer to the buffer containing the data, or NULL if the end of file has been reached.
 */
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

/**
 * @brief Parse data from a buffer in CSV format and return a new raw_t struct.
 * @param buffer A pointer to the buffer containing the CSV-formatted data.
 * @return A pointer to a new raw_t struct containing the parsed data.
 */
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

/**
 * @brief Process a line of CSV-formatted data by parsing it into a raw_t struct and inserting it into the given hash table.
 * @param buffer A pointer to the buffer containing the CSV-formatted data to be processed.
 * @param ptr_hash A pointer to the hash table where the parsed data will be inserted.
 * @return void
 */
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
