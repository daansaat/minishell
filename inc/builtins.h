#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct  s_builtins
{
	char	*name;
	int		(*funct)(char **argv);
	int		builtin_count;
}				t_builtins;

void   init_builtins(t_builtins *builtins);
int    echo(char **argv);

# endif
