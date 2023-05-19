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
#include "./menu.h"
#include "../file/file.h"
#include "../protocol/protocol.h"
#include "../structures/structures.h"

/**
 * @brief Prompts the user to input a number within a specified range.
 * @param min The minimum allowed value.
 * @param max The maximum allowed value.
 * @return long The number input by the user that falls within the specified range.
 */
long get_num_from_input(long min, long max)
{
	long num = -1;

	do {
		int scan_status = scanf("%ld", &num);
		while (getc(stdin) != '\n')
			; // Clear buffer if user registers a string

		if (scan_status == EOF)
			continue; // If scanf fails, try again

		if (min <= num && num <= max)
			return num;

		printf("ERROR: Ingrese un numero entre %ld y %ld: ", min, max);
	} while (1);
}

/**
 * @brief Manage options.
 * @param option An integer representing the option chosen by the user in the menu.
 * @param socket_fd The socket file descriptor.
 * @return void
 * @note Sends an option to the search process through a pipe, and based on the option, prompts the user to input a number
 * or retrieves the mean travel time from the search process and prints it to the console.
 */
void menu_actions(int option, int socket_fd)
{
	secure_send_int(socket_fd, option); // Send option to server

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
		printf("[INFO] Desconectando...\n");
	default:
		return;
	}

	if (option == SEARCH_OPTION)
		printf("[INFO] Se ha enviado la opcion: %d al servidor, esperando resultados...\n", option);

	printf("%s", message);
	if (option != SEARCH_OPTION) {
		long num = get_num_from_input(min, max);
		secure_send_long(socket_fd, num);
		printf("[INFO] Se ha enviado la opcion: %d con el valor %ld al servidor\n", option, num);
		return;
	}

	// Get mean time from search process and print it
	float mean_time = 0;
	secure_recv_float(socket_fd, &mean_time);
	if (mean_time == -1.0)
		printf("NA\n");
	else
		printf("%.2f\n", mean_time);
}

/**
 * @brief Displays the main menu and executes the selected option.
 * @param socket_fd The socket file descriptor.
 * @return void
 * @note This function displays a menu with several options related to the transportation system.
 * It then prompts the user to choose an option by entering a number from 1 to 5.
 * Depending on the option selected, it may call the menu_actions() function to perform specific actions.
 * This function will continue to display the menu until the user selects option 5 to exit the program.
 */
void main_menu(int socket_fd)
{
	printf("\nBienvenido\n");

	int option = 0;
	do {
		printf("\n1. Ingresar origen\n2. Ingresar destino\n3. Ingresar hora\n4. Buscar tiempo de viaje medio\n5. Salir\n\nOpcion: ");
		option = get_num_from_input(SRCID_OPTION, EXIT_OPTION);

		menu_actions(option, socket_fd);
	} while (option != EXIT_OPTION);
}