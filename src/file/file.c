#include <stdio.h>
#include <stdlib.h>
#include "./file.h"

FILE *open_file(char const *path_file, char const *mode)
{
	FILE *file = fopen(path_file, mode);
	if (file == NULL) {
		perror("FILE: ERROR OPEN THE FILE");
		exit(EXIT_FAILURE);
	}

	return file;
}