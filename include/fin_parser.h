#include "fin_commands.h"

int fin_dispatch(char **args)
{
	int status;
	pid_t pid;
	
	/* start new process */
	pid = fork();

	/* if fork() is successful */
	if (pid == 0)
	{
		/* execute arguments; handle exception of argument execution failure */
		if (execvp(args[0], args) == -1)
			perror("shrewd");
		/* exit fail regardless of success executing */
		exit(EXIT_FAILURE);
	}
	/* if there is execution exception */
	else if (pid < 0) 
	{
		perror("shrewd");
	}
	/* if there is timeout error */
	else
	{
		do
		{
			/* suspend execution, wait for process state to change */
			/* return if child has stopped */
			waitpid(pid, &status, WUNTRACED);
			/* continue while the process hasn't exited or raised a signal */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return EXIT_FAILURE;
}

int fin_execute(char **args)
{
	/* exception: if no input - empty string */
	if (args[0] == NULL)
		return EXIT_FAILURE;

	/* rule: search list of commands to find match with input string */
	for (int i = 0; i < fin_num_commands(); i++)
	{
		/* if match is found, return command and execute */
		if (strncmp(args[0], fin_command_list[i], strlen(args[0])) == 0)
			return (*fin_command_calls[i])(args);
	}

	return fin_dispatch(args);
}

char *fin_readline()
{
	/* initial memory allocation */
	char *buf = malloc(sizeof(char) * BUFSIZE);

	/* handle initial allocation exceptions */
	if (!buf)
	{
		fprintf(stderr, "shrewd: memory allocation error\n");	
		exit(EXIT_FAILURE);
	}

	/* declare variables (will be altered in while() loop) */
	int c;
	int position = 0;
	int bufsize = BUFSIZE;

	/* store data in buffer */
	while (TRUE)
	{
		c = getchar();

		if (c == EOF)
		{
			exit(EXIT_SUCCESS);
		}
		/* reset buf position, return buf if 'ENTER' */
		else if (c == '\n')
		{
			buf[position] = '\0';
			return buf;
		}
		/* normal behavior - store values in buffer */
		else
		{
			buf[position] = c;
		}
		position++;

		/* if data exceeds size of buffer */
		if (position >= bufsize)
		{
			/* increase the buffer size */
			bufsize += BUFSIZE;
			/* increase the memory allocation */
			buf = realloc(buf, bufsize);
		
			/* handle mem-alloc exceptions */
			if (!buf)
			{
				fprintf(stderr, "shrewd: memory re-allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

char **fin_parse(char *line)
{
	int bufsize = TOKEN_SIZE, position = 0;
	char *token, **tokens_backup;
	
	/* allocate memory for tokens */
	char **tokens = malloc(sizeof(char*) * bufsize);
	/* handle allocation exceptions */
	if (!tokens)
	{
		fprintf(stderr, "shrewd: memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	/* tokenize the line */
	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		/* store each token in token[position] */
		tokens[position] = token;
		position++;
		
		/* if input is too big for buffer */
		if (position >= bufsize)
		{
			/* increase buffer size */
			bufsize += TOKEN_SIZE;
			/* store a backup */
			tokens_backup = tokens;
			/* increase the memory allocation */
			tokens = realloc(tokens, sizeof(char*) * bufsize);
			
			/* handle memory allocation exceptions */
			if (!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "shrewd: memory allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
		
		/* token array is cleared*/
		token = strtok(NULL, TOKEN_DELIM);
	}
	/* last position is cleared */
	tokens[position] = NULL;

	return tokens;
}

void finnit_shell()
{
	char *lines;
	char **args;
	int status;
	
	system("clear");

	do 
	{	
		printf(">:) [$$] ");
		
		lines = fin_readline();
		args = fin_parse(lines);
		status = fin_execute(args);
	
		/* free DMA after use to avoid memleaks */	
		free(lines);
		free(args);

	} while(status);
}

