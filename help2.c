#include "simple.h"
/**
 * tokenizer - tokenizes input and stores it into an array
 *@input_value: input to be parsed
 *@delim: delimiter to be used, needs to be one character string
 *
 *Return: array of tokens
 */

char **tokenizer(char *input_value, char *deliminator)
{
	int num_deliminator = 0;
	char **av = NULL;
	char *mytoken = NULL;
	char *jeone = NULL;

	mytoken = _strtok_r(input_value, deliminator, &jeone);

	while (mytoken != NULL)
	{
		av = _realloc(av, sizeof(*av) * num_deliminator, sizeof(*av) * (num_deliminator + 1));
		av[num_deliminator] = mytoken;
		mytoken = _strtok_r(NULL, deliminator, &jeone);
		num_deliminator++;
	}

	av = _realloc(av, sizeof(*av) * num_deliminator, sizeof(*av) * (num_deliminator + 1));
	av[num_deliminator] = NULL;

	return (av);
}

/**
 *print - prints a string to stdout
 *@string_value: string to be printed
 *@stream: stream to print out to
 *
 *Return: void, return nothing
 */
void print(char *string_value, int namespace)
{
	int j = 0;
	for (; string_value[j] != '\0'; j++)
		write(namespace, &string_value[j], 1);
}
/**
 *remove_newline - removes new line from a string
 *@str: string to be used
 *
 *
 *Return: void
 */
void removing_newline(char *string)
{
	int z = 0;
	while (string[z] != '\0')
	{
		if (string[z] == '\n')
			break;
		z++;
	}
	string[z] = '\0';
}

/**
 *_strcpy - copies a string to another buffer
 *@mysources: mysources to copy from
 *@destination: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *mysources, char *destination)
{
	int sum = 0;

	for (; mysources[sum] != '\0'; sum++)
		destination[sum] = mysources[sum];
	destination[sum] = '\0';
}

/**
 *_strlen - counts string length
 *@string: string to be counted
 *
 * Return: length of the string
 */

int _strlen(char *string)
{
	int sue = 0;

	if (string == NULL)
		return (sue);
	for (; string[sue] != '\0'; sue++)
		;
	return (sue);
}
