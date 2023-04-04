#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "./menu.h"
#include "../file/file.h"
#include "../structures/structures.h"

long get_num_from_input(long min, long max)
{
	long num = 0;

	do {
		scanf("%ld", &num);
		while (getc(stdin) != '\n') {
		} // Clear buffer if user registers a string

		if (min <= num && num <= max)
			return num;

		printf("ERROR: Ingrese un numero entre %ld y %ld: ", min, max);
	} while (1);
}

void menu_actions(int option, piped_t *pipe_descriptors)
{
	write(pipe_descriptors->write, &option, sizeof(int)); // Send option to search process

	long min = 0;
	long max = 0;
	const char *message = "";
	switch (option) {
	case SRCID_OPTION:
		message = "Ingrese ID del origen: ";
		min = 1;
		max = 1160;
		break;
	case DSTID_OPTION:
		message = "Ingrese ID del destino: ";
		min = 1;
		max = 1160;
		break;
	case HOD_OPTION:
		message = "Ingrese hora del dia: ";
		min = 0;
		max = 23;
		break;
	case SEARCH_OPTION:
		message = "\nTiempo de viaje medio: ";
		break;
	case EXIT_OPTION:
	default:
		return;
	}

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
		printf("%.2f\n", mean_time);
}

void main_menu(piped_t *pipe_descriptors)
{
	printf("\nBienvenido\n");

	int option = 0;
	do {
		printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n\nOpcion: ");
		option = get_num_from_input(SRCID_OPTION, EXIT_OPTION);

		menu_actions(option, pipe_descriptors);
	} while (option != EXIT_OPTION);
}