#include "shell.h"

/**
 * main - this is the entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: returns 0 on success, returns 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				my_eputs(av[0]);
				my_eputs(": 0: Can't open ");
				my_eputs(av[1]);
				this_my_eputchar('\n');
				this_my_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	my_hsh(info, av);
	return (EXIT_SUCCESS);
}

