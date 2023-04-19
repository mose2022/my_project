#include "shell.h"

/**
 * _strcpy - it copies the string.
 * @dest: it is the destination.
 * @src: it is the source.
 *
 * Return: the pointer to destination.
 */
char *_strcpy(char *dest, char *src)
{
    int i;

    if (dest == src || src == 0)
        return (dest);

    for (i = 0; *(src + i); i++)
        *(dest + i) = *(src + i);
    *(dest + i) = 0;

    return (dest);
}

/**
 * _strdup - it duplicates the string.
 * @str: it is the string to duplicate.
 *
 * Return: the pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;
    int i;

    if (str == NULL)
        return (NULL);

    for (i = 0; *(str + i) != '\0'; i++)
        length++;

    ret = malloc(sizeof(char) * (length + 1));

    if (!ret)
        return (NULL);

    for (i = 0; i <= length; i++)
        *(ret + i) = *(str + i);

    return (ret);
}

/**
 * _puts - it prints the input string.
 * @str: it is the string to be printed.
 *
 * Return: Nothing to return.
 */
void _puts(char *str)
{
    int i;

    if (!str)
        return;

    for (i = 0; *(str + i) != '\0'; i++)
        _putchar(*(str + i));
}

/**
 * _putchar - writes the character c to stdout.
 * @c: The character to print.
 *
 * Return: 1 on success, -1 on error.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
    {
        buf[i] = c;
        i++;
    }

    return (1);
}

