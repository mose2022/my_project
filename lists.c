#include "shell.h"

/**
 * add_node - Adds a new node at the beginning of a list_t list
 * @head: Pointer to the head of the list
 * @str: String to be stored in the new node
 * @num: Integer to be stored in the new node
 *
 * Return: Address of the new node, or NULL if it fails
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newhead;

	if (!head)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = _strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *head;
	*head = newhead;
	return (newhead);
}

/**
 * add_node_end - Adds a new node at the end of a list_t list
 * @head: Pointer to the head of the list
 * @str: String to be stored in the new node
 * @num: Integer to be stored in the new node
 *
 * Return: Address of the new node, or NULL if it fails
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
        list_t *newnode, *node;

        if (!head)
                return (NULL);

        node = *head;
        newnode = malloc(sizeof(list_t));
        if (!newnode)
                return (NULL);
        _memset((void *)newnode, 0, sizeof(list_t));
        newnode->num = num;
        if (str)
        {
                newnode->str = _strdup(str);
                if (!newnode->str)
                {
                        free(newnode);
                        return (NULL);
                }
        }
        if (node)
        {
                for (; node->next != NULL; node = node->next)
                {
                }
                node->next = newnode;
        }
        else
                *head = newnode;
        return (newnode);
}

/**
 * print_list_str - Prints only the string e
 * @h: Pointer to the first node.
 *
 * Return: The size of list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at a given index.
 * @head: Address of pointer to the first node.
 * @index: index of node to be deleted.
 *
 * Return: 1 on Success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	prev_node = NULL;
	for (i = 0, node = *head; node; i++, prev_node = node, node = node->next)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
	}

	return (0);
}

/**
 * free_list - Frees all the nodes of a list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: Void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	for (node = head; node; node = next_node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
	}

	*head_ptr = NULL;
}
