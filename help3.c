#include "simple.h"
/**
 *_strtok_r - tokenizes a string
 *@str: string to be tokenized
 *@del: deliter to be used to tokenize the string
 *@saving_ptr: pointer to be used to keep track of the next token
 *
 *Return: The next available token
 */
char *_strtok_r(char *str, char *del, char **saving_ptr)
{
	char *complete;

	if (str == NULL)
		str = *saving_ptr;
	if (*str == '\0')
	{
		*saving_ptr = str;
		return (NULL);
	}
	str += _strspn(str, del);
	if (*str == '\0')
	{
		*saving_ptr = str;
		return (NULL);
	}
	complete = str + _strcspn(str, del);
	if (*complete == '\0')
	{
		*saving_ptr = complete;
		return (str);
	}
	*complete = '\0';
	*saving_ptr = complete + 1;
	return (str);
}
/**
 * _atoi - changes a string to an integer
 * @string: the string to be changed
 *
 * Return: the converted int
 */
int _atoi(char *string)
{
	unsigned int value = 0;

	do {
		if (*string == '-')
			return (-1);
		else if ((*string < '0' || *string > '9') && *string != '\0')
			return (-1);
		else if (*string >= '0'  && *string <= '9')
			value = (value * 10) + (*string - '0');
		else if (value > 0)
			break;
	} while (*string++);
	return (value);
}
/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the memory previously allocated with a call to malloc
 * @previous_size: size of ptr
 * @new_size: size of the new memory to be allocated
 *
 * Return: pointer to the address of the new memory block
 */
void *_realloc(void *ptr, unsigned int previous_size, unsigned int new_size)
{
	void *temp_block;
	unsigned int temp;

	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	else if (new_size == previous_size)
		return (ptr);
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		temp_block = malloc(new_size);
		if (temp_block != NULL)
		{
			for (temp = 0; temp < min(previous_size, new_size); temp++)
			*((char *)temp_block + temp) = *((char *)ptr + temp);
			free(ptr);
			return (temp_block);
		}
		else
			return (NULL);
	}
}
/**
 * handler_ctrl_c - handles the signal raised by CTRL-C
 * @signum: signal number
 *
 * Return: void
 */
void handler_ctrl_c(int signum)
{
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}
/**
 * removing_comment - removes/ignores everything after a '#' char
 * @inputs: inputs to be used
 *
 * Return: void
 */
void removing_comment(char *inputs)
{
	int tax = 0;

	if (inputs[tax] == '#')
		inputs[tax] = '\0';
	while (inputs[tax] != '\0')
	{
		if (inputs[tax] == '#' && inputs[tax - 1] == ' ')
			break;
		tax++;
	}
	inputs[tax] = '\0';
}
