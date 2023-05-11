/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./search.h"
#include "../menu/menu.h"
#include "../file/file.h"
#include "../logger/logger.h"
#include "../protocol/protocol.h"
#include "../structures/structures.h"

/**
 * @brief Check if all the necessary data is in the cache.
 * @param cache The cache to check.
 * @return int Returns 1 if all the necessary data is in the cache, -1 otherwise.
 */
int have_all_data(cache_t *cache)
{
	if (cache->srcid == 0 || cache->dstid == 0 || cache->hod == -1)
		return -1;
	return 1;
}

/**
 * @brief Search actions based on selected option and cache data
 * @param socket_fd The socket file descriptor
 * @param cache Struct containing the cache data
 * @return int Returns EXIT_SUCCESS or EXIT_FAILURE depending on the selected option
 */
int search_actions(client_conn_t *client_conn, cache_t *cache)
{
	int socket_fd = client_conn->client_fd;

	int selected_option = 0;
	secure_recv_int(socket_fd, &selected_option);

	if (selected_option == EXIT_OPTION || selected_option == 0)
		return EXIT_FAILURE;

	// If user not provided all the data, return -1 (NA)
	float mean_time = -1.0;
	if (selected_option == SEARCH_OPTION && have_all_data(cache) < 0) {
		secure_send_float(socket_fd, mean_time);
		log_client_request_data(client_conn->client_ip, mean_time);
		return EXIT_SUCCESS;
	}

	// If user provided all the data, return mean time
	if (selected_option == SEARCH_OPTION) {
		mean_time = get_mean_time(cache);

		secure_send_float(socket_fd, mean_time);
		log_client_request_data(client_conn->client_ip, mean_time);
		return EXIT_SUCCESS;
	}

	const char *type_data = NULL;
	long num = 0;
	secure_recv_long(socket_fd, &num);

	switch (selected_option) {
	case SRCID_OPTION:
		cache->srcid = (unsigned short)num;
		type_data = "srcid";
		break;
	case DSTID_OPTION:
		cache->dstid = (unsigned short)num;
		type_data = "dstid";
		break;
	case HOD_OPTION:
		cache->hod = (char)num;
		type_data = "hod";
		break;
	}

	log_client_send_data(client_conn->client_ip, type_data, num);
	return EXIT_SUCCESS;
}