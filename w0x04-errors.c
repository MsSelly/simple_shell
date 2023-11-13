#include "shell.h"

/**
 * my_eputs - it prints a string to standard error.
 * @str: This the string to be printed.
 *
 * Return: returns nothing.
 */
void my_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		this_my_eputchar(str[i]);
		i++;
	}
}

/**
 * this_my_eputchar - it writes a character to standard error.
 * @c: The character to print.
 *
 * Return: On successb1. On error -1 is returned
 */
int this_my_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * calling_putfd - it writes a character to a given file descriptor.
 * @c: This the character to print.
 * @fd: This the file descriptor to write to.
 *
 * Return: On success 1. On error -1 is returned
 */
int calling_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * calling_putsfd - it prints a string to a specified file descriptor.
 * @str: this the string to be printed.
 * @fd: This the file descriptor to write to.
 *
 * Return: returns the number of characters written.
 */
int calling_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += calling_putfd(*str++, fd);
	}

	return (i);
}

