#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024
#define TRUE 1
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define TOKEN_DELIM "\t\r\n\a"
#define TOKEN_SIZE 64


/* prototypes for each of the calls */
int call_cd(char **args);
int call_clear(char **args);
int call_exit(char **args);
int call_help(char **args);

/* list of calls */
char *command_list[] = {
	"cd",
	"clear",
	"exit",
	"help"
};

int (*command_calls[]) (char**) = {
	&call_cd,
	&call_clear,
	&call_exit,
	&call_help
};

int num_commands()
{
	return sizeof(command_list) / sizeof(char *);
}

/* explicit declarations for shell function calls */
int call_cd(char **args)
{	
	if (args[1] == NULL)
		chdir("~");	
	else
		if (chdir(args[1]) != 0)
			perror("shrewd");

	return EXIT_FAILURE;
}

int call_clear(char **args)
{
	printf("\e[1;1H\e[2J");
	return EXIT_FAILURE;
}

int call_exit(char **args)
{
	return EXIT_SUCCESS;
}

int call_help(char **args)
{
	printf("\n\nshREWD :: developed by Brian Erickson\n");
	printf("Copyleft 2019, GNU GPL v2.0\n");
	printf("Simple shell scripting interface\n");
	printf("::::::::::::::::::::::::::::::::::\n\n");
	
	for (int i = 0; i < num_commands(); i++)
		printf("\t%s\n", command_list[i]);
	printf("\n\n");
	return EXIT_FAILURE;
}
