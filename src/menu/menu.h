#ifndef _MENU_H_
#define _MENU_H_

#define SRCID_OPTION 1
#define DSTID_OPTION 2
#define HOD_OPTION 3
#define SEARCH_OPTION 4
#define EXIT_OPTION 5

#include "../structures/structures.h"

typedef struct {
	int write;
	int read;
} piped_t;

int search_actions(piped_t *pipe_descriptors, cache_t *cache);
void menu_actions(int option, piped_t *pipe_descriptors);

void search_menu(piped_t *pipe_descriptors, cache_t *cache);
void main_menu(piped_t *pipe_descriptors);

#endif // !_MENU_H_