#include "exec.h"
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
	close(fd->in);
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

void	set_fd(t_filed *fd, int num_cmd, int total_num_cmd)
{
    if (dup2(fd->in, STDIN_FILENO) == -1) {
		perror("dup2(1)");
		exit(EXIT_FAILURE);
	}
	close(fd->in);
	if (num_cmd == total_num_cmd - 1)
        fd->out = fd->redirect_out;
	else
		create_pipe(fd);
	if (dup2(fd->out, STDOUT_FILENO) == -1) {
		perror("dup2(2)");
		exit(EXIT_FAILURE);
	}
	close(fd->out);
}

void    set_redirections(t_filed *fd)
{
    if (fd->in == 0) {
        fd->in = dup(fd->tmpin);
        if (fd->in == -1) {
            perror("dup(3)");
            exit(EXIT_FAILURE);
        }
    }
    if (fd->out == 0) {
        fd->redirect_out = dup(fd->tmpout);
        if (fd->redirect_out == -1) {
            perror("dup(4)");
            exit(EXIT_FAILURE);
        }
    }
    else
        fd->redirect_out = fd->out;
}

void    check_redirections(t_ast *ast, t_filed *fd)
{
    int i;

    i = 0;
    while (ast->args[i]) {
        if (ast->args[i]->type == TOKEN_LESS)
            fd->in = open(ast->args[i]->data[0], O_RDONLY);
        // if (ast->args[i]->type == TOKEN_DOUBLELESS)
            // still have to write
        if (fd->in == -1) {
            perror("open(1)");
            exit(EXIT_FAILURE);
        if (ast->args[i]->type == TOKEN_GREATER)
            fd->out = open(ast->args[i]->data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (ast->args[i]->type == TOKEN_DOUBLEGREATER)
            fd->out = open(ast->args[i]->data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd->out == -1) {
            perror("open(2)");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    set_redirections(fd);
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
    if (fd->tmpin == -1) {
        perror("dup(1)");
        exit(EXIT_FAILURE);
    }
	fd->tmpout = dup(STDOUT_FILENO);
    if (fd->tmpout == -1) {
        perror("dup(2)");
        exit(EXIT_FAILURE);
    }
    fd->in = 0;
    fd->out = 0;
    return (fd);
}

void	executor(t_ast *ast)
{
	t_filed	*fd;
	pid_t	cpid;
	int		i = 0;
	int		num_cmd = 0;

    fd = init_fd();
    check_redirections(ast, fd);
	while (ast->args[i])
	{
        while (ast->args[i] && ast->args[i]->type != TOKEN_STRING)
            i++;
        if (!ast->args[i])
            break ;
        set_fd(fd, num_cmd, ast->total_num_cmd);
		cpid = do_execute(ast, fd, i);
        num_cmd++;
		i++;
	}
	if (waitpid(cpid, NULL, 0) == -1){
        perror("waitpid()");
        exit(EXIT_FAILURE);
    }
    close_fd(fd);
}
