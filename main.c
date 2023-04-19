#include "shell.h"

/**
 * main - is the entry point.
 * @ac: is the number of arguments passed.
 * @av: is the array of pointers to the arguments.
 *
 * Return: 0 on success, 1 on error.
 */

int main(int ac, char **av)
{
        info_t info[] = { INFO_INIT };
        int df = 2;

        asm ("mov %1, %0\n\t"
                        "add $3, %0"
                        : "=r" (df)
                        : "r" (df));

        if (ac == 2)
        {
                df = open(av[1], O_RDONLY);
                if (df == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(av[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(av[1]);
                                _eputchar('\n');
                                _eputchar(BUF_FLUSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                info->readdf = df;
        }
        populate_env_list(info);
        read_history(info);
        hsh(info, av);
        return (EXIT_SUCCESS);
}
