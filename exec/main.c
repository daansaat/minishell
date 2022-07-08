#include "exec.h"
#include <stdlib.h>

int	main(void)
{
	t_ast  *ast;

    ast = malloc(sizeof(t_ast));
    ast->args = malloc(sizeof(t_args));
    ast->args[0].data = malloc(sizeof(char*) * 10);
    ast->args[1].data = malloc(sizeof(char*) * 10);
    ast->args[0].data[0] = "ls";
    ast->args[0].data[1] = "-l";
    ast->args[0].data[2] = NULL;
    ast->args[1].data[0] = "wc";
    ast->args[1].data[1] = NULL;
	ast->infile = NULL;
	ast->outfile = NULL;//"output.txt";
	executor(ast);
	return (0);
}