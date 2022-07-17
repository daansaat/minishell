#ifndef EXEC_H
# define EXEC_H
#include "libft.h"
#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
	int		in;
	int		out;
}				t_filed;

typedef struct	s_child
{
	pid_t	pid;
	int		return_status;
	int		state;
}				t_child;

void		executor(t_ast *ast);

char    	*search_path(char *cmd);

t_filed    *init_fd(void);
void	    set_fd(t_ast *ast, t_filed *fd, int i, int num_cmd, int total_num_cmd);
void	    create_pipe(t_filed *fd);
void    	close_fd(t_filed *fd);

void    	read_till_delimiter(t_filed *fd, char *delimiter);
void    	check_redirections_in(t_ast *ast, t_filed *fd, int i);
void    	check_redirections_out(t_ast *ast, t_filed *fd, int i);

# endif
