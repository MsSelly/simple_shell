#include "shell.h"

/**
 * my_strlen - this returns the length of a string.
 *
 * @s: This the string whose length to check.
 *
 * Return: thid the integer length of the string.
 */
int my_strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;

	return (i);
}

/**
 * this_my_strcmp - this performs lexicographic comparison of two strings.
 *
 * @s1: This the first string.
 * @s2: This the second string.
 *
 * Return: returns negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int this_my_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * where_starts_with - it will checks if a string starts with another string.
 *
 * @haystack: This the string to search.
 * @needle: This the substring to find.
 *
 * Return: this the address of the next character of haystack or NULL.
 */
char *where_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}

/**
 * this_my_strcat - this will concatenates two strings.
 *
 * @dest: This the destination buffer.
 * @src: This the source buffer.
 *
 * Return: this the pointer to the destination buffer.
 */
char *this_my_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (ret);
}

