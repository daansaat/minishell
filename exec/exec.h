#ifndef EXEC_H
# define EXEC_H

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
	int		in;
	int		out;
}				t_filed;

typedef struct s_args
{
	char			**data;
	// t_tokentype		type;
}	t_args;

typedef struct s_ast
{
	t_args	*args;
	char	*infile;
	char	*outfile;
	// t_parse			type;
}	t_ast;

void	executor(t_ast *ast);

# endif
