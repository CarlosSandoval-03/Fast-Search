# Fast Search - Operating Systems

Author: csandovalc

## Description

The project consists of developing a fast search system using C language processes, which allows the user to efficiently search a text file with many records.

The system uses indexed files to store relevant information from the text file and improve search time. The indexed files contain relevant information for the search.

For inter-process communication, the system uses pipes, which are a communication mechanism between processes that allows efficient and secure exchange of information. Processes are responsible for searching and reading the indexed files, while pipes are used to transmit information between them.

The purpose of this project is to deepen knowledge about the operating system and apply the multiple utilities offered by POSIX.

## Run

### Prerequisites

If you do not have the processed file:

1. Download the data at the following link: [data in zip format](https://drive.google.com/file/d/1YtSBskKg5gR7Uylk8TZU_c2MkEJKwwbg/view?usp=sharing).
2. Unzip the file "uber_data.zip" and move the csv to "data/raw/".
3. Execute on terminal:

```shell
make pre_process && ./build/run_pre_process
```

### Main program

Once you have the preprocessed files, you can start the execution of the main program:

1. Execute on terminal:

```shell
make build && ./build/main
```

2. Follow the program instructions
