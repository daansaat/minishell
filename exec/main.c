#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	t_ast  *ast;

    ast = malloc(sizeof(t_ast));
    ast->args = malloc(sizeof(t_args));
    ast->args[0].data = malloc(sizeof(char*) * 10);
    ast->args[1].data = malloc(sizeof(char*) * 10);
    ast->args[0].data[0] = "echo";
    ast->args[0].data[1] = "idil";
    ast->args[0].data[2] = NULL;
    ast->args[1].data[0] = "wc";
    ast->args[1].data[1] = NULL;
    ast->infile = malloc(sizeof(char*) * 4);
	ast->infile[0] = "1";
	ast->infile[1] = NULL;
	// ast->infile[1] = "2";
	// ast->infile[2] = "3";
	// ast->infile = NULL;
    ast->outfile = malloc(sizeof(char*) * 4);
	ast->outfile[0] = "1";
	ast->outfile[1] = "2";
	ast->outfile[2] = NULL;
	// ast->outfile[2] = "3";
    ast->outfile_type = malloc(sizeof(int) * 4);
    ast->outfile_type[0] = 0;
    ast->outfile_type[1] = 0;
    // ast->outfile_type[2] = 0;
	executor(ast);
    // system("leaks exec");
	return (0);
}