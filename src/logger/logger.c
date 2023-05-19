/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "./logger.h"
#include "../file/file.h"

// Mutex of logs file
pthread_mutex_t mutex;

/**
 * @brief This function writes the current date to a logs file in specified format
 * @param file A pointer to the file to write the date to (must be opened in "a" mode)
 * @note This function uses the time() and localtime() functions to get the current date
 */
void write_date(FILE *file)
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	fprintf(file, DATE_LOG_FORMAT, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

/**
 * @brief This function writes the client IP to a logs file in specified format
 * @param file A pointer to the file to write the client IP to (must be opened in "a" mode)
 * @param client_ip A string of size INET_ADDRSTRLEN containing the client IP
 */
void write_client(FILE *file, const char *client_ip)
{
	fprintf(file, CLIENT_LOG_FORMAT, client_ip);
}

/**
 * @brief This function write the client action to a logs file in specified format
 * @param client_ip A string of size INET_ADDRSTRLEN containing the client IP
 * @note This function lock the mutex of logs file before write the action and unlock it after
 */
void log_client_connect(const char *client_ip)
{
	pthread_mutex_lock(&mutex);
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_CONNECT_FORMAT);

	fclose(file);
	pthread_mutex_unlock(&mutex);
}

/**
 * @brief This function write the client disconnection to a logs file in specified format
 * @param client_ip A string of size INET_ADDRSTRLEN containing the client IP
 * @note This function lock the mutex of logs file before write the disconnection and unlock it after
 */
void log_client_disconnect(const char *client_ip)
{
	pthread_mutex_lock(&mutex);
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_DISCONNECT_FORMAT);

	fclose(file);
	pthread_mutex_unlock(&mutex);
}

/**
 * @brief This function write the client send data to a logs file in specified format
 * @param client_ip A string of size INET_ADDRSTRLEN containing the client IP
 * @param type_data A string containing the option selected by the client
 * @param data The data sent by the client
 * @note This function lock the mutex of logs file before write the data and unlock it after
 */
void log_client_send_data(const char *client_ip, const char *type_data, unsigned short data)
{
	pthread_mutex_lock(&mutex);
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_SEND_ACTION_FORMAT, type_data, data);

	fclose(file);
	pthread_mutex_unlock(&mutex);
}

/**
 * @brief This function write the client request data to a logs file in specified format
 * @param client_ip A string of size INET_ADDRSTRLEN containing the client IP
 * @param data The data sent by the server
 */
void log_client_request_data(const char *client_ip, float data)
{
	pthread_mutex_lock(&mutex);
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);

	if (data < 0.0)
		fprintf(file, CLIENT_REQUEST_ERROR_FORMAT);
	else
		fprintf(file, CLIENT_REQUEST_ACTION_FORMAT, data);

	fclose(file);
	pthread_mutex_unlock(&mutex);
}