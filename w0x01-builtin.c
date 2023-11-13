#include "shell.h"

/**
 * _myexit - this is going to exit the shell
 * @info: this the Structure containing arguments.
 * Return: it returns with a given exit status
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			my_eputs(info->argv[1]);
			this_my_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd -  this is going to change the current directory
 * @info: this the struct containing potential arguments
 * Return: Always returns 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		this_my_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (this_my_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			this_my_puts(s);
			this_my_putchar('\n');
			return (1);
		}
		this_my_puts(_getenv(info, "OLDPWD=")), this_my_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		my_eputs(info->argv[1]), this_my_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - this is going to change the current directory of the process
 * @info: this the Structure containing potential arguments.
 * constant this the function prototype.
 * Return: Always returns 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	this_my_puts("help call works. Function not yet implemented \n");
	if (0)
		this_my_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

