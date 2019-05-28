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
#define TOKEN_DELIM " \t\r\n\a"
#define TOKEN_SIZE 64

