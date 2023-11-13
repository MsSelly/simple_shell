#include "shell.h"
/**
 * _myhistory - it displays the history list
 * @info: its a structure containing potential arguments and shell information
 *
 * Return: it always 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - it removes an alias with the specified name.
 * @info: its a structure containing potential arguments and shell information.
 * @str: its the name of the alias to remove.
 *
 * Return: always return 0 on success, or 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');

	if (!p)
		return (1);

	c = *p;
	*p = 0;

	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*p = c;
	return (ret);
}

/**
 * set_alias - it sets an alias to the specified string.
 * @info: its a structure containing potential arguments and shell information.
 * @str: this the alias string to set.
 *
 * Return: always return 0 on success, or 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');

	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - it prints an alias string in the format 'alias=value'.
 * @node: this the alias node to print.
 *
 * Return: always return 0 on success, or 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');

		for (a = node->str; a <= p; a++)
			this_my_putchar(*a);

		this_my_putchar('\'');
		this_my_puts(p + 1);
		this_my_puts("'\n");

		return (0);
	}

	return (1);
}
/**
 * _myalias - it manage aliases in the shell
 * @info: it a structure containing potential arguments and shell information
 *
 * Return: always return 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

