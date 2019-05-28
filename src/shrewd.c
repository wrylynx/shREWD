#include "fin_parser.h"
#include "parser.h"

void init_shell(int argc, char* argv[])
{
	if (argc != 1)
	{
		if (strncmp(argv[1], "--version", strlen(argv[1])) == 0)
		{
			printf("shREWD version 1.0.0\n");
			exit(EXIT_SUCCESS);
		}	
		else if (strncmp(argv[1], "--help", strlen(argv[1])) == 0)
		{
			call_help(argv);
			exit(EXIT_SUCCESS);
		}
		else if (strncmp(argv[1], "fin", strlen(argv[1])) == 0)
			finnit_shell();
	}
	else
		run_command();
}

int main(int argc, char* argv[])
{
	init_shell(argc, argv);
	return EXIT_SUCCESS;
}
