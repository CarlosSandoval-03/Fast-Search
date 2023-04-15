/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _PRE_PROCESS_H_
#define _PRE_PROCESS_H_

#include "../structures/structures.h"

// Default file location
#define DEFAULT_PATH_DATA "data/raw/uber_data.csv"
#define DEFAULT_PATH_LIST "data/processed/list.bin"
#define DEFAULT_PATH_HASH "data/processed/hash.bin"

// Default CSV Features
#define DELIMITER_CSV_STRING ","
#define DELIMITER_CSV_CHAR ','
#define NUM_PARAMS_TO_TAKE 4
#define NUM_PARAMS_INT 3

#define BUFFER_SIZE 1024

void clear_buffer(char *buffer, int size_buff);
const char *get_data(FILE *fp, char *buffer, int size_buff);
void process_line(char *buffer, hash_t *ptr_hash);

float get_mean_time(cache_t *cache);

#endif // _PRE_PROCESS_H_