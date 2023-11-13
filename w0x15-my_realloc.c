#include "shell.h"
/**
 * _memset - thsi fills memory with a constant byte.
 *
 * @s: this a pointer to the memory area.
 * @b: This the byte to fill *s with.
 * @n: This the number of bytes to be filled.
 *
 * Return: returns a pointer to the memory area s.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}

/**
 * ffree - this frees a string of strings.
 *
 * @pp: this a string of strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * _realloc - it reallocates a block of memory.
 *
 * @ptr: a pointer to the previous malloc'ated block.
 * @old_size: this the byte size of the previous block.
 * @new_size: this the byte size of the new block.
 *
 * Return: this the pointer to the reallocated block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);

	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);

	return (p);
}

