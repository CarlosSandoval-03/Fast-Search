#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./file/file.h"
#include "./pre_process/pre_process.h"

typedef struct {
	int write;
	int read;
} piped_t; // Pipe descriptor

void menu_actions(int option, piped_t *pipe_descriptors)
{
	write(pipe_descriptors->write, &option, sizeof(int)); // Send option to search process

	switch (option) {
	case 1:
		// Ingresar origen
		break;
	case 2:
		// Ingresar destino
		break;
	case 3:
		// Ingresar hora
		break;
	}
}

void main_menu(piped_t *pipe_descriptors)
{
	printf("Bienvenido\n");

	int option = 0;
	do {
		printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n\nOpcion: ");
		scanf("%d", &option);

		while (getc(stdin) != '\n')
			; // Clear buffer if user registers a string
		if (option < 1 || option > 5)
			continue;

		menu_actions(option, pipe_descriptors);
	} while (option != 5);
}

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
	int main_pipe_fd[2]; // main (write)
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
	int search_pipe_fd[2]; // search (write)
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
	} else {
		// Main process
		close(main_pipe_fd[0]); // Close read
		close(search_pipe_fd[1]); // Close write

		piped_t *pd_main = (piped_t *)malloc(sizeof(piped_t));
		pd_main->write = main_pipe_fd[1];
		pd_main->read = main_pipe_fd[0];
		main_menu(pd_main);

		free(pd_main);
	}

	return EXIT_SUCCESS;
}