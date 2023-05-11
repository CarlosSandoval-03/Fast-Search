#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./logger.h"
#include "../file/file.h"

void write_date(FILE *file)
{
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	fprintf(file, DATE_LOG_FORMAT, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

void write_client(FILE *file, const char *client_ip)
{
	fprintf(file, CLIENT_LOG_FORMAT, client_ip);
}

void log_client_connect(const char *client_ip)
{
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_CONNECT_FORMAT);

	fclose(file);
}

void log_client_disconnect(const char *client_ip)
{
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_DISCONNECT_FORMAT);

	fclose(file);
}

void log_client_send_data(const char *client_ip, const char *type_data, unsigned short data)
{
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);
	fprintf(file, CLIENT_SEND_ACTION_FORMAT, type_data, data);

	fclose(file);
}

void log_client_request_data(const char *client_ip, float data)
{
	FILE *file = open_file(LOG_FILE_PATH, "a");

	write_date(file);
	write_client(file, client_ip);

	if (data < 0.0)
		fprintf(file, CLIENT_REQUEST_ERROR_FORMAT);
	else
		fprintf(file, CLIENT_REQUEST_ACTION_FORMAT, data);

	fclose(file);
}