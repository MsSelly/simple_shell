#include "shell.h"

/**
 * is_my_cmd - it determines if a file is an executable command.
 *
 * @info: This the info struct.
 * @path: this the path to the file.
 *
 * Return: returns 1 if true, returns 0 otherwise.
 */
int is_my_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * my_dup_chars - it duplicates characters from a string within a given range.
 *
 * @pathstr: this the PATH string.
 * @start: this the starting index.
 * @stop: this the stopping index.
 *
 * Return: this the pointer to the new buffer.
 */
char *my_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];

	buf[k] = 0;
	return (buf);
}

/**
 * find_my_path - this finds the full path of a command in the PATH string.
 *
 * @info: This the info struct.
 * @pathstr: This the PATH string.
 * @cmd: This the command to find.
 *
 * Return: this the full path of cmd if found, or NULL.
 */
char *finding_my_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);

	if ((my_strlen(cmd) > 2) && where_starts_with(cmd, "./"))
	{
		if (is_my_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = my_dup_chars(pathstr, curr_pos, i);

			if (!*path)
				this_my_strcat(path, cmd);
			else
			{
				this_my_strcat(path, "/");
				this_my_strcat(path, cmd);
			}

			if (is_my_cmd(info, path))
				return (path);

			if (!pathstr[i])
				break;

			curr_pos = i;
		}
		i++;
	}

	return (NULL);
}

