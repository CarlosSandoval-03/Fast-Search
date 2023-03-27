CC=gcc
CFLAGS=-Wall -g -pedantic
SRC_DIR=./src
BIN_DIR=./bin
OBJ_DIR=./obj
DATA_DIR=./data

# Build dirs
.PHONY: create_bin_dir
create_bin_dir:
	@$(shell mkdir -p $(BIN_DIR))

.PHONY: create_obj_dir
create_obj_dir:
	@$(shell mkdir -p $(OBJ_DIR))

.PHONY: create_data_dir
create_data_dir:
	@$(shell mkdir -p $(DATA_DIR) $(DATA_DIR)/processed $(DATA_DIR)/raw)

# Clean dirs content
.PHONY: clean clean_obj clean_bin
clean: clean_bin clean_obj

.PHONY: clean_obj
clean_obj:
	rm -rf $(OBJ_DIR)/*

.PHONY: clean_obj
clean_bin:
	rm -rf $(BIN_DIR)/*


