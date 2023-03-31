#pragma once
#ifndef _PRE_PROCESS_H_
#define _PRE_PROCESS_H_

#include "../structures/structures.h"

#define DEFAULT_PATH_DATA "data/raw/uber_data.csv"
#define DEFAULT_PATH_LIST "data/processed/list.bin"
#define DEFAULT_PATH_HASH "data/processed/hash.bin"

#define DELIMITER_CSV_STRING ","
#define DELIMITER_CSV_CHAR ','
#define NUM_PARAMS_TO_TAKE 4

unsigned int write_list(node_t *head);
unsigned long index_list(unsigned short srcid, node_t *head);

#endif // _PRE_PROCESS_H_