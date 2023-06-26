#include "main.h"

/**
 * _printf - print.
 * @yes: the yes
 *
 * Return: the number of chars
 */

int _printf(const char *yes, ...)
{
    unsigned int i, length = 0;
    va_list args;

    if (yes == NULL)
        return (-1);
    va_start(args, yes);
    for (i = 0; yes[i]; i++)
    {
        if (yes[i] != '%')
        {
            length += print_char(yes[i]);
            continue;
        }
        if (i++ == strlength(yes) - 1)
            return (-1);
        length += checker(yes[i], args);
    }
    va_end(args);
    return (length);
}