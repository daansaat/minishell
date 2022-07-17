#ifndef EXEC_H
# define EXEC_H
# include <unistd.h>
# include <errno.h>

typedef enum e_tokentype
{
	TOKEN_null,
	TOKEN_PIPE,
	TOKEN_GREATER,
	TOKEN_LESS,
	TOKEN_DOUBLEGREATER,
	TOKEN_DOUBLELESS,
	TOKEN_STRING,
	// TOKEN_doubleQuotedString,
	// TOKEN_singleQuotedString,
	// TOKEN_unquotedString,
	TOKEN_FILEPATH
}	t_tokentype;

typedef struct s_args
{
	char			**data;
	t_tokentype		type;
}	t_args;

typedef struct s_ast
{
	t_args	**args;
	int     cmd_number;
}	t_ast;

typedef struct	s_child
{
	pid_t	pid;
	int		return_status;
	int		state;
}				t_child;

void	executor(t_ast *ast);
char    *search_path(char *cmd);

# endif
