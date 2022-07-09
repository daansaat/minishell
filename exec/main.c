#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
		t_ast  *ast;

    ast = malloc(sizeof(t_ast));

    ast->total_num_cmd = 2;

    ast->args = malloc(sizeof(t_args*) * 50);

    ast->args[0] = malloc(sizeof(t_args));
    ast->args[1] = malloc(sizeof(t_args));
    ast->args[2] = malloc(sizeof(t_args));
    ast->args[3] = malloc(sizeof(t_args));
    ast->args[4] = NULL;

    ast->args[0]->data = malloc(sizeof(char*) * 50);
    ast->args[1]->data = malloc(sizeof(char*) * 50);
    ast->args[2]->data = malloc(sizeof(char*) * 50);
    ast->args[3]->data = malloc(sizeof(char*) * 50);

    ast->args[0]->type = TOKEN_STRING;
    ast->args[0]->data[0] = "cat";
    ast->args[0]->data[1] = NULL;//"marcus";
    ast->args[0]->data[2] = NULL;

    ast->args[1]->type = TOKEN_STRING;
    ast->args[1]->data[0] = "wc";
    ast->args[1]->data[1] = NULL;//"-l";
    ast->args[1]->data[2] = NULL;

    ast->args[2]->type = TOKEN_GREATER;
    ast->args[2]->data[0] = "2";
    ast->args[2]->data[1] = NULL;
    ast->args[2]->data[2] = NULL;

    ast->args[3]->type = TOKEN_LESS;
    ast->args[3]->data[0] = "1";
    ast->args[3]->data[1] = NULL;
    ast->args[3]->data[2] = NULL;

    // ast->args[2] = NULL;
	executor(ast);
    // system("leaks exec");
	return (0);
}
