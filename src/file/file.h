/******************************************************************************************
 * Copyright (C) 2023 by Carlos Sandoval                                                  *
 *                                                                                        *
 * This file is part of Fast-Search.                                                      *
 * @author Carlos Santiago Sandoval Casallas, https://github.com/CarlosSandoval-03        *
 * Released under the terms of the MIT license, see: https://opensource.org/license/mit/  *
 ******************************************************************************************/
#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include "../structures/structures.h"

FILE *open_file(char const *path_file, char const *mode);
void remove_line(FILE *fp);

long write_list(node_t *head, FILE *fp);
void write_hash(hash_t *ptr_hash, FILE *hash_fp, FILE *list_fp);
long get_pos_by_srcid(unsigned short srcid);
float get_mean_time(cache_t *cache);

#endif // _FILE_H_