# Fast Search - Operating Systems

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
