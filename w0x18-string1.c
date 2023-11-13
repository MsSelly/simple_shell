#include "shell.h"
/**
 * this_my_strcpy - this copies a string.
 *
 * @dest: This the destination.
 * @src: This the source.
 *
 * Return: this the pointer to destination.
 */
char *this_my_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = 0;

	return (dest);
}

/**
 * this_my_strdup - this duplicates a string.
 *
 * @str: This the string to duplicate.
 *
 * Return: this a pointer to the duplicated string.
 */
char *this_my_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));

	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * this_my_puts - this will print an input string.
 *
 * @str: This the string to be printed.
 *
 * Return: Nothing.
 */
void this_my_puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		this_my_putchar(str[i]);
		i++;
	}
}

/**
 * this_my_putchar - this writes the character c to stdout.
 *
 * @c: This the character to print.
 *
 * Return: returns On success 1.
 * On error, -1 is returned.
 */
int this_my_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

