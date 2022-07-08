#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_fd
{
	int	tmpin;
	int	tmpout;
	int	in;
	int	out;
}				t_fd;

typedef struct	s_scmd
{
	int		pid;
	char	*args[3];
}				t_scmd;

typedef struct	s_cmd
{
	int		num_simple_cmds;
	char	*infile;
	char	*outfile;
	t_scmd	*scmd;
}				t_cmd;

void	set_pipe(t_fd *fd)
{
	int	fdpipe[2];

	if (pipe(fdpipe) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	fd->in = dup(fdpipe[0]); // fdpipe[0] - read - input
	fd->out = dup(fdpipe[1]); // fdpipe[1] - write - output
}

void	do_execute(t_scmd *scmd)
{
	// int	pid;
	// int	status;

	scmd->pid = fork();
	if (scmd->pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (scmd->pid == 0)
	{
		execvp(scmd->args[0], scmd->args);
		perror("execvp()");
		exit(1);
	}
	// if (waitpid(0, &status, 0) == -1)
	// {
	// 	perror("waitpid()");
	// 	exit(EXIT_FAILURE);
	// }
	// if (WIFEXITED(status))
	// 	if (WEXITSTATUS(status) == 1)
	// 		exit(EXIT_FAILURE);
}

int	check_redirection_out(t_cmd *cmd, t_fd *fd)
{
	if (cmd->outfile)
	{
		return (open(cmd->outfile, O_WRONLY));
	}
	else
		return (dup(fd->tmpout));
}

int	check_redirection_in(t_cmd *cmd, t_fd *fd)
{
	if (cmd->infile)
	{
		printf("yes\n");
		return (open(cmd->infile, O_RDONLY));
	}
	else
		return (dup(fd->tmpin));
}

void	execute(t_cmd *cmd)
{
	t_fd	fd;
	int 	i;

	fd.tmpin = dup(STDIN_FILENO);
	fd.tmpout = dup(STDOUT_FILENO);
	fd.in = check_redirection_in(cmd, &fd);
	i = 0;
	while (i <= cmd->num_simple_cmds - 1)
	{
		if (dup2(fd.in, STDIN_FILENO) == -1)
			perror("dup2()");
		close(fd.in);
		if (i == cmd->num_simple_cmds - 1)
			fd.out = check_redirection_out(cmd, &fd);
		else
			set_pipe(&fd);
		if (dup2(fd.out, STDOUT_FILENO) == -1)
			perror("dup2()");
		close(fd.out);
		do_execute(&cmd->scmd[i]);
		i++;
	}
	if (dup2(fd.tmpin, STDIN_FILENO) == -1)
		perror("dup2()");
	if (dup2(fd.tmpout, STDOUT_FILENO) == -1)
		perror("dup2()");
	close(fd.tmpin);
	close(fd.tmpout);
	waitpid(cmd->scmd[i - 1].pid, NULL, 0);
	printf("hello\n");
}

int	main(void)
{
	t_cmd	cmd;

	cmd.num_simple_cmds = 2;
	cmd.scmd = malloc(sizeof(t_scmd) * 2);
    char	*args[3];
	cmd.scmd[0].args[0] = "ls";
	cmd.scmd[0].args[1] = "-la";
	cmd.scmd[0].args[2] = NULL;
	// cmd.scmd[0].args[0] = "echo";
	// cmd.scmd[0].args[1] = "hello";
	// cmd.scmd[0].args[2] = NULL;
	// cmd.scmd[0].args[2] = NULL;
	cmd.scmd[1].args[0] = "wc";
	cmd.scmd[1].args[1] = "-c";
	cmd.scmd[1].args[1] = NULL;
	// cmd.infile = "~/Documents/codam/minishell/hello";
	execute(&cmd);
	return (0);
}