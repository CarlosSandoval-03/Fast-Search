#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

FILE *open_file(char const *path_file, char const *mode);
void remove_line(FILE *fp);

#endif // _FILE_H_