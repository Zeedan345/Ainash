#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DEL "\n\t \v\f\r"

typedef struct s_builtin {
    const char *builtin_names;
    int(*foo)(char**);

} t_builtin;
void GetCWD(char * , size_t);
void printbanner(void);
void *Malloc(size_t);
void *Realloc(void *, size_t);

int CellExit(char **);
#endif