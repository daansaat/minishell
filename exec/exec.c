#include "exec.h"
// #include "../../inc/tokenizer.h"
// #include "../../inc/parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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

void    read_till_delimiter(t_filed *fd, char *delimiter)
{
	char    buff[1];
	char    line[1024];
	int		i;

	i = 0;
	fd->in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	// create_pipe(fd);
	while (read(STDIN_FILENO, buff, 1)) // replace 0 with fd->in for if input < ??
	{
		line[i] = buff[0];
		if (line[i] == '\n') {
			line[i] = '\0';
			if (strcmp(line, delimiter) == 0) //replace /w ft_strcmp!!
				break ;
			line[i] = '\n';
			write(fd->in, line, i + 1);
			i = -1;
		}
		i++;
	}
	close(fd->in);
	fd->in = open("tmp.txt", O_RDWR | O_CREAT, 0777);
	unlink("tmp.txt");
}

void    check_redirections_in(t_ast *ast, t_filed *fd, int i)
{
	while (ast->args[i] && ast->args[i]->type != TOKEN_STRING) 
    {
		if (ast->args[i]->type == TOKEN_LESS) {
			close(fd->in);
			fd->in = open(ast->args[i]->data[0], O_RDONLY);
		}
		if (ast->args[i]->type == TOKEN_DOUBLELESS) {
			close(fd->in);
			read_till_delimiter(fd, ast->args[i]->data[0]); //make it child process??
		}
		if (fd->in == -1) {
			perror("open(1)");
			exit(EXIT_FAILURE);
		}
        i++;
    }
}

void    check_redirections_out(t_ast *ast, t_filed *fd, int i)
{
	while (ast->args[i] && ast->args[i]->type != TOKEN_STRING) 
    {
		if (ast->args[i]->type == TOKEN_GREATER) {
			close(fd->out);
			fd->out = open(ast->args[i]->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (ast->args[i]->type == TOKEN_DOUBLEGREATER) {
			close(fd->out);
			fd->out = open(ast->args[i]->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		if (fd->out == -1) {
			perror("open(2)");
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
