#include "cell.h"

//WRAPPERS

void GetCWD(char * buf, size_t size) {
    if (NULL == getcwd(buf, size)){
        perror("getcwd Failed");
    }
}

void printbanner(void) {

    printf(
        "█████╗ ██╗███╗   ██╗ █████╗ ███████╗██╗  ██╗     ██╗    ██████╗ \n"
        "██╔══██╗██║████╗  ██║██╔══██╗██╔════╝██║  ██║    ███║   ██╔═████╗\n"
        "███████║██║██╔██╗ ██║███████║███████╗███████║    ╚██║   ██║██╔██║\n"
        "██╔══██║██║██║╚██╗██║██╔══██║╚════██║██╔══██║     ██║   ████╔╝██║\n"
        "██║  ██║██║██║ ╚████║██║  ██║███████║██║  ██║     ██║██╗╚██████╔╝\n"
        "╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝     ╚═╝╚═╝ ╚═════╝ \n"
        "                                                                \n"
    );
}

void *Malloc(size_t size) {
    void * ptr;
    if (size == 0) {
        return NULL;
    }
    ptr = malloc(size);
    if (!ptr) {
        perror("Malloc Failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}
void *Realloc(void *ptr, size_t size) {
    void * newPtr;

    newPtr = realloc(ptr, size);
    if (!newPtr && size !=0) {
        perror("Realloc Failed");
        exit(EXIT_FAILURE);
    }
    return (newPtr);
}
pid_t Fork(void) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }
    return pid;
}
void Execvp(const char *file, char *const argv[])
{
	if (!file || !argv)
	{
		fprintf(stderr, "Execvp: invalid arguments\n");
		exit(EXIT_FAILURE);
	}
	if (execvp(file, argv) == -1)
	{
		perror("💥CELL_Jr failed💥");
		exit(EXIT_FAILURE);
	}
}
pid_t	Wait(int *status)
{
	pid_t	result;

	if (!status)
	{
		fprintf(stderr, "Wait: status argument required\n");
		return (-1);
	}
	result = wait(status);
	if (result == -1)
		perror("Wait failed");
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status); 
	return (result);
}
void	Chdir(const char *path)
{
	if (!path)
	{
		fprintf(stderr, "cd: path argument required\n");
		return ;
	}
	if (chdir(path) == -1)
		perror("cd failed");
}