#include "shell.h"

/**
 * list_len - It determines length of linked list.
 * @h: Pointer to the first node.
 *
 * Return: The size of list.
 */
size_t list_len(const list_t *h)
{
	size_t i;
	
	for (i = 0; h; i++)
		h = h->next;
	
	return (i);
}

/**
 * list_to_strings - Returns an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: An array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t m = list_len(head), n;
	char **strs;
	char *str;

	if (!head || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	m = 0;
	while (node)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < m; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[m] = str;
		node = node->next;
		m++;
	}
	strs[m] = NULL;
	return (strs);
}

/**
 * print_list - Prints all elements of the list.
 * @h: Pointer to the first node.
 *
 * Return: The size of the list.
 */
size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h; h = h->next, i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}

	return (i);
}

/**
 * node_starts_with - Returns the node whose string starts with prefix.
 * @node: The pointer to the head.
 * @prefix: The string to match.
 * @c: The character after prefix.
 *
 * Return: The match node or NULL.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *a = NULL;

    for (; node; node = node->next)
    {
        a = starts_with(node->str, prefix);
        if (a && ((c == -1) || (*a == c)))
            return (node);
    }
    return (NULL);
}

/**
 * get_node_index - It gets the index of the node.
 * @head: The pointer to the list.
 * @node: The pointer to the node.
 *
 * Return: The index of the node, or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j;

	for (j = 0; head; head = head->next, j++)
	{
		if (head == node)
			return (j);
	}
	return (-1);
}

