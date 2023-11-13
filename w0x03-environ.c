#include "shell.h"
/**
 * _myenv - it prints the current environment variables.
 * @info: it a structure containing potential arguments and shell information
 *
 * Return: always return 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - it gets the value of an environment variable.
 * @info: it a structure containing potential arguments and shell information.
 * @name: its the name of the environment variable.
 *
 * Return: value of the environment variable, or NULL
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = where_starts_with(node->str, name);
		if (p && *p)
			return (p);

		node = node->next;
	}

	return (NULL);
}

/**
 * _mysetenv - inializes a new environment variable or modify an existing one
 * @info: its a structure containing potential arguments and shell information.
 *
 * Return: always return 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		my_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv - it remove one or more environment variables.
 * @info: its a structure containing potential arguments and shell information.
 *
 * Return: always return 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		my_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - it populate the environment linked list.
 * @info: its a structure containing potential arguments and shell information
 *
 * Return: always return 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);

	info->env = node;

	return (0);
}

