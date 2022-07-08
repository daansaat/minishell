#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

pid_t	do_execute(t_ast *ast, int i)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {
		// close(fd->in);
		execvp(ast->args[i].data[0], ast->args[i].data);
		perror("execvp()");
		exit(EXIT_FAILURE);
	}
	return (cpid);
}

void	create_pipe(t_filed *fd)
{
	int		fdpipe[2];
	
	if (pipe(fdpipe) == -1) { 	// fdpipe[0] - read - input
		perror("pipe()"); 		// fdpipe[1] - write - output
		exit(EXIT_FAILURE);
	}
	fd->in = fdpipe[0];
	fd->out = fdpipe[1];
}

void	check_redirection(t_ast *ast, t_filed *fd, int i, int num_cmd)
{
	if (i == 0 && num_cmd != 1) {
		if (ast->infile)
			fd->in = open(ast->infile, O_RDONLY);
		else
			fd->in = dup(fd->tmpin);
	}
	if (i == num_cmd - 1) {
		if (ast->outfile)
			fd->out = open(ast->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd->out = dup(fd->tmpout);
	}
}

void	set_fd(t_ast *ast, t_filed *fd, int i, int num_cmd)
{
	if (dup2(fd->in, STDIN_FILENO) == -1) {
		perror("dup2(1)");
		exit(EXIT_FAILURE);
	}
	close(fd->in);
	if (i == num_cmd - 1)
		check_redirection(ast, fd, i, num_cmd);
	else
		create_pipe(fd);
	if (dup2(fd->out, STDOUT_FILENO) == -1) {
		perror("dup2(2)");
		exit(EXIT_FAILURE);
	}
	close(fd->out);
}

void	executor(t_ast *ast)
{
	t_filed	*fd;
	pid_t	cpid;
	int		i = 0;
	int		num_cmd = 2;

	fd = malloc(sizeof(t_filed));
	fd->tmpin = dup(STDIN_FILENO);
	fd->tmpout = dup(STDOUT_FILENO);
	fd->in = dup(fd->tmpin);
	check_redirection(ast, fd, i, num_cmd);
	while (i < num_cmd)
	{
		set_fd(ast, fd, i, num_cmd);
		cpid = do_execute(ast, i);
		i++;
	}
	waitpid(cpid, NULL, 0);
	dup2(fd->tmpin, STDIN_FILENO);
	dup2(fd->tmpout, STDOUT_FILENO);
	close(fd->tmpin);
	close(fd->tmpout);
	close(fd->in);
}
