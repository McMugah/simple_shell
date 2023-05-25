#include "simple.h"
/**
 *_strcmp - compare two strings
 *@num1: first string to be compared
 *@num2: second string to be compared
 *
 * Return: difference of the two strings
 */
int _strcmp(char *num1, char *num2)
{
	int i = 0;
	while (num1[i] != '\0')
	{
		if (num1[i] != num2[i])
			break;
		i++;
	}
	return (num1[i] - num2[i]);
}
/**
 *_strcat - concatenates two strings
 *@value: string to be concatenated to
 *@source:  string to concatenate
 *
 * Return: address of the new string
 */
char *_strcat(char *value, char *source)
{
	char *new_command =  NULL;
	int age = _strlen(value);
	int val = _strlen(source);

	new_command = malloc(sizeof(*new_command) * (age + val + 1));
	_strcpy(value, new_command);
	_strcpy(source, new_command + age);
	new_command[age + val] = '\0';
	return (new_command);
}
/**
 *_strspn - gets the length of a prefix substring
 *@q: string to be searched
 *@r: string to be used
 *
 *Return: number of bytes in the initial segment of 5 which are part of accept
 */

int _strspn(char *q, char *r)
{
	int i = 0;
	int match = 0;

	while (q[i] != '\0')
	{
		if (_strchr(r, q[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}
/**
 *_strcspn - computes segment of q which consists of characters not in r
 *@q: string to be searched
 *@r: string to be used
 *
 *Return: index at which a char in q exists in r
 */
int _strcspn(char *q, char *r)
{
	int len = 0, i;
	for (i = 0; q[i] != '\0'; i++)
	{
		if (_strchr(r, q[i]) != NULL)
			break;
		len++;
	}
	return (len);
}
/**
 *_strchr - locates a char in a string
 *@x: string to be searched
 *@y: char to be checked
 *
 *Return: pointer to the first occurence of y in s
 */
char *_strchr(char *x, char y)
{
	int i = 0;

	for (; x[i] != y && x[i] != '\0'; i++)
		;
	if (x[i] == y)
		return (x + i);
	else
		return (NULL);
}