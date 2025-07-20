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