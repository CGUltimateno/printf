#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * by Joseph and Ciny
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
    int x = *i + 1;
    int precision = -1;

    if (format[x] != '.')
        return (precision);

    precision = 0;

    for (x += 1; format[x] != '\0'; x++)
    {
        if (is_digit(format[x]))
        {
            precision *= 10;
            precision += format[x] - '0';
        }
        else if (format[x] == '*')
        {
            x++;
            precision = va_arg(list, int);
            break;
        }
        else
            break;
    }

    *i = x - 1;

    return (precision);
}