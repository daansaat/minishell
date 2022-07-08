#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_ARGC 3

typedef struct s_args
{
	char			**data;
	// t_tokentype		type;
}	t_args;

typedef struct s_ast
{
	t_args			*args;
	// struct t_ast	*outfile;
	// struct t_ast	*infile;
	// t_parse			type;
}	t_ast;

void	executor(void)
{
	int		fdpipe[2];
	int		i = 0;
	int		num_cmd = 2;
	int		tmpin = dup(STDIN_FILENO);
	int		tmpout = dup(STDOUT_FILENO);
	pid_t	cpid;
	// pid_t	cpid2;
	char	*cmd[][MAX_ARGC + 1] = {
		{"ls", NULL},
		{"wc", NULL}
	};

	if (pipe(fdpipe) == -1) { 	// fdpipe[0] - read - input
		perror("pipe()"); 		// fdpipe[1] - write - output
		exit(EXIT_FAILURE);
	}
	while (i < num_cmd)
	{
		cpid = fork();
		if (cpid == -1) {
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		if (cpid == 0) {
			if (i != num_cmd - 1)
				dup2(fdpipe[1], STDOUT_FILENO);
			close(fdpipe[0]);
			close(fdpipe[1]);
			execvp(cmd[i][0], cmd[i]);
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
		if (dup2(fdpipe[0], STDIN_FILENO) == -1) {
			perror("dup2()");
		}
		// waitpid(-1, NULL, 0);
		i++;
	}
    // waitpid(cpid, NULL, 0);
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	close(fdpipe[0]);
	close(fdpipe[1]);
	// cpid2 = fork();
	// if (cpid2 == 0) {
	// 	dup2(fdpipe[0], STDIN_FILENO);
	// 	close(fdpipe[0]);
	// 	close(fdpipe[1]);
	// 	execvp(cmd[1][0], cmd[1]);
	// 	perror("wc()");
	// }
	// waitpid(cpid, NULL, 0);
	// waitpid(cpid2, NULL, 0);
}

int	main(void)
{
	// char	*cmd[][MAX_ARGC + 1] = {
	// 	{"ls", NULL},
	// 	{"wc", NULL}
	// };
	// t_ast	*ast;

	// ast->args[0].data[0] = "ls";
	// ast->args[0].data[1] = "-l";
	// ast->args[0].data[2] = NULL;
	// ast->args[1].data[0] = "wc";
	// ast->args[1].data[1] = NULL;

	executor();//(cmd);
	// printf("1\n");
	return (0);
}