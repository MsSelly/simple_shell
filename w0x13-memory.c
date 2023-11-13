#include "shell.h"

/**
 * bfree - this frees a pointer and sets its address to NULL.
 * @ptr: thsis is the address of the pointer to free.
 * Return: returns 1 if freed, otherwise return 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}

