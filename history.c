#include "shell.h"

/**
 * get_history_file - Returns the path to the history file
 * @info: Pointer to info_t struct
 *
 * Return: Pointer to the path of the history file, or NULL on failure
 */
char *get_history_file(info_t *info)
{
	char *buff, *dirr;

	dirr = _getenv(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - Writes command history to file.
 * @info: Pointer to parameter struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *info)
{
	ssize_t df;
	char *file = get_history_file(info);
	list_t *node = NULL;

	if (!file)
		return (-1);

	df = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (df == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, df);
		_putfd('\n', df);
	}
	_putfd(BUF_FLUSH, df);

	close(df);
	return (1);
}

/**
 * read_history - Reads command history from file
 * @info: Pointer to info_t struct
 *
 * Return: Number of lines read on success, 0 on failure
 */
int read_history(info_t *info)
{
	int j = 0, last = 0, linecount = 0;
	ssize_t df, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *file = get_history_file(info);

	if (!file)
		return (0);

	df = open(file, O_RDONLY);
	free(file);
	if (df == -1)
		return (0);

	if (!fstat(df, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return (0);

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);

	rdlen = read(df, buf, fsize);
	buf[fsize] = '\0';
	if (rdlen <= 0)
		return (free(buf), 0);

	close(df);

	while (buf[j] != '\0')
	{
		if (buf[j] == '\n')
		{
			buf[j] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
		j++;
	}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);

	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - Adds entry to the history list.
 * @info: The Structure containing arguments.
 * @buf: The buffer.
 * @linecount: The history linecount.
 *
 * Return: Always 0
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
 * renumber_history - Renumbers the history linked list.
 * @info: The pointer to info struct.
 *
 * Return: The number of items in the history list.
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i;

	for (i = 0; node; node = node->next, i++)
		node->num = i;

	return (info->histcount = i);
}
