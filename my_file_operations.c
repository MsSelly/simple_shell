#include "history.h"

/**
 * open_and_verify_file - this opens and verifies the given file.
 * @filename: This the name of the file to open.
 *
 * Return: this the file descriptor on success, -1 on failure.
 */
int open_and_verify_file(char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

/**
 * get_file_size - it get thesizeof the file associated with a file descriptor
 * @fd: This the file descriptor.
 *
 * Return: this the size of the file on success, -1 on failure.
 */
ssize_t get_file_size(int fd)
{
	struct stat st;

	if (fstat(fd, &st) == -1)
	{
		perror("Error getting file size");
		return (-1);
	}
	return (st.st_size);
}

/**
 * read_file_contents -  contents ofthefile into a dynamic allocated buffer
 * @fd: This the file descriptor.
 * @fsize: This the size of the file.
 *
 * Return: dynamic allocated buffer containing file contents on success, NULL
 */
char *read_file_contents(int fd, ssize_t fsize)
{
	char *buf = malloc(fsize + 1);
	ssize_t bytesRead;

	if (!buf)
	{
		perror("Error allocating memory");
		return (NULL);
	}

	bytesRead = read(fd, buf, fsize);
	if (bytesRead == -1)
	{
		perror("Error reading file contents");
		free(buf);
		return (NULL);
	}

	buf[fsize] = '\0'; /* Null-terminate the string */
	return (buf);
}

/**
 * process_file_contents - processes the content of the file build history list
 * @info: this the parameter struct.
 * @buf: this the Buffer containing the file contents.
 * @fsize: this the size of the file.
 */
void process_file_contents(info_t *info, char *buf, ssize_t fsize)
{
	int i, last = 0, linecount = 0;

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
	{
		build_history_list(info, buf + last, linecount++);
	}
}
