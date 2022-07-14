#include "exec.h"
// #include "../../inc/tokenizer.h"
// #include "../../inc/parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

pid_t	do_execute(t_ast *ast, t_filed *fd, int i)
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {
		close(fd->in);
		execvp(ast->args[i]->data[0], ast->args[i]->data);
		perror("execvp()");
		exit(EXIT_FAILURE);
	}
	return (cpid);
}

void	create_pipe(t_filed *fd)
{
	int		fdpipe[2];
	
	if (pipe(fdpipe) == -1) { 	
		perror("pipe()"); 		
		exit(EXIT_FAILURE);
	}
	fd->in = fdpipe[0]; // fdpipe[0] - read - input
	fd->out = fdpipe[1]; // fdpipe[1] - write -output
}

void	set_fd(t_ast *ast, t_filed *fd, int i, int num_cmd, int total_num_cmd)
{
	check_redirections_in(ast, fd, i + 1);
	if (dup2(fd->in, STDIN_FILENO) == -1) {
		perror("set_fd dup2(1)");
		exit(EXIT_FAILURE);
	}
	close(fd->in);
	if (num_cmd == total_num_cmd - 1)
		fd->out = dup(fd->tmpout);
	else
		create_pipe(fd);
	check_redirections_out(ast, fd, i + 1);
	if (dup2(fd->out, STDOUT_FILENO) == -1) {
		perror("set_fd dup2(2)");
		exit(EXIT_FAILURE);
	}
	close(fd->out);
}

void	executor(t_ast *ast)
{
	t_filed	*fd;
	pid_t	cpid;
	int		i = 0;
	int		num_cmd = 0;

	fd = init_fd();
	while (ast->args[i])
	{
		if (ast->args[i] && ast->args[i]->type == TOKEN_STRING) {
			set_fd(ast, fd, i, num_cmd, ast->cmd_number); 
			cpid = do_execute(ast, fd, i);
			num_cmd++;
		}
		i++;
	}
	if (waitpid(cpid, NULL, 0) == -1) {
		perror("waitpid()");
		exit(EXIT_FAILURE);
	}
	close_fd(fd);
}
