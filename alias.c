#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIASES 100
#define MAX_ALIAS_LENGTH 50

typedef struct {
	char name[MAX_ALIAS_LENGTH];
	char value[MAX_ALIAS_LENGTH];
} Alias;

Alias aliases[MAX_ALIASES];
int aliasCount = 0;

/**
 * printAliases - Prints all aliases
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
 * printAlias - Prints a specific alias
 * @name: Name of the alias
 */
void printAlias(char *name)
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
}

/**
 * setAlias - Sets a new alias or updates an existing alias
 * @name: Name of the alias
 * @value: Value of the alias
 */
void setAlias(char *name, char *value)
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
	if (aliasCount < MAX_ALIASES)
	{
		strcpy(aliases[aliasCount].name, name);
		strcpy(aliases[aliasCount].value, value);
		aliasCount++;
	}
}

/**
 * processCommand - Processes the shell command
 * @command: The command to process
 * Return: 0 if successful, 1 otherwise
 */
int processCommand(char *command)
{
	char *name;
	char *value;

	/* Handle alias command */
	if (strcmp(command, "alias") == 0)
	{
		printAliases();
		return 0;
	}

	/* Handle alias name command */
	if (strncmp(command, "alias ", 6) == 0)
	{
		char *name = strtok(command + 6, " ");
		printAlias(name);
		return 0;
	}

	/* Handle alias name=value command */
	name = strtok(command, "=");
	value = strtok(NULL, "");
	if (name != NULL && value != NULL)
	{
		setAlias(name, value);
		return 0;
	}

	/* Handle other commands here */

	return 1;
}
