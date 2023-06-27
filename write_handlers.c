#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
                      int f, int w, int p, int size)
{ /* char is stored at left and padding at buffer's right */
    int i = 0;
    char padding = ' ';

    UNUSED(p);
    UNUSED(size);

    if (f & F_ZERO)
        padding = '0';

    buffer[i++] = c;
    buffer[i] = '\0';

    if (w > 1)
    {
        buffer[BUFF_SIZE - 1] = '\0';
        for (i = 0; i < w - 1; i++)
            buffer[BUFF_SIZE - i - 2] = padding;

        if (f & F_MINUS)
            return (write(1, &buffer[0], 1) +
                    write(1, &buffer[BUFF_SIZE - i - 1], w - 1));
        else
            return (write(1, &buffer[BUFF_SIZE - i - 1], w - 1) +
                    write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @f:  Calculates active f
 * @w: get w.
 * @p: p specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
                 int f, int w, int p, int size)
{
    int length = BUFF_SIZE - ind - 1;
    char padding = ' ', extra_ch = 0;

    UNUSED(size);

    if ((f & F_ZERO) && !(f & F_MINUS))
        padding = '0';
    if (is_negative)
        extra_ch = '-';
    else if (f & F_PLUS)
        extra_ch = '+';
    else if (f & F_SPACE)
        extra_ch = ' ';

    return (write_num(ind, buffer, f, w, p,
                      length, padding, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @f: f
 * @w: w
 * @prec: p specifier
 * @length: Number length
 * @padding: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
              int f, int w, int prec,
              int length, char padding, char extra_c)
{
    int i, padding_start = 1;

    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && w == 0)
        return (0); /* printf(".0d", 0)  no char is printed */
    if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        buffer[ind] = padding = ' '; /* w is displayed with paddinging ' ' */
    if (prec > 0 && prec < length)
        padding = ' ';
    while (prec > length)
        buffer[--ind] = '0', length++;
    if (extra_c != 0)
        length++;
    if (w > length)
    {
        for (i = 1; i < w - length + 1; i++)
            buffer[i] = padding;
        buffer[i] = '\0';
        if (f & F_MINUS && padding == ' ')/* Asign extra char to left of buffer */
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        }
        else if (!(f & F_MINUS) && padding == ' ')/* extra char to left of buff */
        {
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        }
        else if (!(f & F_MINUS) && padding == '0')/* extra char to left of padding */
        {
            if (extra_c)
                buffer[--padding_start] = extra_c;
            return (write(1, &buffer[padding_start], i - padding_start) +
                    write(1, &buffer[ind], length - (1 - padding_start)));
        }
    }
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @f: f specifiers
 * @w: w specifier
 * @p: p specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
                 char buffer[],
                 int f, int w, int p, int size)
{
    /* The number is stored at the bufer's right and starts at position i */
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padding = ' ';

    UNUSED(is_negative);
    UNUSED(size);

    if (p == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
        return (0); /* printf(".0d", 0)  no char is printed */

    if (p > 0 && p < length)
        padding = ' ';

    while (p > length)
    {
        buffer[--ind] = '0';
        length++;
    }

    if ((f & F_ZERO) && !(f & F_MINUS))
        padding = '0';

    if (w > length)
    {
        for (i = 0; i < w - length; i++)
            buffer[i] = padding;

        buffer[i] = '\0';

        if (f & F_MINUS) /* Asign extra char to left of buffer [buffer>padding]*/
        {
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        }
        else /* Asign extra char to left of paddinging [padding>buffer]*/
        {
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @w: Ww specifier
 * @f: f specifier
 * @padding: Char representing the paddinging
 * @extra_c: Char representing extra char
 * @padding_start: Index at which paddinging should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
                  int w, int f, char padding, char extra_c, int padding_start)
{
    int i;

    if (w > length)
    {
        for (i = 3; i < w - length + 3; i++)
            buffer[i] = padding;
        buffer[i] = '\0';
        if (f & F_MINUS && padding == ' ')/* Asign extra char to left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        }
        else if (!(f & F_MINUS) && padding == ' ')/* extra char to left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
                buffer[--ind] = extra_c;
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        }
        else if (!(f & F_MINUS) && padding == '0')/* extra char to left of padding */
        {
            if (extra_c)
                buffer[--padding_start] = extra_c;
            buffer[1] = '0';
            buffer[2] = 'x';
            return (write(1, &buffer[padding_start], i - padding_start) +
                    write(1, &buffer[ind], length - (1 - padding_start) - 2));
        }
    }
    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c)
        buffer[--ind] = extra_c;
    return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}