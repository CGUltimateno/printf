#include "main.h"

/**
 * get_w - Calculates the w for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: w.
 */
int get_width(const char *format, int *i, va_list list)
{
    int x;
    int w = 0;

    for (x = *i + 1; format[x] != '\0'; x++)
    {
        if (is_digit(format[x]))
        {
            w *= 10;
            w += format[x] - '0';
        }
        else if (format[x] == '*')
        {
            x++;
            w = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *i = x - 1;

    return (w);
}
