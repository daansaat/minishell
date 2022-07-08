#include "exec.h"
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
		execvp(ast->args[i].data[0], ast->args[i].data);
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

void	check_redirection_out(t_ast *ast, t_filed *fd)
{
    int i;

    i = 0;
    if (ast->outfile[i]) {
        while (ast->outfile[i]) {
            if (ast->outfile_type[i] == 0 ) // >
                fd->out = open(ast->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (ast->outfile_type[i] == 1) // >>
                fd->out = open(ast->outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd->out == -1) {
                perror("open(2)");
                exit(EXIT_FAILURE);
            }
            i++;
        }
    }
    else {
        fd->out = dup(fd->tmpout);
        if (fd->out == -1) {
            perror("dup(2)");
            exit(EXIT_FAILURE);
        }
    }
}

void	check_redirection_in(t_ast *ast, t_filed *fd)
{
    int i;
    
    i = 0;
    if (ast->infile[i]) {
        while (ast->infile[i]) {
            fd->in = open(ast->infile[i], O_RDONLY);
            if (fd->in == -1) {
                perror("open(1)");
                exit(EXIT_FAILURE);
            }
            i++;
        }
    }
    else {
        fd->in = dup(fd->tmpin);
        if (fd->in == -1) {
            perror("dup(1)");
            exit(EXIT_FAILURE);
        }
    }
}

// void    check_redirections(t_ast *ast, t_filed *fd)
// {
//     int i;

//     i = 0;
//     while (ast->args[i]) {
//         if (ast->args[i].type == TOKEN_GREATER)
//             fd->out = open(ast->outfile[i].data[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (ast->args[i].type == TOKEN_LESS)
//             fd->in = open(ast->infile[i].data[0], O_RDONLY);
//         if (ast->args[i].type == TOKEN_DOUBLEGREATER)
//             fd->out = open(ast->outfile[i].data[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
//         // if (ast->args[i].type == TOKEN_DOUBLELESS)
//             // still have to write
//         if (fd->in == -1 || fd->out == -1) {
//             perror("open(1)");
//             exit(EXIT_FAILURE);
//             }
//         i++;
//     }
//     if (fd->in == NULL) {
//         fd->in = dup(fd->tmpin);
//         if (fd->in == -1) {
//             perror("dup(1)");
//             exit(EXIT_FAILURE);
//         }
//     }
//     if (fd->out == NULL) {
//         fd->redirect_out = dup(fd->tmpout);
//         if (fd->redirect_out == -1) {
//             perror("dup(1)");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else
//         fd->redirect_out = fd->out 

// }

void	set_fd(t_ast *ast, t_filed *fd, int i, int num_cmd)
{
	if (dup2(fd->in, STDIN_FILENO) == -1) {
		perror("dup2(2)");
		exit(EXIT_FAILURE);
	}
	close(fd->in);
	if (i == num_cmd - 1)
		check_redirection_out(ast, fd);
	else
		create_pipe(fd);
	if (dup2(fd->out, STDOUT_FILENO) == -1) {
		perror("dup2(3)");
		exit(EXIT_FAILURE);
	}
	close(fd->out);
}

void	executor(t_ast *ast)
{
	t_filed	*fd;
	pid_t	cpid;
	int		i = 0;
	int		num_cmd = 1;

	fd = malloc(sizeof(t_filed));
    if (!fd) {
        perror("malloc(1)");
        exit(EXIT_FAILURE);
    }
	fd->tmpin = dup(STDIN_FILENO);
	fd->tmpout = dup(STDOUT_FILENO);
	check_redirection_in(ast, fd);
	while (i < num_cmd)
	{
		set_fd(ast, fd, i, num_cmd);
		cpid = do_execute(ast, fd, i);
		i++;
	}
	waitpid(cpid, NULL, 0);
	dup2(fd->tmpin, STDIN_FILENO);
	dup2(fd->tmpout, STDOUT_FILENO);
	close(fd->tmpin);
	close(fd->tmpout);
	close(fd->in);
    free(fd);
}
