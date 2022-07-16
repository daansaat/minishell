#include "exec.h"

void    close_fd(t_filed *fd)
{
	if (dup2(fd->tmpin, STDIN_FILENO) == -1) {
		perror("dup2(3)");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd->tmpout, STDOUT_FILENO) == -1) {
		perror("dup2(4)");
		exit(EXIT_FAILURE);
	}
	close(fd->tmpin);
	close(fd->tmpout);
	free(fd);
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

t_filed    *init_fd(void)
{
	t_filed	*fd;
	
	fd = malloc(sizeof(t_filed));
	if (!fd) {
		perror("malloc(1)");
		exit(EXIT_FAILURE);
	}
	fd->tmpin = dup(STDIN_FILENO);
	fd->tmpout = dup(STDOUT_FILENO);
	fd->in = dup(STDIN_FILENO);
	fd->out = dup(STDOUT_FILENO);
	return (fd);
}
