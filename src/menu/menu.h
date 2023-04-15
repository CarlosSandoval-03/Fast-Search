/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _MENU_H_
#define _MENU_H_

// Option-Related Macros
#define SRCID_OPTION 1
#define DSTID_OPTION 2
#define HOD_OPTION 3
#define SEARCH_OPTION 4
#define EXIT_OPTION 5

#include "../structures/structures.h"

void menu_actions(int option, piped_t *pipe_descriptors);

void main_menu(piped_t *pipe_descriptors);

#endif // !_MENU_H_