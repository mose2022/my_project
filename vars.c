#include "shell.h"

/**
 * is_chain - it tests if the current char is in buffer.
 * @info: it is the parameter struct.
 * @buf: the char buffer
 * @p: the address of curent position in buf in the code.
 *
 * Return: 1 if there is a chain delimeter, and 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j;
	for (j = *p; buf[j] != '\0'; j++)
	{
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
			break;
		}
		else
			return (0);
	}

	*p = j;
	return (1);
}

/**
 * check_chain - it checks chaining based on last statue.
 * @info: it is the parameter struct.
 * @buf: it is the char buffer.
 * @p: it is the address of current position in buf.
 * @i: it is the starting position in buf.
 * @len: it is the length of buf.
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	for (; j < len; j++)
	{
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
	}
	*p = j;
}


/**
 * replace_alias - it replaces an alases.
 * @info: the parameter struct.
 *
 * Return: 1 if it is replaced, and 0 otherwise.
 */
int replace_alias(info_t *info)
{
    int i = 0;
    list_t *node;
    char *p;

    while (i < 10)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);

        free(info->argv[0]);
        p = _strchr(node->str, '=');

        if (!p)
            return (0);
        p = _strdup(p + 1);

        if (!p)
            return (0);
        info->argv[0] = p;
        i++;
    }

    return (1);
}

/**
 * replace_vars - it replaces vars in the string.
 * @info: it is the parameter struct.
 *
 * Return: 1 if it is replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    while (info->argv[i])
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
        {
            i++;
            continue;
        }

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                    _strdup(convert_number(info->status, 10, 0)));
            i++;
            continue;
        }

        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                    _strdup(convert_number(getpid(), 10, 0)));
            i++;
            continue;
        }

        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                    _strdup(_strchr(node->str, '=') + 1));
            i++;
            continue;
        }

        replace_string(&info->argv[i], _strdup(""));
        i++;
    }

    return (0);
}

/**
 * replace_string - it replaces string.
 * @old: it is the address of old string.
 * @new: it is the new string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}
