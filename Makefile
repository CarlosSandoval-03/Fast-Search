CC=gcc
CFLAGS=-Wall -g -pedantic
SRC_DIR=./src
BUILD_DIR=./build
OBJ_DIR=./obj
DATA_DIR=./data
MAIN_DEPENDENCIES=$(OBJ_DIR)/file.o $(OBJ_DIR)/pre_process.o $(OBJ_DIR)/structures.o $(SRC_DIR)/p1-odProgram.c

# Build
build: create_build_dir create_obj_dir create_data_dir $(BUILD_DIR)/main
	@echo "Building..."

$(BUILD_DIR)/main: $(MAIN_DEPENDENCIES)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/main $(MAIN_DEPENDENCIES)

# Object files
$(OBJ_DIR)/file.o: $(SRC_DIR)/file/file.c $(SRC_DIR)/file/file.h $(SRC_DIR)/pre_process/pre_process.h $(SRC_DIR)/structures/structures.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/file.o -c $(SRC_DIR)/file/file.c

$(OBJ_DIR)/pre_process.o: $(SRC_DIR)/pre_process/pre_process.c $(SRC_DIR)/pre_process/pre_process.h $(SRC_DIR)/structures/structures.h $(SRC_DIR)/file/file.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/pre_process.o -c $(SRC_DIR)/pre_process/pre_process.c

$(OBJ_DIR)/structures.o: $(SRC_DIR)/structures/structures.c $(SRC_DIR)/structures/structures.h $(SRC_DIR)/pre_process/pre_process.h $(SRC_DIR)/file/file.h
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/structures.o -c $(SRC_DIR)/structures/structures.c

# Unity Test
SRC_TEST_DIR= $(wildcard $(TEST_DIR)/*.c)
TEST_DIR=./test
RESULTS_DIR=./build/test_results
UNITY_DIR=./unity
TEST_CFLAGS=-I. -I$(UNITY_DIR) -I$(SRC_DIR) -I$(TEST_DIR) -DTEST

test: $()

# Build dirs
.PHONY: create_build_dir
create_build_dir:
	@$(shell mkdir -p $(BUILD_DIR))

.PHONY: create_obj_dir
create_obj_dir:
	@$(shell mkdir -p $(OBJ_DIR))

.PHONY: create_data_dir
create_data_dir:
	@$(shell mkdir -p $(DATA_DIR) $(DATA_DIR)/processed $(DATA_DIR)/raw)

# Clean dirs content
.PHONY: clean clean_obj clean_build
clean: clean_build clean_obj clean_processed_data

.PHONY: clean_obj
clean_obj:
	rm -rf $(OBJ_DIR)/*

.PHONY: clean_build
clean_build:
	rm -rf $(BUILD_DIR)/*

.PHONY: clean_processed_data
clean_processed_data:
	rm -rf $(DATA_DIR)/processed/*