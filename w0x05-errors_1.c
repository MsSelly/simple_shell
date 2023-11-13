#include "shell.h"
/**
 * _erratoi - it convert a string to an integer.
 * @s: this the string to be converted.
 *
 * Return: it returns 0 if no numbers in the string, -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * print_error - this prints an error message.
 * @info: this the parameter & return info struct.
 * @estr: this the string containing the specified error type.
 *
 * Return: Nothing.
 */
void print_error(info_t *info, char *estr)
{
	my_eputs(info->fname);
	my_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	my_eputs(": ");
	my_eputs(info->argv[0]);
	my_eputs(": ");
	my_eputs(estr);
}

/**
 * print_d - this prints a decimal (integer) number (base 10).
 * @input: this is the input number.
 * @fd: this the file descriptor to write to.
 *
 * Return: this the number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = this_my_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = this_my_eputchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;

	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - this converts a number to a string.
 * @num: This the number to convert.
 * @base: this the base of the conversion.
 * @flags: Argument flags.
 *
 * Return: this a string representing the converted number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - it replaces the first instance of '#' with '\0' in a str
 * @buf: This the address of the string to modify.
 *
 * Return: always returns 0.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

