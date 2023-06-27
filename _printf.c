#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: print chars.
 */
int _printf(const char *format, ...)
{
    int i, print = 0, print_c = 0;
    int f, w, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            /* write(1, &format[i], 1);*/
            print_c++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            f = get_f(format, &i);
            w = get_width(format, &i, list);
            precision = get_precision(format, &i, list);
            size = get_size(format, &i);
            ++i;
            print = handle_print(format, &i, list, buffer,
                                   f, w, precision, size);
            if (print == -1)
                return (-1);
            print_c += print;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(list);

    return (print_c);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind);

    *buff_ind = 0;
}
