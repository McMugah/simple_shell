#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_LENGTH 100
#define MAX_COMMAND_LENGTH 100

/**
 * struct Alias - Represents an alias mapping
 * @name: The name of the alias
 * @value: The value of the alias
 */
typedef struct Alias
{
	char name[MAX_ALIAS_LENGTH];
	char value[MAX_ALIAS_LENGTH];
} Alias;

Alias aliases[MAX_ALIAS_COUNT];
int aliasCount = 0;

/**
 * printAliases - Prints all defined aliases
 */
void printAliases(void)
{
	int i;

	for (i = 0; i < aliasCount; i++)
	{
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

/**
 * printAlias - Prints the value of a specific alias
 * @name: The name of the alias to print
 */
void printAlias(const char *name)
{
	int i;

	for (i = 0; i < aliasCount; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			printf("%s='%s'\n", aliases[i].name, aliases[i].value);
			return;
		}
	}

	printf("Alias '%s' not found\n", name);
}

/**
 * setAlias - Sets the value of an alias or creates a new alias
 * @name: The name of the alias to set
 * @value: The value of the alias
 */
void setAlias(const char *name, const char *value)
{
	int i;

	for (i = 0; i < aliasCount; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			strcpy(aliases[i].value, value);
			return;
		}
	}

	if (aliasCount == MAX_ALIAS_COUNT)
	{
		printf("Maximum number of aliases reached\n");
		return;
	}

	strcpy(aliases[aliasCount].name, name);
	strcpy(aliases[aliasCount].value, value);
	aliasCount++;
}

/**
 * parseAlias - Parses and sets an alias from a command
 * @command: The command containing the alias to parse
 */
void parseAlias(char *command)
{
	char *name = strtok(command, "=");
	char *value = strtok(NULL, "=");

	if (name == NULL || value == NULL)
	{
		printf("Invalid alias format\n");
		return;
	}

	setAlias(name, value);
}

/**
 * processCommand - Processes a command and executes the appropriate action
 * @command: The command to process
 */
void processCommand(char *command)
{
	if (strncmp(command, "alias", 5) == 0)
	{
		char *arguments = command + 5;

		if (*arguments == '\0')
		{
			printAliases();
		}
		else if (*arguments == ' ')
		{
			char *name = strtok(arguments, " ");

			while (name != NULL)
			{
				printAlias(name);
				name = strtok(NULL, " ");
			}
		}
		else if (*arguments == '=')
		{
			parseAlias(arguments + 1);
		}
		else
		{
			printf("Invalid alias command\n");
		}
	}
	else
	{
		/* Handle other commands here */
		printf("Executing command: %s\n", command);
	}
}
