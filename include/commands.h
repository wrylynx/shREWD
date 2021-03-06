#include "defs.h"

/* prototypes for each of the calls */
int call_cd(char **args);
int call_clear(char **args);
int call_exit(char **args);
int call_fin(char **args);
int call_help(char **args);

/* list of calls */
char *command_list[] = {
	"cd",
	"clear",
	"exit",
	"fin",
	"help"
};

int (*command_calls[]) (char**) = {
	&call_cd,
	&call_clear,
	&call_exit,
	&call_fin,
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

int call_fin(char **args)
{
	system("clear");
	system("./shrewd fin");
	return EXIT_FAILURE;
}

int call_help(char **args)
{
	printf("\n\nshREWD :: developed by Brian Erickson\n");
	printf("2019, MIT License\n");
	printf("Simple shell && virtual environment\n");
	printf("::::::::::::::::::::::::::::::::::\n\n");
	
	for (int i = 0; i < num_commands(); i++)
		printf("\t%s\n", command_list[i]);
	printf("\n\n");
	return EXIT_FAILURE;
}
