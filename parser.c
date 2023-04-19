#include "shell.h"

/**
 * is_cmd - Checks if a given file is executable.
 * @info: A pointer to the info_t struct.
 * @path: The path to check.
 *
 * Return: 1 if it is true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat str;

	(void)info;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - the duplicate characters.
 * @pathstr: the path of the string.
 * @start: the starting index of the substring
 * @stop: the stopping index of the substring.
 *
 * Return: the pointer to the duplicated substring.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int n = 0, m = 0;

	for (m = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			buf[m++] = pathstr[n];
	buf[m] = 0;

	return (buf);
}

/**
 * find_path - Finds cmd in the PATH.
 * @info: it is the info struct.
 * @pathstr: it is the PATH String.
 * @cmd: it is the cmd to find
 *
 * Return: if full path of cmd found, or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int m = 0, currpos = 0;
    char *path;

    if (!pathstr)
        return (NULL);

    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (is_cmd(info, cmd))
            return (cmd);
    }
    while (1)
    {
        if (!pathstr[m] || pathstr[m] == ':')
        {
            path = dup_chars(pathstr, currpos, m);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            if (is_cmd(info, path))
                return (path);

            if (!pathstr[m])
                break;

            currpos = m;
        }
        m++;
    }
    return (NULL);
}
