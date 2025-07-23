#include "cell.h"

t_builtin g_builtin[] = {
    //{.builtin_names="echo", .foo=cell_echo};
    //{.builtin_names="env", .foo=cell_env};
    {.builtin_names="exit", .foo=CellExit},
    {.builtin_names=NULL}
};
int status = 0;

void cellLaunch(char ** args) {
    if (Fork() == 0) {
        Execvp(args[0], args);
    } else {
        Wait(&status);
    }
}
void cellExec(char **args) {
    int i;
    const char *curr;
    i = 0;
    while((curr = g_builtin[i].builtin_names)) {
        if (!strcmp(curr, args[0])) {
            g_builtin[i].foo(args);
            return ;
        }
        ++i;
    }
    cellLaunch(args);
}
char ** cellSplitLine(char * line) {
    char **tokens;
    unsigned int position;
    size_t bufsize;

    bufsize = BUFSIZ;
    tokens = Malloc(BUFSIZ * sizeof * tokens);
    position = 0;

    for (char * token = strtok(line, DEL); token; token = strtok(NULL, DEL)) {
        tokens[position++] = token;
        if (position >= BUFSIZ) {
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(**tokens));
        }
    }
    tokens[position] = NULL;
    return tokens;
}
char * cellReadLine(void) {
    char * buf;
    size_t bufsize;
    char cwd[BUFSIZ];

    buf = NULL;
    GetCWD(cwd, sizeof(cwd));

    printf("✨ %s $>", cwd);
    if (getline(&buf, &bufsize, stdin) == -1 ) {
        free(buf);
        buf = NULL;
        if (feof(stdin)) {
            printf("End of File");
        } else {
            printf("Get Line Failed");
        }
        return buf;
    }

    return buf;
}
int main(int ac, char **av) {
    char * line;
    char ** args;
    printbanner();
    //REPL -> Read Eval Print Loop
    while ((line = cellReadLine()))
	{

		// 2) Tokens
		args = cellSplitLine(line);	

        //check if cd
		// if (args[0] && !strcmp(args[0], "cd"))
		// 	Chdir(args[1]);

        //execute
		cellExec(args);

		//Clean🧹
		free(line);
		free(args);
	

	}
    
    return EXIT_SUCCESS;
}