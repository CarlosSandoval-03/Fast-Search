#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_FILE_PATH "./data/logs/logs.txt"

#define DATE_LOG_FORMAT "[%d-%02d-%02dT%02d:%02d:%02d] "
#define CLIENT_LOG_FORMAT "[%s] "
#define CLIENT_CONNECT_FORMAT "[CONNECTED]\n"
#define CLIENT_DISCONNECT_FORMAT "[DISCONNECTED]\n"
#define CLIENT_SEND_ACTION_FORMAT "%s: [%u]\n"
#define CLIENT_REQUEST_ACTION_FORMAT "SEND_MEAN_TIME: [%.2f]\n"
#define CLIENT_REQUEST_ERROR_FORMAT "SEND_MEAN_TIME: [NA]\n"

#include <stdio.h>

void log_client_connect(const char *client_ip);
void log_client_disconnect(const char *client_ip);
void log_client_send_data(const char *client_ip, const char *type_data, unsigned short data);
void log_client_request_data(const char *client_ip, float data);

#endif // !_LOGGER_H_