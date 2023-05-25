#include "simple.h"

char *shell_name = NULL;
int status = 0;
char **commands = NULL;
char *line = NULL;

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * applies the functions in utils and helpers
 * implements EOF
 * Prints error on Failure
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char **running_cmd = NULL;
	int val, user_typed_command = 0;
	size_t n = 0;

	signal(SIGINT, handler_ctrl_c);
	shell_name = argv[0];
	while (1)
	{
		non_interactive();
		print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);
			exit(status);
		}
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
			user_typed_command = parser_command(running_cmd[0]);

			/* initializer -   */
			initializer(running_cmd, user_typed_command);
			free(running_cmd);
		}
		free(commands);
	}
	free(line);

	return (status);
}