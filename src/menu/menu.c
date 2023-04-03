#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./menu.h"
#include "../structures/structures.h"

long get_num_from_input(long min, long max)
{
	long num = 0;

	do {
		scanf("%ld", &num);
		while (getc(stdin) != '\n') {
		} // Clear buffer if user registers a string

		if (num >= min && num <= max)
			return num;
	} while (1);
}

int search_actions(piped_t *pipe_descriptors, cache_t *cache)
{
	int selected_option = 0;
	read(pipe_descriptors->read, &selected_option, sizeof(int));

	if (selected_option == EXIT_OPTION)
		return -1;

	if (selected_option == SEARCH_OPTION) {
		float mean_time = -1;

		// If user not selected any option, return -1
		if (cache->srcid == 0 || cache->dstid == 0 || cache->hod == -1) {
			write(pipe_descriptors->write, &mean_time, sizeof(float));
		}

		// TODO: Proceso de búsqueda
		write(pipe_descriptors->write, &mean_time, sizeof(float));
		return EXIT_SUCCESS;
	}

	// If user not search or exit, then get number from input
	switch (selected_option) {
	case SRCID_OPTION:
		// Ingresar origen
		break;
	case DSTID_OPTION:
		// Ingresar destino
		break;
	case HOD_OPTION:
		// Ingresar hora
		break;
	}

	return EXIT_SUCCESS;
}

void menu_actions(int option, piped_t *pipe_descriptors)
{
	write(pipe_descriptors->write, &option, sizeof(int)); // Send option to search process

	long min = 0;
	long max = 0;
	const char *message = "";
	switch (option) {
	case SRCID_OPTION:
		// Ingresar origen
		message = "Ingrese ID del origen: ";
		min = 0;
		max = 1160;
		break;
	case DSTID_OPTION:
		// Ingresar destino
		message = "Ingrese ID del destino: ";
		min = 0;
		max = 1160;
		break;
	case HOD_OPTION:
		// Ingresar hora
		message = "Ingrese hora del dia: ";
		min = 0;
		max = 23;
		break;
	case SEARCH_OPTION:
		message = "Tiempo de viaje medio: ";
		break;
	case EXIT_OPTION:
	default:
		return;
	}

	// Send number to search process
	printf("%s", message);
	if (option != SEARCH_OPTION) {
		long num = get_num_from_input(min, max);
		write(pipe_descriptors->write, &num, sizeof(long));
		return;
	}

	// Get mean time from search process and print it
	float mean_time = 0;
	read(pipe_descriptors->read, &mean_time, sizeof(float));
	if (mean_time == -1)
		printf("NA\n");
	else
		printf("%f\n", mean_time);
}

void search_menu(piped_t *pipe_descriptors, cache_t *cache)
{
	int flag = 0;
	while (flag != -1) {
		flag = search_actions(pipe_descriptors, cache);
	}
}

void main_menu(piped_t *pipe_descriptors)
{
	printf("Bienvenido\n");

	int option = 0;
	do {
		printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n\nOpcion: ");
		option = get_num_from_input(SRCID_OPTION, EXIT_OPTION);

		menu_actions(option, pipe_descriptors);
	} while (option != EXIT_OPTION);
}