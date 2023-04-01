#include <stdio.h>
#include <stdlib.h>
#include "./structures/structures.h"

int main()
{
	hash_t *hash = new_hash();

	node_t *node = new_node(1, 2, 3.0);
	node_t *node2 = new_node(2, 3, 4.0);
	node_t *node3 = new_node(3, 4, 5.0);
	node_t *node4 = new_node(4, 5, 6.0);
	node_t *node5 = new_node(5, 6, 7.0);
	node_t *node6 = new_node(6, 7, 8.0);

	insert(hash, 2, node);
	insert(hash, 2, node2);
	insert(hash, 2, node3);
	insert(hash, 2, node4);
	insert(hash, 2, node5);
	insert(hash, 2, node6);

	for (int i = 0; i < TOTAL_DESTINY_ID; i++) {
		node_t *head = hash->headers_list[i];

		printf("index: %d\n", i);
		node_t *current = head;
		while (current != NULL) {
			printf("\tdstid: %d, hod: %d, mean_travel_time: %f \n", current->dstid, current->hod, current->mean_travel_time);
			current = current->next;
		}
	}

	return EXIT_SUCCESS;
}