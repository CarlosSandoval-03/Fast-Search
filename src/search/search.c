#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./search.h"
#include "../menu/menu.h"
#include "../file/file.h"
#include "../structures/structures.h"

int have_all_data(cache_t *cache)
{
	if (cache->srcid == 0 || cache->dstid == 0 || cache->hod == -1)
		return -1;
	return 1;
}

int search_actions(piped_t *pipe_descriptors, cache_t *cache)
{
	int selected_option = 0;
	read(pipe_descriptors->read, &selected_option, sizeof(int));

	if (selected_option == EXIT_OPTION)
		return EXIT_FAILURE;

	// If user not provided all the data, return -1 (NA)
	float mean_time = -1.0;
	if (selected_option == SEARCH_OPTION && have_all_data(cache) < 0) {
		write(pipe_descriptors->write, &mean_time, sizeof(float));
		return EXIT_SUCCESS;
	}

	// If user provided all the data, return mean time
	if (selected_option == SEARCH_OPTION) {
		mean_time = get_mean_time(cache);

		write(pipe_descriptors->write, &mean_time, sizeof(float));
		return EXIT_SUCCESS;
	}

	long num = 0;
	read(pipe_descriptors->read, &num, sizeof(long));

	switch (selected_option) {
	case SRCID_OPTION:
		cache->srcid = (unsigned short)num;
		break;
	case DSTID_OPTION:
		cache->dstid = (unsigned short)num;
		break;
	case HOD_OPTION:
		cache->hod = (char)num;
		break;
	}

	return EXIT_SUCCESS;
}