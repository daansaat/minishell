#include "exec.h"

pid_t	do_execute(t_ast *ast, t_filed *fd, int i)
{
	pid_t	cpid;
    char    *pathname;

	cpid = fork();
	if (cpid == -1) {
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (cpid == 0) {
		close(fd->in);
        if (ft_strchr(ast->args[i]->data[0], '/'))
		    execve(ast->args[i]->data[0], ast->args[i]->data, NULL);
        else
        {
            pathname = search_path(ast->args[i]->data[0]);
            if (!pathname) {
                perror("command not found");
                exit(EXIT_FAILURE);
            }
            execve(pathname, ast->args[i]->data, NULL);
            free(pathname);
        }
		perror("execve()");
		exit(EXIT_FAILURE);
	}
	return (cpid);
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
