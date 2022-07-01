#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_file
{
	int	tmpin;
	int	tmpout;
	int	in;
	int	out;
}				t_file;

typedef struct	s_list
{
	int		num_simple_cmds;
	char	*infile;
	char	*outfile;
	char	*cmd_args[3];
}				t_list;

void	set_pipe(t_file *fd)
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

void	do_execute(t_list *cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execvp(cmd->cmd_args[0], cmd->cmd_args);
		perror("execvp()");
		exit(1);
	}
	if (waitpid(0, &status, 0) == -1)
	{
		perror("waitpid()");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(status))
		if (WEXITSTATUS(status) == 1)
			exit(EXIT_FAILURE);
}

int	check_redirection_out(t_list *cmd, t_file *fd)
{
	if (cmd->outfile)
		return (open(cmd->outfile, O_WRONLY));
	else
		return (dup(fd->tmpout));
}

int	check_redirection_in(t_list *cmd, t_file *fd)
{
	if (cmd->infile)
		return (open(cmd->infile, O_RDONLY));
	else
		return (dup(fd->tmpin));
}

void	execute(t_list *cmd)
{
	t_file	fd;
	int i;

	fd.tmpin = dup(STDIN_FILENO);
	fd.tmpout = dup(STDOUT_FILENO);
	fd.in = check_redirection_in(cmd, &fd);
	i = 0;
	while (i <= cmd->num_simple_cmds - 1)
	{
		dup2(fd.in, STDIN_FILENO);
		close(fd.in);
		if (i == cmd->num_simple_cmds - 1)
			fd.out = check_redirection_out(cmd, &fd);
		else
			set_pipe(&fd);
		dup2(fd.out, STDOUT_FILENO);
		close(fd.out);
		do_execute(cmd);
		i++;
	}
	dup2(fd.tmpin, STDIN_FILENO);
	dup2(fd.tmpout, STDOUT_FILENO);
	close(fd.tmpin);
	close(fd.tmpout);
}

int	main(void)
{
	t_list	cmd;

	cmd.num_simple_cmds = 1;
	cmd.cmd_args[0] = "ls";
	cmd.cmd_args[1] = "-al";
	cmd.cmd_args[2] = NULL;
	execute(&cmd);
	return (0);
}