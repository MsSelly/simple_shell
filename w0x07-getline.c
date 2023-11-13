#include "shell.h"
/**
 * input_buf - this reads and buffers chained commands.
 * @info: Parameter struct.
 * @buf: this the Address of the buffer.
 * @len: this the address of len variable.
 *
 * Return: this the number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* it removes trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * get_input - it get a line minus the newline character.
 * @info: Parameter struct.
 *
 * Return: this the number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	this_my_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		j = i; /* this initialize new iterator to current buffer position */
		p = buf + i; /* this get pointer for return */
		check_chain(info, buf, &j, i, len);

		while (j < len) /* this Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* (this use to increment past nulled ';'') */

		if (i >= len)
		{
			i = len = 0; /* (this will reset position and length) */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*going to pass back pointer to the current command position*/
		return (my_strlen(p)); /*going to return the length of the current command*/
	}
	*buf_p = buf; /* (Else not a chain, pass back buffer from _getline()) */
	return (r); /* (Return the length of the buffer from _getline()) */
}

/**
 * read_buf - this reads a buffer.
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: returns r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - it gets the next line of input from STDIN.
 * @info: Parameter struct.
 * @ptr: this the address of the pointer to the buffer, preallocated or NULL.
 * @length: this the size of the preallocated ptr buffer if not NULL.
 *
 * Return: it returns s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);

	if (!new_p) /* THE MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * sigintHandler - the blocks Ctrl-C.
 * @sig_num: The signal number.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	this_my_puts("\n");
	this_my_puts("$ ");
	this_my_putchar(BUF_FLUSH);
}
