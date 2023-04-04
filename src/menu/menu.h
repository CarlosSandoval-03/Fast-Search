#ifndef _MENU_H_
#define _MENU_H_

#define SRCID_OPTION 1
#define DSTID_OPTION 2
#define HOD_OPTION 3
#define SEARCH_OPTION 4
#define EXIT_OPTION 5

#include "../structures/structures.h"

void menu_actions(int option, piped_t *pipe_descriptors);

void main_menu(piped_t *pipe_descriptors);

#endif // !_MENU_H_