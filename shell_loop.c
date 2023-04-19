#include "shell.h"

/**
 * hsh - main function for shell
 * @info: a pointer to the info_t struct
 * @av: double pointer to an array of arguments
 *
 * Return: the exit status of the shell
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);

		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);

		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}

		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * is_builtin - checks if the given command is a built-in
 * @cmd: the command to check
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int is_builtin(char *cmd)
{
    if (strcmp(cmd, "exit") == 0)
        return (1);
    if (strcmp(cmd, "env") == 0)
        return (1);
    if (strcmp(cmd, "help") == 0)
        return (1);
    if (strcmp(cmd, "history") == 0)
        return (1);
    if (strcmp(cmd, "setenv") == 0)
        return (1);
    if (strcmp(cmd, "unsetenv") == 0)
        return (1);
    if (strcmp(cmd, "cd") == 0)
        return (1);
    if (strcmp(cmd, "alias") == 0)
        return (1);
    return (0);
}

/**
 * run_builtin - runs the given built-in command
 * @cmd: the command to run
 * @info: a pointer to the info_t struct
 *
 * Return: the return value of the built-in command
 */
int run_builtin(char *cmd, info_t *info)
{
    int ret = 0;
    if (strcmp(cmd, "exit") == 0)
        ret = _myexit(info);
    else if (strcmp(cmd, "env") == 0)
        ret = _myenv(info);
    else if (strcmp(cmd, "help") == 0)
        ret = _myhelp(info);
    else if (strcmp(cmd, "history") == 0)
        ret = _myhistory(info);
    else if (strcmp(cmd, "setenv") == 0)
        ret = _mysetenv(info);
    else if (strcmp(cmd, "unsetenv") == 0)
        ret = _myunsetenv(info);
    else if (strcmp(cmd, "cd") == 0)
        ret = _mycd(info);
    else if (strcmp(cmd, "alias") == 0)
        ret = _myalias(info);
    return (ret);
}

/**
 * find_builtin - searches for a built-in command
 * @info: a pointer to the info_t struct
 *
 * Return: the exit status of the built-in command
 */
int find_builtin(info_t *info)
{
    if (is_builtin(info->argv[0]))
    {
        info->line_count++;
        return run_builtin(info->argv[0], info);
    }

    return (-1);
}

/**
 * find_cmd - finds a command in PATH.
 * @info: the parameter and return information.
 * Return: void return.
 */
void find_cmd(info_t *info)
{
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];

    if (info->linecount_flag == 1)
    {
        info->line_count++;
        info->linecount_flag = 0;
    }

    for (i = 0, k = 0; info->arg[i]; i++)
        if (!is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    if (path)
    {
        info->path = path;
        fork_cmd(info);
    }

    else
    {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/')
            && is_cmd(info, info->argv[0]))
            fork_cmd(info);

        else if (*(info->arg) != '\n')
        {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * fork_cmd - Forks a therad.
 * @info: the parameter and return information.
 * Return: void return
 */
void fork_cmd(info_t *info)
{
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1)
    {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");

        return;
    }

    if (child_pid == 0)
    {
        if (execve(info->path, info->argv, get_environ(info)) == -1)
        {
            free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    }
    else
    {
        wait(&(info->status));

        if (WIFEXITED(info->status))
        {
            info->status = WEXITSTATUS(info->status);

            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
