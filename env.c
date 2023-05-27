#include "simple.h"

/**
 * setenv_builtin - sets a new environment variable or modifies an existing one
 * @args: arguments passed to the command
 *
 * Return: 0 on success, -1 on failure
 */
int setenv_builtin(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		print("Usage: setenv VARIABLE VALUE\n", STDERR_FILENO);
		return (-1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		print("Error: Failed to set environment variable\n", STDERR_FILENO);
		return (-1);
	}

	return (0);
}

/**
 * unsetenv_builtin - removes an environment variable
 * @args: arguments passed to the command
 *
 * Return: 0 on success, -1 on failure
 */
int unsetenv_builtin(char **args)
{
	if (args[1] == NULL)
	{
		print("Usage: unsetenv VARIABLE\n", STDERR_FILENO);
		return (-1);
	}

	if (unsetenv(args[1]) == -1)
	{
		print("Error: Failed to unset environment variable\n", STDERR_FILENO);
		return (-1);
	}

	return (0);
}

/**
 * execute_builtin - executes a built-in command
 * @args: arguments passed to the command
 *
 * Return: 0 on success, -1 on failure or if the command is not a built-in
 */
int execute_builtin(char **args)
{
	if (_strcmp(args[0], "setenv") == 0)
		return (setenv_builtin(args));

	if (_strcmp(args[0], "unsetenv") == 0)
		return (unsetenv_builtin(args));

	return (-1);
}
