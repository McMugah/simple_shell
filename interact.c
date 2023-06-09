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
				user_type_command = parser_command(running_cmd[0]);
				initializer(running_cmd, user_type_command);
				free(running_cmd);
			}
			free(commands);
		}
		free(line);
		exit(status);
	}
}
