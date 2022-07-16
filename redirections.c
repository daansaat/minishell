#include "exec.h"

void    read_till_delimiter(t_filed *fd, char *delimiter)
{
	char    buff[1];
	char    line[1024];
	int		i;

	i = 0;
	fd->in = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
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
