#ifndef EXEC_H
# define EXEC_H

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
	t_tokentype		type;
}	t_args;

typedef struct s_ast
{
	t_args	**args;
    int     cmd_number;
}	t_ast;

void	executor(t_ast *ast);

# endif
