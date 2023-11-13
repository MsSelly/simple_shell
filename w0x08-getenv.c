#include "shell.h"

/**
 * get_environ - it returns a string array copy of our environ.
 * @info: Structure containing potential arguments
 * Return: this a string array containing environment variables.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - this removes an environment variable.
 * @info: Structure containing potential arguments
 * @var: The string representing the environment variable to be removed.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = where_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}

	return (info->env_changed);
}

/**
 * _setenv - this initializes a new env variable or modifies an existing one.
 * @info: structure containing potential arguments.
 * @var: this the string representing the environment variable property.
 * @value: This the string representing the environment variable value.
 *
 * Return: Always return 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(my_strlen(var) + my_strlen(value) + 2);

	if (!buf)
		return (1);

	this_my_strcpy(buf, var);
	this_my_strcat(buf, "=");
	this_my_strcat(buf, value);

	node = info->env;
	while (node)
	{
		p = where_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
