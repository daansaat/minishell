#ifndef FILE_D_H
# define FILE_D_H
# include "exec.h"

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
	int		in;
	int		out;
}				t_filed;

void    init_fd(t_filed *fd);
void	set_fd(t_ast *ast, t_filed *fd, int i, int num_cmd, int total_num_cmd);
void	create_pipe(t_filed *fd);
void    close_fd(t_filed *fd);

void    read_till_delimiter(t_filed *fd, char *delimiter);
void    check_redirections_in(t_ast *ast, t_filed *fd, int i);
void    check_redirections_out(t_ast *ast, t_filed *fd, int i);

# endif