#ifndef _PRE_PROCESS_H_
#define _PRE_PROCESS_H_

#include "../structures/structures.h"

#define DEFAULT_PATH_DATA "data/raw/uber_data.csv"
#define DEFAULT_PATH_LIST "data/processed/list.bin"
#define DEFAULT_PATH_HASH "data/processed/hash.bin"

#define DELIMITER_CSV_STRING ","
#define DELIMITER_CSV_CHAR ','
#define NUM_PARAMS_TO_TAKE 4
#define NUM_PARAMS_INT 3

#define BUFFER_SIZE 1024

void clear_buffer(char *buffer, int size_buff);

#endif // _PRE_PROCESS_H_