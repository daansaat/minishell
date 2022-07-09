#include <stdlib.h>
#include <stdio.h>

typedef enum e_tokentype
{
	TOKEN_null,
    TOKEN_PIPE,
    TOKEN_GREATER,
    TOKEN_LESS,
    TOKEN_DOUBLEGREATER,
    TOKEN_DOUBLELESS,
    TOKEN_STRING,
    // TOKEN_doubleQuotedString,
    // TOKEN_singleQuotedString,
    // TOKEN_unquotedString,
    TOKEN_FILEPATH
}	t_tokentype;

typedef struct	s_filed
{
	int		tmpin;
	int		tmpout;
    int     redirect_out;
	int		in;
	int		out;
}				t_filed;

typedef struct s_args
{
	char			**data;
	t_tokentype		type;
}	t_args;

typedef struct s_ast
{
	t_args	**args;
    int     total_num_cmd;
}	t_ast;





int	main(void)
{
	t_ast  *ast;

    ast = malloc(sizeof(t_ast));

    ast->args = malloc(sizeof(t_args*) * 50);

    ast->args[0] = malloc(sizeof(t_args) * 50);
    ast->args[1] = malloc(sizeof(t_args) * 50);
    ast->args[2] = malloc(sizeof(t_args) * 50);
    ast->args[3] = malloc(sizeof(t_args) * 50);
    ast->args[3] = NULL;

    ast->args[0]->data = malloc(sizeof(char*) * 50);
    ast->args[1]->data = malloc(sizeof(char*) * 50);
    ast->args[2]->data = malloc(sizeof(char*) * 50);
    ast->args[3]->data = malloc(sizeof(char*) * 50);

    ast->args[0]->type = TOKEN_STRING;
    ast->args[0]->data[0] = "echo";
    ast->args[0]->data[1] = "marcus";
    ast->args[0]->data[2] = NULL;

    ast->args[0]->type = TOKEN_STRING;
    ast->args[0]->data[0] = "wc";
    ast->args[0]->data[1] = NULL;//"-l";
    ast->args[0]->data[2] = NULL;

    ast->args[0]->type = TOKEN_GREATER;
    ast->args[0]->data[0] = "1";
    ast->args[0]->data[1] = NULL;//"-l";
    ast->args[0]->data[2] = NULL;

    if (ast->args[0]->type == TOKEN_STRING)
        printf("%s\n", ast->args[0]->data[0]);

    // ast->args[1]->data[0] = NULL;
    // // ast->args[1].data[0] = "wc";
    // ast->args[1]->data[1] = NULL;
    // ast->args[1] = NULL;
    // // ast->args[2].data[0] = NULL;
    // ast->infile = malloc(sizeof(char*) * 4);
	// ast->infile[0] = NULL;

    // ast->outfile = malloc(sizeof(char*) * 4);
	// ast->outfile[0] = "1";
	// // ast->outfile[0] = NULL;
	// // ast->outfile[1] = "2";
	// // ast->outfile[2] = NULL;
	// // ast->outfile[2] = "3";
    // ast->outfile_type = malloc(sizeof(int) * 4);
    // ast->outfile_type[0] = 0;
    // // ast->outfile_type[1] = 0;
    // // ast->outfile_type[2] = 0;


	// executor(ast);
    // system("leaks exec");
	return (0);
}

	// t_ast  *ast;

    // ast = malloc(sizeof(t_ast));
    // ast->args = malloc(sizeof(t_args) * 50);
    // ast->args[0]->data = malloc(sizeof(char*) * 10);
    // ast->args[1]->data = malloc(sizeof(char*) * 10);
    // ast->args[2]->data = malloc(sizeof(char*) * 10);
    // ast->args[0]->data[0] = "echo";
    // ast->args[0]->data[1] = "marcus";
    // ast->args[0]->data[2] = NULL;
    // ast->args[1]->data[0] = NULL;
    // // ast->args[1].data[0] = "wc";
    // ast->args[1]->data[1] = NULL;
    // ast->args[1] = NULL;
    // // ast->args[2].data[0] = NULL;
    // ast->infile = malloc(sizeof(char*) * 4);
	// ast->infile[0] = NULL;
	// // ast->infile[0] = "1";
	// // ast->infile[1] = NULL;
	// // ast->infile[1] = "2";
	// // ast->infile[2] = "3";
	// // ast->infile = NULL;
    // ast->outfile = malloc(sizeof(char*) * 4);
	// ast->outfile[0] = "1";
	// // ast->outfile[0] = NULL;
	// // ast->outfile[1] = "2";
	// // ast->outfile[2] = NULL;
	// // ast->outfile[2] = "3";
    // ast->outfile_type = malloc(sizeof(int) * 4);
    // ast->outfile_type[0] = 0;
    // // ast->outfile_type[1] = 0;
    // // ast->outfile_type[2] = 0;


	// // executor(ast);
    // // system("leaks exec");