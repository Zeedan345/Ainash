#include "cell.h"

int CellExit(char **args) {
    (void) args;
    exit(EXIT_SUCCESS);
}

int CellEnc(char **args) {
    extern char **environ;
    (void)args;
    if (!environ) {return 1;}
    for (int i; environ[i]; i++) {printf("%s\n", environ[i]);}
    return 0;
}
int	cellEnv(char **args)
{
	extern char	**environ;

	(void)args;
	if (!environ)
		return (1);
	for (int i = 0; environ[i]; i++)
		p("%s\n", environ[i]);
	return (0);
}