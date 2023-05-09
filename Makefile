CC=gcc
CFLAGS=-Wall -Wextra -Werror -g -pedantic
SRC_DIR=./src
BUILD_DIR=./build
OBJ_DIR=./build/objs
DATA_DIR=./data
MAIN_DEPENDENCIES=$(OBJ_DIR)/file.o $(OBJ_DIR)/structures.o $(OBJ_DIR)/pre_process.o $(OBJ_DIR)/menu.o $(OBJ_DIR)/search.o $(OBJ_DIR)/logger.o $(OBJ_DIR)/socket.o $(OBJ_DIR)/client.o $(OBJ_DIR)/server.o
PRE_PROCESS_DEPENDENCIES=$(OBJ_DIR)/file.o $(OBJ_DIR)/structures.o
CLIENT_DEPENDENCIES=$(SRC_DIR)/protocol/protocol.h $(SRC_DIR)/client/client.h $(SRC_DIR)/client/client.c
SERVER_DEPENDENCIES=$(SRC_DIR)/protocol/protocol.h $(SRC_DIR)/logger/logger.h $(SRC_DIR)/socket/socket.h $(SRC_DIR)/server/server.h $(SRC_DIR)/server/server.c

# Build main
build: create_build_dir create_obj_dir create_data_dir $(BUILD_DIR)/server $(BUILD_DIR)/client $(BUILD_DIR)/run_pre_process
	@echo "Building pre_process script..."
	@echo "Building server..."
	@echo "Building client..."

$(BUILD_DIR)/server: $(SRC_DIR)/p2-server.c $(MAIN_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/server $^

$(BUILD_DIR)/client: $(SRC_DIR)/p2-client.c $(MAIN_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/client $^

# Build pre_process
pre_process: create_build_dir create_obj_dir create_data_dir $(BUILD_DIR)/run_pre_process
	@echo "Build pre_process..."

$(BUILD_DIR)/run_pre_process: $(PRE_PROCESS_DEPENDENCIES) $(OBJ_DIR)/pre_process.o $(SRC_DIR)/run_pre_process.c
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/run_pre_process $(PRE_PROCESS_DEPENDENCIES) $(OBJ_DIR)/pre_process.o $(SRC_DIR)/run_pre_process.c

# Object files dependencies
$(OBJ_DIR)/client.o: $(CLIENT_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/client.o -c $(SRC_DIR)/client/client.c -lm

$(OBJ_DIR)/server.o: $(SERVER_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/server.o -c $(SRC_DIR)/server/server.c -lm

$(OBJ_DIR)/socket.o: $(SRC_DIR)/socket/socket.h $(SRC_DIR)/server/server.h $(SRC_DIR)/socket/socket.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/socket.o -c $(SRC_DIR)/socket/socket.c -lm

$(OBJ_DIR)/logger.o: $(SRC_DIR)/logger/logger.h $(SRC_DIR)/logger/logger.c $(SRC_DIR)/file/file.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/logger.o -c $(SRC_DIR)/logger/logger.c

$(OBJ_DIR)/search.o: $(SRC_DIR)/structures/structures.h $(SRC_DIR)/file/file.h $(SRC_DIR)/menu/menu.h $(SRC_DIR)/search/search.h $(SRC_DIR)/search/search.c
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/search.o -c $(SRC_DIR)/search/search.c

$(OBJ_DIR)/menu.o: $(SRC_DIR)/structures/structures.h $(SRC_DIR)/file/file.h $(SRC_DIR)/menu/menu.c $(SRC_DIR)/menu/menu.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/menu.o -c $(SRC_DIR)/menu/menu.c

$(OBJ_DIR)/pre_process.o: $(PRE_PROCESS_DEPENDENCIES) $(SRC_DIR)/pre_process/pre_process.c $(SRC_DIR)/pre_process/pre_process.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/pre_process.o -c $(SRC_DIR)/pre_process/pre_process.c

$(OBJ_DIR)/file.o: $(SRC_DIR)/file/file.c $(SRC_DIR)/file/file.h $(SRC_DIR)/structures/structures.h $(SRC_DIR)/pre_process/pre_process.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/file.o -c $(SRC_DIR)/file/file.c

$(OBJ_DIR)/structures.o: $(SRC_DIR)/structures/structures.c $(SRC_DIR)/structures/structures.h $(SRC_DIR)/file/file.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/structures.o -c $(SRC_DIR)/structures/structures.c

# Build dirs
.PHONY: create_build_dir
create_build_dir:
	@$(shell mkdir -p $(BUILD_DIR))

.PHONY: create_obj_dir
create_obj_dir:
	@$(shell mkdir -p $(OBJ_DIR))

.PHONY: create_data_dir
create_data_dir:
	@$(shell mkdir -p $(DATA_DIR) $(DATA_DIR)/processed $(DATA_DIR)/raw $(DATA_DIR)/logs)

# Clean dirs content
.PHONY: clean clean_obj clean_build
clean: clean_build clean_obj

.PHONY: clean_obj
clean_obj:
	rm -rf $(OBJ_DIR)/*

.PHONY: clean_build
clean_build:
	rm -rf $(BUILD_DIR)/*

.PHONY: clean_processed_data
clean_processed_data:
	rm -rf $(DATA_DIR)/processed/*