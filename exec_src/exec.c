#include "libft.h"
#include "exec.h"
#include "builtins.h"
#include "filed.h"
#include <stdio.h>
#include <stdlib.h>

pid_t	do_execute(t_ast *ast, int i)
{
	char    *pathname;

	// close(fd->in); // necessary?
	pathname = ast->args[i]->data[0];
	if (!ft_strchr(pathname, '/'))
		pathname = search_path(ast->args[i]->data[0]);
	if (!pathname)
	{
		perror("command not found");//perror(ast->args[i]->data[0]);
		// exit(127);//EXIT_FAILURE);
	}
	execve(pathname, ast->args[i]->data, NULL);
	perror("execve()");
	exit(EXIT_FAILURE); // free pathname??
}

void    do_simple_command(t_ast *ast, t_child *child, int i)
{
	t_builtins  builtins[7];
	int         j;

	j = 0;
	init_builtins(builtins);
	while (builtins[j].name)
	{
		if (ft_strcmp(ast->args[i]->data[0], builtins[j].name) == 0)
		{
			child->return_status = builtins[j].funct(ast->args[i]->data);
			return ;//(errno);
		}
		j++;
	}
	child->pid = fork();
	if (child->pid == -1) 
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (child->pid == 0)
		do_execute(ast, i);
}

void	executor(t_ast *ast)
{
	t_filed	fd;
	t_child child;
	int		i = 0;
	int		num_cmd = 0;

	init_fd(&fd);
	while (ast->args[i])
	{
		if (ast->args[i] && ast->args[i]->type == TOKEN_STRING) 
		{
			set_fd(ast, &fd, i, num_cmd, ast->cmd_number);
			do_simple_command(ast, &child, i);
			num_cmd++;
		}
		i++;
	}
	if (waitpid(child.pid, NULL, 0) == -1) 
	{
		perror("waitpid()");
		exit(EXIT_FAILURE);
	}
	close_fd(&fd);
}
