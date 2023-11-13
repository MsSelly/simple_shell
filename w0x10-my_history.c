#include "history.h"
/**
 * get_history_file - this will get the path to the history file
 * @info: Parameter struct.
 *
 * Return: this an allocated string containing the history file path.
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");

	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (my_strlen(dir) + my_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	this_my_strcpy(buf, dir);
	this_my_strcat(buf, "/");
	this_my_strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - this will write command history to a file.
 * @info: Parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		calling_putsfd(node->str, fd);
		calling_putfd('\n', fd);
	}

	calling_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history - this will read command history from a file.
 * @info: Parameter struct.
 *
 * Return: this the number of commands read on success, 0 on failure.
 */
int read_history(info_t *info)
{
	char *filename;
	int fd;
	ssize_t fsize;
	char *buf;

	filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open_and_verify_file(filename);
	free(filename);

	if (fd == -1)
		return (0);

	fsize = get_file_size(fd);
	if (fsize < 2)
	{
		close(fd);
		return (0);
	}

	buf = read_file_contents(fd, fsize);
	close(fd);

	if (!buf)
		return (0);

	process_file_contents(info, buf, fsize);

	free(buf);
	return (info->histcount);
}

/**
 * build_history_list - this will add an entry to the history linked list.
 * @info: Parameter struct.
 * @buf: the buffer containing the history entry.
 * @linecount: this the history line count.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history - this will renumber the history linked list after changes.
 * @info: Parameter struct.
 *
 * Return: This the new history count.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}


