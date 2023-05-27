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

	if (user_typed_command == EXTERNAL_COMMAND ||
			user_typed_command == PATH_COMMAND)
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
