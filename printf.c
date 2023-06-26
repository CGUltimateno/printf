#include "main.h"

/**
 * _printf - print.
 * @format: the format
 *
 * Return: the number of chars
 */

int _printf(const char *format, ...)
{
    unsigned int i, length = 0;
    va_list args;

    if (format == NULL)
        return (-1);
    va_start(args, format);
    for (i = 0; format[i]; i++)
    {
        if (format[i] != '%')
        {
            length += print_char(format[i]);
            continue;
        }
        if (i++ == strlength(format) - 1)
            return (-1);
        length += checker(format[i], args);
    }
    va_end(args);
    return (length);
}