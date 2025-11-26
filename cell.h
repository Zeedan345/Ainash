#ifndef CELL_H
#define CELL_H

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <unistd.h>

#define DEL "\n\t \v\f\r"

typedef struct s_builtin {
  const char *builtin_names;
  int (*foo)(char **);

} t_builtin;
void GetCWD(char *, size_t);
void printbanner(void);
void *Malloc(size_t);
void *Realloc(void *, size_t);

int CellExit(char **);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
pid_t Wait(int *);

int cellEnv(char **);
int cellEcho(char **);
void Chdir(const char *);

char **cellSplitLine(char *line);
char *find_command(char *cmd);
char *ask_gemini(const char *prompt);

bool validate_security(const char *command);

#endif