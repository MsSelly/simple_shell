#include "shell.h"
/**
 * is_chain - it tests if the current character in the buffer
 *
 * @info: This the parameter struct.
 * @buf: This the char buffer.
 * @p: this the address of the current position in buf.
 *
 * Return: returns 1 if a chain delimiter, returns 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - this checks if we should continue chaining
 *
 * @info: This the parameter struct.
 * @buf: This the char buffer.
 * @p: this the address of the current position in buf.
 * @i: this the starting position in buf.
 * @len: this the length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - this replaces an alias in the tokenized string.
 *
 * @info: This is the parameter struct.
 *
 * Return: returns 1 if replaced, returns 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);

		p = this_my_strdup(p + 1);
		if (!p)
			return (0);

		info->argv[0] = p;
	}

	return (1);
}

/**
 * replace_vars - this replaces variables in the tokenized string.
 *
 * @info: This the parameter struct.
 *
 * Return: returns 1 if replaced, returns 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!this_my_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), this_my_strdup
					(convert_number
					 (info->status, 10, 0)))
				;
			continue;
		}

		if (!this_my_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					this_my_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					this_my_strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		replace_string(&info->argv[i], this_my_strdup(""));
	}

	return (0);
}

/**
 * replace_string - this replaces a string.
 *
 * @old: this the address of the old string.
 * @new: this the new string.
 *
 * Return: returns 1 if replaced, returns 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

