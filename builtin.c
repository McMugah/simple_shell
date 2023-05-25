#include "simple.h"
/**
 *env - prints the current_environnement
 *@tokenizing_cmd: command entered
 *
 *Return: void
 */
void env(char **tokenizing_cmd __attribute__((unused)))
{
	int k;

	for (k = 0; environ[k] != NULL; k++)
	{
		print(environ[k], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}
/**
 * quit - exits the shell
 * @tokenizing_cmd: command entered
 *
 * Return: void
 */
void quit(char **tokenizing_cmd)
{
	int token_1 = 0, arg;
	for (; tokenizing_cmd[token_1] != NULL; token_1++);
	if (token_1 == 1)
	{
		free(tokenizing_cmd);
		free(line);
		free(commands);
		exit(status);
	}
	else if (token_1 == 2)
	{
		arg = _atoi(tokenizing_cmd[1]);
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tokenizing_cmd[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tokenizing_cmd);
			free(commands);
			exit(arg);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}
