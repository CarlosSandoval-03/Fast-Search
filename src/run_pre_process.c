#include <stdio.h>
#include <stdlib.h>
#include "./file/file.h"
#include "./pre_process/pre_process.h"
#include "./structures/structures.h"

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