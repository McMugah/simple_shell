
#ifndef SIMPLE_H
#define SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1
#define min(x, y) (((x) < (y)) ? (x) : (y))
/**
 *struct map - a struct that maps a command name to a function
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **commands);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*helpers*/
void print(char *, int);
char **tokenizer(char *, char *);
void removing_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/*helpers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/*helpers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int previous_size, unsigned int new_size);
void handler_ctrl_c(int);
void removing_comment(char *);

/*utils*/
int parser_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/*built_in*/
void env(char **);
void quit(char **);

/*main*/
extern void non_interactive(void);
extern void initializer(char **running_cmd, int user_typed_command);

#endif /*SIMPLE_H*/
