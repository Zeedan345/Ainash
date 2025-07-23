#ifndef CELL_H
#define CELL_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>

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
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
pid_t Wait(int *status);
#endif