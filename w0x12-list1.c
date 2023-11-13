#include "shell.h"

/**
 * list_len - this determines the length of a linked list.
 *
 * @h: this the pointer to the first node.
 *
 * Return: this the size of the list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * list_to_strings - this converts a linked list of strings
 *
 * @head: the pointer to the first node.
 *
 * Return: Array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(my_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);

			free(strs);
			return (NULL);
		}

		str = this_my_strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - this prints all elements of a list_t linked list.
 *
 * @h: the pointer to the first node.
 *
 * Return: this is the size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		this_my_puts(convert_number(h->num, 10, 0));
		this_my_putchar(':');
		this_my_putchar(' ');
		this_my_puts(h->str ? h->str : "(nil)");
		this_my_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * node_starts_with - it return the node whose string start with given prefix
 *
 * @node: this the pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after the prefix to match.
 *
 * Return: returns matching node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = where_starts_with(node->str, prefix);

		if (p && ((c == -1) || (*p == c)))
			return (node);

		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - this gets the index of a node in a linked list
 * @head: this the pointer to the list head.
 * @node: the pointer to the node.
 *
 * Return: returns index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);

		head = head->next;
		i++;
	}
	return (-1);
}

