#include "builtins.h"
#include <stdio.h>

void    init_builtins(t_builtins *builtins)
{
	builtins[0].name = "echo";
	builtins[0].funct = ft_echo;
	builtins[1].name = NULL;
}

int    ft_echo(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
	{    
		printf("%s ", argv[i]);
		i++;
	}
	printf("\n");
	return (0);//(errno);
}