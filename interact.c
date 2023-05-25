#include "simple.h"

/**
 * non_interactive - handles non_interactive mode
 *
 * Return: void
 */
void non_interactive(void)
{
	char **running_cmd = NULL;
	int val, user_type_command = 0;
	size_t n = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &n, stdin) != -1)
		{
			removing_newline(line);
			removing_comment(line);
			commands = tokenizer(line, ";");
			for (val = 0; commands[val] != NULL; val++)
			{
				running_cmd = tokenizer(commands[val], " ");
				if (running_cmd[0] == NULL)
				{
					free(running_cmd);
					break;
				}
				user_type_command = parse_command(running_cmd[0]);
				initializer(running_cmd, user_type_command);
				free(running_cmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
#include "simple.h"
/**
 * initializer - starts executing everything
 * @running_cmd: try to check current token
 * @user_typed_command: parse token
 *
 * Return: void function
 */
void initializer(char **running_cmd, int user_typed_command)
{
	pid_t PID;
	if (user_typed_command == EXTERNAL_COMMAND || user_typed_command == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(running_cmd, user_typed_command);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(running_cmd, user_typed_command);
}
