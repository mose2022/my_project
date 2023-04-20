#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to memory area
 * @b: Constant byte
 * @n: Number of bytes to fill
 *
 * Return: Pointer to memory area
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}

/**
 * ffree - Frees array of chars.
 * @pp: Double pointer to array.
 *
 * Return: Nothing.
 */

void ffree(char **pp)
{
	char **e = pp;
	int i;

	if (!pp)
		return;
	for (i = 0; pp[i]; i++)
		free(pp[i]);
	free(e);
}

/**
 * _realloc - Reallocates a memory block
 * @ptr: Pointer to memory previously allocated with malloc()
 * @old_size: Size in bytes of allocated space for ptr
 * @new_size: Size in bytes of new memory block
 *
 * Return: Pointer to reallocated memory block, or NULL if allocation fails
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *a;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	a = malloc(new_size);
	if (!a)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	for (unsigned int i = 0; i < old_size; i++)
		a[i] = ((char *)ptr)[i];
	free(ptr);
	return (a);
}
