#include <stdio.h>
#include <stdlib.h>
#include "../file/file.h"
#include "../structures/structures.h"
#include "./pre_process.h"

unsigned int write_list(node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_LIST, "w");

	unsigned int written_nodes = 0;
	node_t *curr_node = head;
	while (curr_node != NULL) {
		fwrite(curr_node, sizeof(node_t), 1, fp);
		written_nodes++;

		curr_node = curr_node->next;
	}

	fclose(fp);
	return written_nodes;
}
