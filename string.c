#include "shell.h"

/**
 * _strlen - returns length of the string.
 * @s: string whose length is to be checked.
 *
 * Return: length of the string as an interger.
 */

int _strlen(char *s)
{
        int i = 0;

        if (!s)
                return (0);

        while (*s++)
                i++;

        return (i);
}

/**
 * _strcmp - Compares two strings
 * @s1: The first string to be compared
 * @s2: The second string to be compared
 *
 * Return: An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2
 */
int _strcmp(char *s1, char *s2)
{
        while (*s1 && *s2)
        {
                if (*s1 != *s2)
                        return (*s1 - *s2);
                s1++;
                s2++;
        }

        if (*s1 == *s2)
                return (0);
        else
                return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - it checks if the needle starts with the haystack.
 * @haystack: The string to search.
 * @needle: The substring to find.
 *
 * Return: The address of next char or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
    for (; *needle; needle++, haystack++) {
        if (*needle != *haystack) {
            return (NULL);
        }
    }
    return ((char *) haystack);
}

/**
 * _strcat - It concatenates two strings.
 * @dest: It is the destination buffer.
 * @src: It is the source buffer.
 *
 * Return: The pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
    char *ret = dest;
    int i;

    for (i = 0; *(dest + i); i++)
        ;
    for (; *(src); i++)
        *(dest + i) = *(src++);
    *(dest + i) = *src;
    return (ret);
}
