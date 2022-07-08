#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    t_ast  *ast;

    ast = malloc(sizeof(t_ast));
    ast->args = malloc(sizeof(t_args));
    ast->args[0].data = malloc(sizeof(char*));
    ast->args[1].data = malloc(sizeof(char*));
    ast->args[0].data[0] = "ls";
    ast->args[0].data[1] = "-l";
    ast->args[0].data[2] = NULL;
    ast->args[1].data[0] = "wc";
    ast->args[1].data[1] = NULL;
    ast->args[1].data[2] = NULL;
    printf("%s\n", ast->args[1].data[0]);
}


























// typedef struct s_list
// {
//     char **ptr;
// }               t_list;

// int main(void)
// {
//     t_list *str;

//     str = malloc(sizeof(t_list));
//     str->ptr = malloc(sizeof(char*));
//     str->ptr[0] = "hello";
//     str->ptr[1] = "bye";
//     str->ptr[2] = NULL;
//     printf("%s\n", str->ptr[1]);

//     // t_list str;
//     // str.ptr[0] = "hello";
//     // printf("%s\n", str.ptr[0]);

//     // char *word;
//     // word = "hello";
//     // printf("%s\n", word);
// }