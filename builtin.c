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
		printf("%s\n", environ[i]);
	return (0);
}
int	cellEcho(char **args)
{
	int start = 1;
	bool newline = true;

	if (!args || !args[0])
		return (1);
	if (args[1] && !strcmp(args[1], "-n"))
	{
		newline = false;
		start = 2;
	}
	for (int i = start; args[i]; i++)
	{
		printf("%s", args[i]);
		if (args[i + 1])
			p(" ");
	}

	if (newline)
		printf("\n");

	return (0);
}