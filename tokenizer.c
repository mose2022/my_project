#include "shell.h"

/**
 * **strtow - it splits a string into two.
 * @str: it is the input string.
 * @d: it is the delimeter string.
 *
 * Return: The pointer to an array of the string or NULL.
 */
char **strtow(char *str, char *d)
{
	int a, e, o, u, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);
	for (a = 0, e = 0; e < numwords; e++)
	{
		while (is_delim(str[a], d))
			a++;
		o = 0;

		while (!is_delim(str[a + o], d) && str[a + o])
			o++;
		s[e] = malloc((o + 1) * sizeof(char));
		if (!s[e])
		{
			for (o = 0; o < e; o++)
				free(s[o]);
			free(s);
			return (NULL);
		}

		for (u = 0; u < o; u++)
			s[e][u] = str[a++];
		s[e][u] = 0;
	}

	s[e] = NULL;
	return (s);
}

/**
 * **strtow2 - it splits the string.
 * @str: it is the input string.
 * @d: it is the delimeter.
 *
 * Return: the pointer to an array of the string.
 */
char **strtow2(char *str, char d)
{
	int a, e, o, u, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);
	for (a = 0, e = 0; e < numwords; e++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		o = 0;

		while (str[a + o] != d && str[a + o] && str[a + o] != d)
			o++;
		s[e] = malloc((o + 1) * sizeof(char));
		if (!s[e])
		{
			for (o = 0; o < e; o++)
				free(s[o]);
			free(s);
			return (NULL);
		}

		for (u = 0; u < o; u++)
			s[e][u] = str[a++];
		s[e][u] = 0;
	}

	s[e] = NULL;
	return (s);
}
