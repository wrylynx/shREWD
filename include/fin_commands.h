#include "defs.h"

/* prototypes for each of the calls */
int fin_cd(char **args);
int fin_clear(char **args);
int fin_exit(char **args);
int fin_fin(char **args);
int fin_help(char **args);

/* list of calls */
char *fin_command_list[] = {
	"cd",
	"clear",
	"exit",
	"fin",
	"help"
};

int (*fin_command_calls[]) (char**) = {
	&fin_cd,
	&fin_clear,
	&fin_exit,
	&fin_fin,
	&fin_help
};

int fin_num_commands()
{
	return sizeof(fin_command_list) / sizeof(char *);
}

/* explicit declarations for shell function calls */
int fin_cd(char **args)
{	
	if (args[1] == NULL)
		chdir("~");	
	else
		if (chdir(args[1]) != 0)
			perror("shrewd");

	return EXIT_FAILURE;
}

int fin_clear(char **args)
{
	printf("\e[1;1H\e[2J");
	return EXIT_FAILURE;
}

int fin_exit(char **args)
{
	return EXIT_SUCCESS;
}

int fin_fin(char **args)
{
	system("clear");
	system("./shrewd fin");
	return EXIT_FAILURE;
}

int fin_help(char **args)
{
	printf("\n\nshREWD :: developed by Brian Erickson\n");
	printf("2019, MIT License\n");
	printf("Simple shell && virtual environment\n");
	printf("::::::::::::::::::::::::::::::::::\n\n");
	
	for (int i = 0; i < fin_num_commands(); i++)
		printf("\t%s\n", fin_command_list[i]);
	printf("\n\n");
	return EXIT_FAILURE;
}
