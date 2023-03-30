#include <stdio.h>
#include <stdlib.h>
#include "../file/file.h"
#include "../structures/structures.h"
#include "./pre_process.h"

unsigned int write_list(node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_LIST, "ab");

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

unsigned long index_list(unsigned short srcid, node_t *head)
{
	FILE *fp = open_file(DEFAULT_PATH_HASH, "ab");
	unsigned long start_pos = (unsigned long)ftell(fp);
	index_t *list_index = new_index(srcid, start_pos);

	fwrite(list_index, sizeof(index_t), 1, fp);
	write_list(head);

	return start_pos;
}