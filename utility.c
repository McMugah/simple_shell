#include "simple.h"

/** parse_command - determines the type of the command
 * @command: command to be parsed
 *
 */

int parser_command(char *commands)
{
	int tax;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	for (tax = 0; commands[tax] != '\0'; tax++)
	{
		if (commands[tax] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (tax = 0; internal_command[tax] != NULL; tax++)
	{
		if (_strcmp(commands, internal_command[tax]) == 0)
			return (INTERNAL_COMMAND);
	}
	/* @check_path - checks if a command is found in the PATH */
	path = check_path(commands);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - executes a command based on it's type
 * @tokenizing_cmd: tokenized form of the command (ls -l == {ls, -l, NULL})
 * @user_typed_command: type of the command
 *
 * Return: void
 */
void execute_command(char **tokenizing_cmd, int user_typed_command)
{
	void (*func)(char **command);

	if (user_typed_command == EXTERNAL_COMMAND)
	{
		if (execve(tokenizing_cmd[0], tokenizing_cmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (user_typed_command == PATH_COMMAND)
	{
		if (execve(check_path(tokenizing_cmd[0]), tokenizing_cmd, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}
	if (user_typed_command == INTERNAL_COMMAND)
	{
		func = get_func(tokenizing_cmd[0]);
		func(tokenizing_cmd);
	}
	if (user_typed_command == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenizing_cmd[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - checks if a command is found in the PATH
 * @command: command to be used
 *
 * Return: path where the command is found in, NULL if not found
 */
char *check_path(char *commands)
{
	char **path_arr = NULL;
	char *tmp, *tmp2, *path_copy;
	char *path = _getenv("PATH");
	int j;

	if (path == NULL || _strlen(path) == 0)
		return (NULL);
	path_copy = malloc(sizeof(*path_copy) * (_strlen(path) + 1));
	_strcpy(path, path_copy);
	path_arr = tokenizer(path_copy, ":");
	for (j = 0; path_arr[j] != NULL; j++)
	{
		tmp2 = _strcat(path_arr[j], "/");
		tmp = _strcat(tmp2, commands);
		if (access(tmp, F_OK) == 0)
		{
			free(tmp2);
			free(path_arr);
			free(path_copy);
			return (tmp);
		}
		free(tmp);
		free(tmp2);
	}
	free(path_copy);
	free(path_arr);
	return (NULL);
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */
void (*get_func(char *commands))(char **)
{
	int arr;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	for (arr = 0; arr < 2; arr++)
	{
		if (_strcmp(commands, mapping[arr].command_name) == 0)
			return (mapping[arr].func);
	}
	return (NULL);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the variable as a string
 */
char *_getenv(char *name)
{
	
	char *pair_pointers;
	char *copy_name;
  char **shell_environ;
	for (shell_environ = environ; *shell_environ != NULL; shell_environ++)
	{
		for (pair_pointers = *shell_environ, copy_name = name;
		     *pair_pointers == *copy_name; pair_pointers++, copy_name++)
		{
			if (*pair_pointers == '=')
				break;
		}
		if ((*pair_pointers == '=') && (*copy_name == '\0'))
			return (pair_pointers + 1);
	}
	return (NULL);
}