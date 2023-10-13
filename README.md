# Fast Search - Operating Systems

- [Fast Search - Operating Systems](#fast-search---operating-systems)
  - [Description](#description)
  - [Project Setup](#project-setup)
    - [Run Server](#run-server)
    - [Run Client](#run-client)
  - [Example Of How The Program Works](#example-of-how-the-program-works)
  - [User Documentation](#user-documentation)
  - [Dev Documentation](#dev-documentation)
    - [Client](#client)
      - [Client Macros](#client-macros)
      - [Client Header Guard](#client-header-guard)
    - [File](#file)
      - [File Dependencies](#file-dependencies)
      - [File Functions](#file-functions)
    - [Logger](#logger)
      - [Logger Dependencies](#logger-dependencies)
      - [Logger Macros](#logger-macros)
      - [Logger Global Variables](#logger-global-variables)
      - [Logger Functions](#logger-functions)
    - [Menu](#menu)
      - [Menu Dependencies](#menu-dependencies)
      - [Menu Macros](#menu-macros)
      - [Menu Functions](#menu-functions)
    - [Pre Process](#pre-process)
      - [Preprocessor Dependencies](#preprocessor-dependencies)
      - [Preprocessor Macros](#preprocessor-macros)
      - [Preprocessor Structure](#preprocessor-structure)
      - [Preprocessor Functions](#preprocessor-functions)
    - [Protocol](#protocol)
      - [Protocol Dependencies](#protocol-dependencies)
      - [Protocol Macros](#protocol-macros)
      - [Protocol Functions](#protocol-functions)
    - [Search](#search)
      - [Search Dependencies](#search-dependencies)
      - [Search Functions](#search-functions)
    - [Server](#server)
      - [Server Dependencies](#server-dependencies)
      - [Server Macros](#server-macros)
      - [Server Global Variables](#server-global-variables)
      - [Server Functions](#server-functions)
    - [Socket](#socket)
      - [Socket Dependencies](#socket-dependencies)
      - [Socket Functions](#socket-functions)
    - [Structures](#structures)
      - [Structures Dependencies](#structures-dependencies)
      - [Structures Macros](#structures-macros)
      - [Structures Structures](#structures-structures)
      - [Structures Functions](#structures-functions)
    - [Run Pre Process](#run-pre-process)
      - [Run Pre Process Dependencies](#run-pre-process-dependencies)
      - [Run Pre Process Flow](#run-pre-process-flow)
    - [Run Server](#run-server-1)
      - [Run Server Dependencies](#run-server-dependencies)
      - [Run Server Flow](#run-server-flow)
    - [Run Client](#run-client-1)
      - [Run Client Dependencies](#run-client-dependencies)
      - [Run Client Flow](#run-client-flow)

Author: csandovalc

## Description

The project involves the development of a rapid search system using the C programming language in POSIX operating systems. This system enables users to efficiently search through a text file containing multiple records.

To optimize search speed, the system employs indexed files, which store pertinent information from the text file.

To establish a client-server architecture, two main programs are created to facilitate communication via text strings transmitted through sockets.

The server is responsible for searching and reading the indexed files, while the client initiates the required requests.

The primary objective of this project is to deepen our understanding of the operating system and apply the diverse utilities offered by POSIX.

## Project Setup

First, make a copy of the repository in its latest version main. Once cloned, navigate to the project folder using the following command:

```shell
# Using ssh
git clone git@github.com:CarlosSandoval-03/Fast-Search.git && cd Fast-Search

#Using https
git clone https://github.com/CarlosSandoval-03/Fast-Search.git && cd Fast-Search
```

### Run Server

To run the server, you need to download the [docker image of the project](https://hub.docker.com/r/carlossandoval03/fast-search) using the following command:

```shell
docker pull carlossandoval03/fast-search:latest
```

To start the server in a Docker instance using docker-compose, make sure to adjust the downloaded image with the one specified in the `docker-compose.yaml` file if necessary:

```shell
docker-compose up -d
```

Once the process is completed, the server will be running on port `8080`.

### Run Client

To run the client, you need to build the project first. This can be done using the following command:

```shell
make build
```

After the process is finished, you need an active server instance. To establish a connection to this server, use the following command:

```shell
./build/client <server-ip>

# Examples
./build/client 52.152.198.248
./build/client # Equivalent to using the IP "127.0.0.1"
```

## Example Of How The Program Works

![Sequence Diagram Of Fast Search](images/Sequence_Diagram.jpg)

## User Documentation

To begin, run the client program in the terminal. When executing the command, specify the IP address of the server you want to connect to. If it is a local instance, you don't need to specify anything:

```shell
./build/client # Connect to 127.0.0.1
./build/client 52.152.198.248 # Connect to 52.152.198.248
```

If the given IP address is correct, the program will display the server's IP address and port to which you have connected, along with the main menu, which will appear as follows:

```text
Bienvenido

1. Ingresar origen
2. Ingresar destino
3. Ingresar hora
4. Buscar tiempo de viaje medio
5. Salir

Opcion:
```

Here, based on the query you want to make, you should enter the corresponding option. If you select options `1-3`, you should provide the value related to your query. For example:

```text
Opcion: 1
Ingrese ID del origen: 462
```

The system will display confirmation messages about the request made and prompt you to press the `ENTER` key to continue.

When you want to disconnect, simply choose option `5` from the main menu.

## Dev Documentation

---

### Client

The `client.h` header file contains the definitions for the client program.

#### Client Macros

- `SERVER_HOST`: This macro defines the default server IP address as "127.0.0.1". It is used when no IP address is specified during program execution.
- `SERVER_PORT`: This macro defines the default server port number as 8080. It is used when no port number is specified during program execution.

#### Client Header Guard

The header guard `#ifndef _CLIENT_H_` `#define _CLIENT_H_` `#endif` ensures that the contents of the header file are only included once in the compilation process. It prevents multiple inclusions and potential naming conflicts.

Ensure that the `client.h` header file is properly included in the source file(s) that require access to the client program's definitions and macros.

---

### File

The `file.h` header file contains function declarations and definitions related to file handling operations.

#### File Dependencies

- stdio.h
- stdlib.h
- string.h
- [file.h](#file)
- [structures.h](#structures)
- [pre_process.h](#pre-process)

#### File Functions

```c
FILE *open_file(char const *path_file, char const *mode);
```

- **Description**: This function opens a file in the specified mode.
- **Parameters:**
  - `path_file`: The path of the file to open.
  - `mode`: The mode in which to open the file (e.g., "r", "w", "a", etc.).
- **Returns:** A pointer to the opened file.
- **Errors:** If the file cannot be opened, the function will print an error message using `perror()` and exit the program with a failure status.

```c
void remove_line(FILE *fp);
```

- **Description:** This function removes a line from a file.
- **Parameters:**
  - `fp`: A pointer to the file from which to remove a line.
- **Note:** This function reads the file character by character until it reaches the end of the current line (indicated by a newline character).

```c
long write_list(node_t *head, FILE *fp);
```

- **Description:** This function writes a linked list to a file.
- **Parameters:**
  - `head`: A pointer to the head node of the linked list to write.
  - `fp`: A pointer to the file to write the linked list to.
- **Returns:** The starting position in the file where the linked list was written.
- **Note:** This function writes each node of the linked list to the file using `fwrite()`. The size of each node is determined by `sizeof(node_t)`.

```c
void write_hash(hash_t *ptr_hash, FILE *hash_fp, FILE *list_fp);
```

- **Description:** This function writes the hash table to files.
- **Parameters:**
  - `ptr_hash`: A pointer to the hash table to write to files.
  - `hash_fp`: A pointer to the file to write the hash table index.
  - `list_fp`: A pointer to the file to write the linked lists.
- **Note:** This function iterates over each header in the hash table and writes the corresponding linked list to the list file. It then creates a new index with the source ID and starting position of the linked list in the list file and writes this index to the hash file using `fwrite()`.

```c
long get_pos_by_srcid(unsigned short srcid);
```

- **Description:** This function retrieves the starting position of a linked list in the list file given a source ID from the hash file.
- **Parameters:**
  - `srcid`: The source ID to search for in the hash file.
- **Returns:** The starting position of the linked list in the list file if found, or -1 if not found.
- **Note:** This function opens the hash file for reading and searches for an index with the provided source ID. If found, it returns the starting position of the corresponding linked list in the list file. If not found, it returns -1.

```c
long get_pos_by_srcid(unsigned short srcid);
```

- **Description:** This function calculates the mean travel time for a specific cache.
- **Parameters:**
  - `cache`: A pointer to the cache to calculate the mean travel time for.
- **Returns:** The mean travel time for the specified cache, or -1.0 if the cache cannot be found.
- **Note:** This function retrieves the starting and ending positions of the linked list for the specified cache using the `get_pos_by_srcid()` function. It then searches the linked list in the list file for the cache, and if found, returns the mean travel time for the cache. If the cache cannot be found, the function returns -1.0.

**Note:** It's important to include the necessary header files and dependencies in your implementation to ensure the proper functioning of the functions declared in `file.h`.

---

### Logger

The `logger.h` header file contains function declarations and definitions for logging operations.

#### Logger Dependencies

- stdio.h
- stdlib.h
- time.h
- pthread.h
- [file.h](#file)

#### Logger Macros

- `LOG_FILE_PATH`: The file path for the log file.
- `DATE_LOG_FORMAT`: The format string for the date log entry.
- `CLIENT_LOG_FORMAT`: The format string for the client log entry.
- `CLIENT_CONNECT_FORMAT`: The format string for the client connection log entry.
- `CLIENT_DISCONNECT_FORMAT`: The format string for the client disconnection log entry.
- `CLIENT_SEND_ACTION_FORMAT`: The format string for the client send action log entry.
- `CLIENT_REQUEST_ACTION_FORMAT`: The format string for the client request action log entry.
- `CLIENT_REQUEST_ERROR_FORMAT`: The format string for the client request error log entry.

#### Logger Global Variables

- `mutex`: Mutex for synchronizing access to the log file.

#### Logger Functions

```c
void write_date(FILE *file);
```

- **Description:** Writes the current date to a logs file in the specified format.
- **Parameters:**
  - `file`: A pointer to the file to write the date to (must be opened in "a" mode).

```c
void write_client(FILE *file, const char *client_ip);
```

- **Description**: Writes the client IP to a logs file in the specified format.
- **Parameters**:
  - `file`: A pointer to the file to write the client IP to (must be opened in "a" mode).
  - `client_ip`: A string of size `INET_ADDRSTRLEN` containing the client IP.

```c
void log_client_connect(const char *client_ip);
```

- **Description:** Logs a client connection event.
- **Parameters:**
  - `client_ip`: A string of size `INET_ADDRSTRLEN` containing the client IP.

```c
void log_client_disconnect(const char *client_ip);
```

- **Description:** Logs a client disconnection event.
- **Parameters:**
  - `client_ip`: A string of size `INET_ADDRSTRLEN` containing the client IP.

```c
void log_client_send_data(const char *client_ip, const char *type_data, unsigned short data);
```

- **Description:** Logs a client data send event.
- **Parameters:**
  - `client_ip`: A string of size `INET_ADDRSTRLEN` containing the client IP.
  - `type_data`: A string containing the option selected by the client.
  - `data`: The data value being sent.

```c
void log_client_request_data(const char *client_ip, float data);
```

- **Description:** Logs a client data request event.
- **Parameters:**
  - `client_ip`: A string of size `INET_ADDRSTRLEN` containing the client IP.
  - `data`: The requested data value.

**Note:** The log entries are formatted using the provided format strings and the relevant information is substituted into the respective placeholders. The log entries are then written to the log file specified by `LOG_FILE_PATH`. The access to the log file is synchronized using the `mutex` to ensure thread safety. Ensure that the necessary file handling operations are implemented in the corresponding source file.

---

### Menu

The Menu.h header file contains function declarations for menu-related operations.

#### Menu Dependencies

- stdio.h
- stdlib.h
- unistd.h
- [menu.h](#menu)
- [file.h](#file)
- [protocol.h](#protocol)
- [structures.h](#structures)

#### Menu Macros

- `SRCID_OPTION`: Constant representing the source ID option.
- `DSTID_OPTION`: Constant representing the destination ID option.
- `HOD_OPTION`: Constant representing the hour of the day option.
- `SEARCH_OPTION`: Constant representing the search option.
- `EXIT_OPTION`: Constant representing the exit option.

#### Menu Functions

```c
long get_num_from_input(long min, long max);
```

- **Description:** Prompts the user to input a number within a specified range.
- **Parameters:**
  - `min`: The minimum allowed value.
  - `max`: The maximum allowed value.
- **Returns:** The number input by the user that falls within the specified range.

```c
void menu_actions(int option, int socket_fd);
```

- **Description:** Manages options based on the selected menu option.
- **Parameters:**
  - `option`: An integer representing the option chosen by the user in the menu.
  - `socket_fd`: The socket file descriptor.
- **Note:** This function uses the `secure_send_int()` and `secure_send_long()` functions to send data to the server.

```c
void main_menu(int socket_fd);
```

- **Description:** Displays the main menu and executes the selected option.
- **Parameters:**
  - `socket_fd`: The socket file descriptor.
- **Note:** This function displays a menu with several options related to the transportation system. It prompts the user to choose an option by entering a number from 1 to 5. Depending on the option selected, it may call the `menu_actions()` function to perform specific actions. This function will continue to display the menu until the user selects option 5 to exit the program.

---

**Note:** The `get_num_from_input()` function prompts the user to enter a number within a specified range. The `menu_actions()` function manages options based on the selected menu option and communicates with the server using the provided `socket_fd`. The `main_menu()` function displays the main menu, handles user input, and executes the selected option until the user chooses to exit the program.

---

### Pre Process

The `pre_process.h` is a header file contains preprocessor macros and function declarations for pre-processing operations.

#### Preprocessor Dependencies

- stdio.h
- stdlib.h
- unistd.h
- [file.h](#file)
- [structures.h](#structures)

#### Preprocessor Macros

- `DEFAULT_PATH_DATA`: Default file location for the raw Uber data.
- `DEFAULT_PATH_LIST`: Default file location for the processed list.
- `DEFAULT_PATH_HASH`: Default file location for the processed hash.
- `DELIMITER_CSV_STRING`: Delimiter string used in the CSV file.
- `DELIMITER_CSV_CHAR`: Delimiter character used in the CSV file.
- `NUM_PARAMS_TO_TAKE`: Number of parameters to extract from each line of the CSV file.
- `NUM_PARAMS_INT`: Number of integer parameters in each line of the CSV file.
- `BUFFER_SIZE`: Size of the buffer used for reading data from a file.

#### Preprocessor Structure

```c
typedef struct {
  unsigned short srcid;   # Source ID
  unsigned short dstid;   # Destination ID
  unsigned char hod;      # Hour of the day
  float mean_travel_time; # Mean travel time
} raw_t;
```

#### Preprocessor Functions

```c
raw_t *new_raw();
```

- **Description:** Creates a new instance of the `raw_t` struct.
- **Returns:** A pointer to the newly created `raw_t` struct.
- **Note:**
  - This function allocates memory for a new instance of the `raw_t` struct using the `malloc` function.
  - If the allocation fails, the function exits the program with an error message.

```c
void clear_buffer(char *buffer, int size_buff);
```

- **Description:** Clears the contents of a buffer.
- **Parameters:**
  - `buffer`: A pointer to the buffer to be cleared.
  - `size_buff`: The size of the buffer to be cleared.

```c
const char *get_data(FILE *fp, char *buffer, int size_buff);
```

- **Description:** Reads data from a CSV file, storing it in a buffer.
- **Parameters:**
  - `fp`: The file pointer to the CSV file to read from.
  - `buffer`: The buffer where the data will be stored.
  - `size_buff`: The size of the buffer.
- **Returns:** A pointer to the buffer containing the data, or `NULL` if the end of file has been reached.
- **Note:**
  - This function uses the `fgets` function to read data from the file.
  - If the file pointer is `NULL`, the function exits the program with an error message.

```c
raw_t *parse_data(char *buffer);
```

- **Description:** Parse data from a buffer in CSV format and return a new `raw_t` struct.
- **Parameters:**
  - `buffer`: A pointer to the buffer containing the CSV-formatted data.
- **Returns:** A pointer to a new `raw_t` struct containing the parsed data.

```c
void process_line(char *buffer, hash_t *ptr_hash)
```

- **Description:** Process a line of CSV-formatted data by parsing it into a raw_t struct and inserting it into the given hash table.
- **Parameters:**
  - `buffer`: A pointer to the buffer containing the CSV-formatted data to be processed.
  - `ptr_hash`: A pointer to the hash table where the parsed data will be inserted.

---

### Protocol

The `protocol.h` file contains the declarations of constants, macros, and function prototypes for a communication protocol implemented in C.

#### Protocol Dependencies

- stdio.h
- stdlib.h
- stdint.h
- string.h
- arpa/inet.h
- [protocol.h](#protocol)

#### Protocol Macros

- `SERVER_CONN_CONFIRMATION`: Represents the hexadecimal value `0x01`, indicating a server connection confirmation message.
- `SERVER_CONN_REJECTION`: Represents the hexadecimal value `0x02`, indicating a server connection rejection message.
- `SERVER_SEND_MESSAGE`: Represents the hexadecimal value `0x03`, indicating a server send message.
- `SERVER_RECV_MESSAGE`: Represents the hexadecimal value `0x04`, indicating a server receive message.
- `CLIENT_CONN_CONFIRMATION`: Represents the hexadecimal value `0x11`, indicating a client connection confirmation message.
- `CLIENT_DISCONNECTION`: Represents the hexadecimal value `0x12`, indicating a client disconnection message.
- `CLIENT_SEND_MESSAGE`: Represents the hexadecimal value `0x13`, indicating a client send message.
- `CLIENT_RECV_MESSAGE`: Represents the hexadecimal value `0x14`, indicating a client receive message.
- `FAKE_SIGNAL`: Represents the value `0`, used for fake signal purposes.
- `BUFFER_SIZE`: Represents the size of the buffer used for communication, set to `1024`.

#### Protocol Functions

```c
void int_to_string(int value, char *buffer, size_t buffer_size);
```

- **Description:** This function converts an integer to a string, and stores it in a buffer.
- **Parameters:**
  - `value`: Integer to be converted.
  - `buffer`: Buffer where the string will be stored.
  - `buffer_size`: Size of the buffer.

```c
void long_to_string(long value, char *buffer, size_t buffer_size);
```

- **Description:** This function converts a long to a string, and stores it in a buffer.
- **Parameters:**
  - `value`: Long to be converted.
  - `buffer`: Buffer where the string will be stored.
  - `buffer_size`: Size of the buffer.

```c
void float_to_string(float value, char *buffer, size_t buffer_size);
```

- **Description:** This function converts a float to a string, and stores it in a buffer.
- **Parameters:**
  - `value`: Float to be converted.
  - `buffer`: Buffer where the string will be stored.
  - `buffer_size`: Size of the buffer.

```c
void secure_send(int socket_fd, const char *string);
```

- **Description:** This function sends a string through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `string`: String to be sent.
- **Notes:**
  - First, the function sends the size of the string, in network byte order, and then it sends the string itself.
  - The string must be null-terminated.

```c
void secure_send_int(int socket_fd, int value);
```

- **Description:** This function sends an integer through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Integer to be sent.
- **Note:** First, the function converts the integer to a string, and then it sends the string through the socket.

```c
void secure_send_long(int socket_fd, long value);
```

- **Description:** This function send an long through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Long to be sent.
- **Note:** First, the function converts the long to a string, and then it sends the string through the socket.

```c
void secure_send_float(int socket_fd, float value);
```

- **Description:** This function send an float through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Float to be sent.
- **Note:** First, the function converts the float to a string, and then it sends the string through the socket.

```c
void secure_recv_string(int socket_fd, char *buffer, size_t size_buffer);
```

- **Description:** This function receives a string through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `buffer`: Buffer where the string will be stored.
  - `size_buffer`: Size of the buffer.
- **Note:** First, the function receives the size of the string, in network byte order, and then it receives the string itself.

```c
void secure_recv_int(int socket_fd, int *value);
```

- **Description:** This function receives an integer through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Integer to be received.
- **Note:** First, the function receives the string through the socket, and then it converts the string to an integer.

```c
void secure_recv_long(int socket_fd, long *value);
```

- **Description:** This function receives an long through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Long to be received.
- **Note:** First, the function receives the string through the socket, and then it converts the string to an long.

```c
void secure_recv_float(int socket_fd, float *value);
```

- **Description:** This function receives an float through a socket.
- **Parameters:**
  - `socket_fd`: Socket file descriptor.
  - `value`: Float to be received.
- **Note:** First, the function receives the string through the socket, and then it converts the string to an float.

---

### Search

This header file declares the function `search_actions` used for performing search actions based on selected options and cache data.

#### Search Dependencies

- stdio.h
- stdlib.h
- unistd.h
- [search.h](#search)
- [menu.h](#menu)
- [file.h](#file)
- [logger.h](#logger)
- [protocol.h](#protocol)
- [structures.h](#structures)

#### Search Functions

```c
int have_all_data(cache_t *cache);
```

- **Description:** Check if all the necessary data is in the cache.
- **Parameters:**
  - `cache` The cache to check.
- **Return:** Returns 1 if all the necessary data is in the cache, -1 otherwise.

```c
int search_actions(client_conn_t *client_conn, cache_t *cache);
```

- **Description:** Search actions based on selected option and cache data.
- **Parameters:**
  - `socket_fd`: The socket file descriptor.
  - `cache`: Struct containing the cache data.
- **Return:** Returns `EXIT_SUCCESS` or `EXIT_FAILURE` depending on the selected option.

---

### Server

#### Server Dependencies

- stdio.h
- stdlib.h
- unistd.h
- string.h
- stdint.h
- pthread.h
- sys/types.h
- sys/socket.h
- netinet/in.h
- arpa/inet.h
- [server.h](#server)
- [search.h](#search)
- [socket.h](#socket)
- [logger.h](#logger)
- [protocol.h](#protocol)
- [structures.h](#structures)

#### Server Macros

- `MAX_CONNS`: Maximum number of connections allowed by the server.
- `HOST`: The host IP address.
- `PORT`: The port number to listen on.

#### Server Global Variables

- `mutex_conns`: Mutex for synchronizing access to the conns counter.
- `ACTUAL_CONNS`: Number of active connections.

#### Server Functions

```c
void create_queue_conns(int queue_fd[2], queue_conn_t *queue_conn);
```

- **Description:** Create a queue conns object.
- **Parameters:**
  - `queue_fd`: Array of file descriptors.
  - `queue_conn`: Struct containing the queue connections (empty).

```c
void enqueue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn);
```

- **Description:** Enqueue a client connection to the queue.
- **Parameters:**
  - `queue_conns`: Struct containing the queue pipe file descriptors.
  - `client_conn`: Struct containing the client connection data.

```c
void dequeue_conn(queue_conn_t *queue_conns, client_conn_t *client_conn);
```

- **Description:** Dequeue a client connection from the queue.
- **Parameters:**
  - `queue_conns`: Struct containing the queue pipe file descriptors.
  - `client_conn`: Struct containing the client connection data.

```c
int server_start_listen(int server_fd, int max_conns);
```

- **Description:** Start the listening process of the server.
- **Parameters:**
  - `server_fd`: Server socket file descriptor.
  - `max_conns`: Maximum number of connections.
- **Return:** Status of the listen process.

```c
void server_accept_client(int server_fd, client_conn_t *client_conn, queue_conn_t *queue_conns);
```

- **Description:** Accept a client connection and send it to the queue.
- **Parameters:**
  - `server_fd`: Server socket file descriptor.
  - `client_conn`: Struct to save the client connection data.
  - `queue_conns`: Struct containing the queue pipe file descriptors.

```c
void secure_disconnect_client(client_conn_t *client_conn);
```

- **Description:** Disconnect a client connection and free the memory.
- **Parameters:**
  - `client_conn`: Struct containing the client connection data.

```c
void *worker_routine(void *args);
```

- **Description:** Worker thread routine - Manage the client connection.
- **Parameters:**
  - `args`: Struct pointer containing the client connection data.
- **Notes:**
  - This method is executed by each worker thread.
  - In case of error, the thread is canceled and the client is disconnected.

```c
void create_worker_thread(client_conn_t *client_conn, pthread_t *worker_thread);
```

- **Description:** Create a worker thread object, and save in the method arguments.
- **Parameters:**
  - `client_conn`: Struct pointer containing the client connection data.
  - `worker_thread`: Pointer to the worker thread object.
- **Note:** In case of error, the client connection is disconnected.

```c
void *scheduler_routine(void *args);
```

- **Description:** Scheduler thread routine - Manage queue of client connections and create worker threads.
- **Parameters:**
  - `args`: Struct pointer containing the queue pipe file descriptors.
- **Note:** This method is executed by the scheduler thread.

```c
void create_scheduler_thread(queue_conn_t *queue_conns, pthread_t *scheduler_thread);
```

- **Description:** Create a scheduler thread object, and save in the method arguments.
- **Parameters:**
  - `queue_conns`: Struct pointer containing the queue pipe file descriptors.
  - `scheduler_thread`: Pointer to the scheduler thread object.
- **Note:** In case of error, the program is terminated.

---

### Socket

This header file contains the declarations of functions related to socket operations.

#### Socket Dependencies

- stdio.h
- stdlib.h
- string.h
- sys/types.h
- sys/socket.h
- netinet/in.h
- arpa/inet.h
- [server.h](#server)

#### Socket Functions

```c
int create_socket();
```

- **Description:** Create a socket object.
- **Return:** File descriptor of the socket.

```c
int socket_bind_server(int server_fd, unsigned int port);
```

- **Description:** Bind a server socket to a port.
- **Parameters:**
  - `server_fd`: File descriptor of the socket.
  - `port`: Port to bind the socket.
- **Return:** Status of the bind.

```c
int socket_connect_client(int client_fd, char *host, unsigned int port);
```

- **Description:** Configure the socket to connect to a server.
- **Parameters:**
  - `client_fd`: File descriptor of the socket.
  - `host`: Host to connect.
  - `port`: Port to connect.
- **Return:** Status of the connection.

---

### Structures

This header file contains the declarations of various data structures used in the program.

#### Structures Dependencies

- stdio.h
- stdlib.h
- arpa/inet.h
- [file.h](#file)

#### Structures Macros

- `HASH_SIZE`: The size of the hash table.

#### Structures Structures

```c
// Structure of the linked node.
typedef struct Node {
  unsigned short dstid;   // The destination ID.
  unsigned char hod;      // The hour of the day.
  float mean_travel_time; // The mean travel time.
  struct Node *next;      // Pointer to the next node in the linked list.
} node_t;
```

```c
// Hash structure.
typedef struct {
  node_t *headers_list[HASH_SIZE]; // Array of linked list heads for the hash table.
} hash_t;
```

```c
// Hash elements that allow indexing the position of the pointer of each list.
typedef struct {
  unsigned short srcid; // The source ID.
  long start_pos;       // The starting position.
} index_t;
```

```c
// Storage structure for storage of user choices.
typedef struct {
  unsigned short srcid; // The source ID.
  unsigned short dstid; // The destination ID.
  char hod;             // The hour of the day.
} cache_t;
```

```c
// Characteristics of the client connection.
typedef struct {
  int client_fd;                    // The client file descriptor.
  char client_ip[INET_ADDRSTRLEN];  // The client IP address.
} client_conn_t;
```

```c
// Abstraction system for connection queue.
typedef struct {
  int enqueue;  // The enqueue operation.
  int dequeue;  // The dequeue operation.
} queue_conn_t;
```

#### Structures Functions

```c
node_t *new_node();
```

- **Description:** Creates a new node.
- **Return:** Return a pointer to the newly created node.

```c
node_t *push(node_t **head, unsigned short dstid, unsigned char hod, float mean_travel_time);
```

- **Description:** Add a new node to the beginning of a linked list.
- **Parameters:**
  - `head`: Pointer to a pointer to the head of the linked list.
  - `dstid`: The destination ID of the new node.
  - `hod`: The hour of day of the new node.
  - `mean_travel_time`: The mean travel time of the new node.
- **Return:** Pointer to the new node.

```c
hash_t *new_hash()
```

- **Description:** Creates a new hash table.
- **Return:** A pointer to the newly created hash table.
- **Note:** If the allocation fails, the function exits the program with an error message.

```c
int hash(int srcid)
```

- **Description:** Calculates the hash value for a given source ID.
- **Parameters:**
  - `srcid` The source ID to hash.
- **Return:** The hash value.
- **Note:** If the source ID is less than 1 or greater than the size of the hash table, the program will exit with `EXIT_FAILURE`.

```c
int insert(hash_t *ptr_hash, int srcid, unsigned short dstid, unsigned char hod, float mean_travel_time);
```

- **Description:** Inserts a new node with the given parameters to the hash table.
- **Parameters:**
  - `ptr_hash`: Pointer to the hash table.
  - `srcid`: The source id of the new node.
  - `dstid`: The destination id of the new node.
  - `hod`: The hour of the day of the new node.
  - `mean_travel_time`: The mean travel time of the new node.
- **Return:** The index in the hash table where the new node was inserted.

```c
index_t *new_index(unsigned short srcid, long start_pos)
```

- **Description:** Creates a new index_t struct and returns a pointer to it.
- **Parameters:**
  - `srcid`: The source ID for the index.
  - `start_pos`: The starting position for the index.
- **Return:** index_t\* A pointer to the new index_t struct.

```c
void free_hash(hash_t *ptr_hash)
```

- **Description:** Frees the memory allocated for the hash table and all its nodes.
- **Parameters:**
  - `ptr_hash`: A pointer to the hash table.a

### Run Pre Process

#### Run Pre Process Dependencies

- stdio.h
- stdlib.h
- [file.h](#file)
- [pre_process.h](#pre-process)
- [structures.h](#structures)

#### Run Pre Process Flow

The code begins with several include statements, importing necessary standard C libraries (`stdio.h`, `stdlib.h`) and custom header files (`file.h`, `pre_process.h`, `structures.h`) located in specific directories using relative paths.

```c
int main()
{
  FILE *data_fp = open_file(DEFAULT_PATH_DATA, "r");
  FILE *list_fp = open_file(DEFAULT_PATH_LIST, "wb");
  FILE *hash_fp = open_file(DEFAULT_PATH_HASH, "wb");
```

The `main()` function is the entry point of the program. It starts by declaring and initializing three `FILE` pointers: `data_fp`, `list_fp`, and `hash_fp`. These pointers will be used to work with files.

The `open_file()` function is called to open three files (`DEFAULT_PATH_DATA`, `DEFAULT_PATH_LIST`, `DEFAULT_PATH_HASH`) in different modes (`"r"` for reading, `"wb"` for writing in binary mode). The returned `FILE` pointers are assigned to the corresponding variables.

```c
  remove_line(data_fp);

  hash_t *hash_ptr = new_hash();
  char buffer[BUFFER_SIZE];

  printf("Processing data...\n");
  while (get_data(data_fp, buffer, BUFFER_SIZE) != NULL) {
    process_line(buffer, hash_ptr);
  }
```

The `remove_line()` function is called to remove the first line of the `data_fp` file.

A pointer `hash_ptr` of type `hash_t` is declared and assigned the return value of the `new_hash()` function. This function dynamically allocates memory for a new hash table and initializes it.

A character array `buffer` is declared with a size of `BUFFER_SIZE`. This buffer will be used to read data from the file.

A `while` loop is used to read data from `data_fp` using the `get_data()` function. The loop continues until there is no more data to read (`get_data()` returns `NULL`). Inside the loop, each line of data is processed using the `process_line()` function, passing the `buffer` and `hash_ptr` as arguments.

```c
  write_hash(hash_ptr, hash_fp, list_fp);
  printf("Done!\n");
```

Once the data processing loop completes, the `write_hash()` function is called to write the contents of the `hash_ptr` hash table to the `hash_fp` and `list_fp` files.

A simple "Done!" message is printed to the console.

```c
  free_hash(hash_ptr);
  fclose(data_fp);
  fclose(list_fp);
  fclose(hash_fp);

  return EXIT_SUCCESS;
}
```

The dynamically allocated memory for the hash table `hash_ptr` is freed using the `free_hash()` function.

All the opened files (`data_fp`, `list_fp`, `hash_fp`) are closed using the `fclose()` function.

Finally, the program exits with a return value of `EXIT_SUCCESS`, indicating successful execution.

Overall, the code reads data from a file, processes it using a hash table, and writes the results to other files.

### Run Server

#### Run Server Dependencies

- stdio.h
- stdlib.h
- unistd.h
- string.h
- pthread.h
- sys/socket.h
- [server.h](#server)
- [socket.h](#socket)

#### Run Server Flow

The code begins with several include statements, importing necessary standard C libraries (`stdio.h`, `stdlib.h`, `unistd.h`, `string.h`, `pthread.h`, `sys/socket.h`) and custom header files (`server.h`, `socket.h`) located in specific directories using relative paths.

```c
int main(int argc, char *argv[])
{
  // Get the port from the command line arguments or use the default value
  unsigned int port = PORT;
  if (argc >= 2) {
    char *end_ptr;
    port = (unsigned int)strtol(argv[1], &end_ptr, 10);
  }
```

The `main()` function is the entry point of the program. It takes command line arguments `argc` (argument count) and `argv` (argument vector).

The code checks if there is at least one command line argument (`argc >= 2`). If present, it converts the first argument (`argv[1]`) to an unsigned integer using `strtol()`, and assigns it to the variable `port`. If no argument is provided, it uses a default value stored in `PORT`.

```c
  // Create queue of connections
  int queue_fd[2];
  queue_conn_t *queue_conn = (queue_conn_t *)malloc(sizeof(queue_conn_t));
  create_queue_conns(queue_fd, queue_conn);
```

An array `queue_fd` of two integers is declared. It will be used for inter-process communication between the server and the scheduler thread.

A pointer `queue_conn` of type `queue_conn_t` is declared and dynamically allocated memory for it using `malloc()`. This structure holds information about the queue of connections.

The `create_queue_conns()` function is called, passing `queue_fd` and `queue_conn` as arguments. It sets up the necessary components for the inter-process communication.

```c
  // Create the server socket and bind it to the port
  int server_fd = create_socket();
  socket_bind_server(server_fd, port);
```

An integer variable `server_fd` is declared and assigned the value returned by the `create_socket()` function. This function creates a socket and returns the file descriptor for the socket.

The `socket_bind_server()` function is called, passing `server_fd` and `port` as arguments. It binds the server socket to the specified port.

```c
  // Start listening for connections
  server_start_listen(server_fd, MAX_CONNS);
```

The `server_start_listen()` function is called, passing `server_fd` and `MAX_CONNS` as arguments. It starts listening for incoming connections on the server socket.

```c
  // Create a scheduler thread to handle the queue of connections
  pthread_t *scheduler_thread = (pthread_t *)malloc(sizeof(pthread_t));
  create_scheduler_thread(queue_conn, scheduler_thread);
```

A pointer `scheduler_thread` of type `pthread_t` is declared and dynamically allocated memory for it using `malloc()`. This thread will handle the queue of connections.

The `create_scheduler_thread()` function is called, passing `queue_conn` and `scheduler_thread` as arguments. It creates the scheduler thread and sets it up to handle the queue of connections.

```c
  while (1) {
    client_conn_t *client_conn = (client_conn_t *)malloc(sizeof(client_conn_t));
    server_accept_client(server_fd, client_conn, queue_conn);
  }
```

Within an infinite `while` loop, the code continuously accepts incoming client connections using the `server_accept_client()` function. It passes the server file descriptor `server_fd`, a dynamically allocated `client_conn_t` structure `client_conn`, and the `queue_conn` structure to handle the queue of connections.

This loop ensures that the server keeps accepting new client connections and adding them to the queue for processing.

```c
  // Cleanup and exit the program
  free(scheduler_thread);
  free(queue_conn);
  close(server_fd);

  return EXIT_SUCCESS;
}
```

After the infinite loop, the program performs necessary cleanup operations:

- The memory allocated for the `scheduler_thread` is freed using `free()`.
- The memory allocated for the `queue_conn` structure is freed using `free()`.
- The server socket `server_fd` is closed using `close()`.

Finally, the program returns `EXIT_SUCCESS` to indicate successful execution.

Overall, this code sets up a server that listens for incoming client connections, accepts the connections, and adds them to a queue for processing. It uses sockets for communication and employs multithreading to handle the queue of connections efficiently.

### Run Client

#### Run Client Dependencies

- stdio.h
- stdlib.h
- unistd.h
- string.h
- signal.h
- netinet/in.h
- [menu.h](#menu)
- [client.h](#client)
- [socket.h](#socket)
- [protocol.h](#protocol)

#### Run Client Flow

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include "./menu/menu.h"
#include "./client/client.h"
#include "./socket/socket.h"
#include "./protocol/protocol.h"
```

The code includes necessary header files for standard input/output, standard library functions, system calls, signal handling, network-related structures, and custom header files for menu, client, socket, and protocol functionalities.

```c
int main(int argc, char *argv[])
{
  int client_fd = create_socket();
```

The `main()` function is the entry point of the program. It starts by creating a client socket using the `create_socket()` function, which returns a file descriptor (`client_fd`) representing the socket.

```c
  // Get the host and port from the command line arguments or use the default values
  char *host = (char *)malloc(sizeof(char) * INET_ADDRSTRLEN);
  unsigned int port = SERVER_PORT;
  strcpy(host, SERVER_HOST);
  if (argc >= 2) {
    strncpy(host, argv[1], INET_ADDRSTRLEN);
  }
  if (argc >= 3) {
    char *end_ptr;
    port = (unsigned int)strtol(argv[2], &end_ptr, 10);
  }
```

The code retrieves the host and port information from the command line arguments. If provided, the values are copied into the `host` variable and `port` variable, respectively. Otherwise, default values are used (`SERVER_HOST` and `SERVER_PORT`).

```c
  // Connect to the server
  socket_connect_client(client_fd, host, port);
```

The client socket connects to the server using the `socket_connect_client()` function. It passes the `client_fd`, `host`, and `port` to establish the connection.

```c
  // Wait server conn confirmation
  int server_msg;
  secure_recv_int(client_fd, &server_msg);
  if (server_msg != SERVER_CONN_CONFIRMATION && server_msg != SERVER_CONN_REJECTION) {
    perror("CLIENT: ERROR WHEN CONNECTING TO THE SERVER\n");
    exit(EXIT_FAILURE);
  }
  if (server_msg == SERVER_CONN_REJECTION) {
    printf("CLIENT: THE SERVER REJECT THE CONNECTION\n");
    exit(EXIT_FAILURE);
  }
```

The client waits to receive a connection confirmation message from the server using the `secure_recv_int()` function. If the received message is neither a connection confirmation nor a rejection, an error is displayed, and the program exits. If the server rejects the connection, an appropriate message is printed, and the program exits.

```c
  // Send client conn confirmation
  server_msg = CLIENT_CONN_CONFIRMATION;
  secure_send_int(client_fd, server_msg);
```

The client sends a connection confirmation message to the server using the `secure_send_int()` function. It sets the `server_msg` to `CLIENT_CONN_CONFIRMATION` before sending.

```c
  // Show main menu
  main_menu(client_fd);
```

The main menu is displayed using the `main_menu()` function. It takes the `client_fd` as an argument to perform menu-related operations.

```c
  close(client_fd);
  free(host);
  return EXIT_SUCCESS;
}
```

After the menu operations, the client socket is closed using `close()`, and the dynamically allocated memory for the `host` variable is freed using `free()`. The program then returns `EXIT_SUCCESS` to indicate successful execution.

In summary, this code represents a client program that creates a socket, connects to a server using the provided host and port, waits for a connection confirmation from the server, sends a connection confirmation to the server, and displays a main menu for further interactions with the server. It utilizes custom functions from the `socket`, `protocol`, `client`, and `menu` modules to handle the network communication and user interactions.

The main steps in the program are as follows:

1. Create a client socket using `create_socket()`.
2. Retrieve the host and port information from the command line arguments or use default values.
3. Connect to the server using `socket_connect_client()` with the client socket, host, and port.
4. Wait for a connection confirmation message from the server using `secure_recv_int()`.
5. Check the received message to ensure it is a valid connection confirmation or rejection.
6. If the connection is rejected, print an appropriate message and exit the program.
7. Send a connection confirmation message to the server using `secure_send_int()`.
8. Display the main menu using `main_menu()` to interact with the server.
9. Close the client socket with `close()` and free the memory allocated for the host variable using `free()`.
10. Return `EXIT_SUCCESS` to indicate successful execution of the program.

Overall, this code sets up a client-side application to establish a connection with a server, handle the initial handshake, and provide a menu-based interface for further communication with the server.

---
