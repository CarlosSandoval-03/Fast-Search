#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "./file/file.h"
#include "./menu/menu.h"
#include "./pre_process/pre_process.h"

int main()
{
	/**
	 * Main pipe operation:
	 * 	 Read												Write
	 * |--------|									|--------|
	 * | search | <-------------- |  Main  |
	 * |--------|									|--------|
	 *
	 */
	int main_pipe_fd[2];
	int main_pipe = pipe(main_pipe_fd);
	if (main_pipe == -1) {
		perror("MAIN: PIPE ERROR");
		exit(EXIT_FAILURE);
	}

	/**
	 * Search pipe operation:
	 * 	 Read												Write
	 * |--------|									|--------|
	 * |  Main  | <-------------- | Search |
	 * |--------|									|--------|
	 */
	int search_pipe_fd[2];
	int search_pipe = pipe(search_pipe_fd);
	if (search_pipe == -1) {
		perror("MAIN: PIPE ERROR");
		exit(EXIT_FAILURE);
	}

	// Fork
	pid_t cpid;
	cpid = fork();
	if (cpid == -1) {
		perror("MAIN: FORK ERROR");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {
		// Search process
		close(main_pipe_fd[1]); // Close write
		close(search_pipe_fd[0]); // Close read

		piped_t *pd_search = (piped_t *)malloc(sizeof(piped_t));
		pd_search->read = main_pipe_fd[0];
		pd_search->write = search_pipe_fd[1];

		cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
		cache->srcid = 0;
		cache->dstid = 0;
		cache->hod = -1;

		search_menu(pd_search, cache);

		free(cache);
		free(pd_search);

		exit(EXIT_SUCCESS);
	} else {
		// Main process
		close(main_pipe_fd[0]); // Close read
		close(search_pipe_fd[1]); // Close write

		piped_t *pd_main = (piped_t *)malloc(sizeof(piped_t));
		pd_main->write = main_pipe_fd[1];
		pd_main->read = main_pipe_fd[0];
		main_menu(pd_main);

		free(pd_main);

		wait(NULL);
	}

	return EXIT_SUCCESS;
}