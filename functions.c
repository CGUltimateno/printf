#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @f:  Calculates active functions
 * @w: width
 * @p: precision specification
 * @s: size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
               int f, int w, int p, int s)
{
    char c = va_arg(types, int);

    return (handle_write_char(c, buffer, f, w, p, s));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @f:  Calculates active f
 * @w: get w.
 * @p: p specification
 * @s: s specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
                 int f, int w, int p, int s)
{
    int length = 0, i;
    char *str = va_arg(types, char *);

    UNUSED(buffer);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);
    if (str == NULL)
    {
        str = "(null)";
        if (p >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (p >= 0 && p < length)
        length = p;

    if (w > length)
    {
        if (f & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = w - length; i > 0; i--)
                write(1, " ", 1);
            return (w);
        }
        else
        {
            for (i = w - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (w);
        }
    }

    return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @f:  Calculates active f
 * @w: get w.
 * @p: p specification
 * @s: s specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
                  int f, int w, int p, int s)
{
    UNUSED(types);
    UNUSED(buffer);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);
    return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @f:  Calculates active f
 * @w: get w.
 * @p: p specification
 * @s: s specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
              int f, int w, int p, int s)
{
    int i = BUFF_s - 2;
    int is_negative = 0;
    long int n = va_arg(types, long int);
    unsigned long int num;

    n = convert_size_number(n, s);

    if (n == 0)
        buffer[i--] = '0';

    buffer[BUFF_s - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        is_negative = 1;
    }

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_number(is_negative, i, buffer, f, w, p, s));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @f:  Calculates active f
 * @w: get w.
 * @p: p specification
 * @s: s specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
                 int f, int w, int p, int s)
{
    unsigned int n, m, i, sum;
    unsigned int a[32];
    int count;

    UNUSED(buffer);
    UNUSED(f);
    UNUSED(w);
    UNUSED(p);
    UNUSED(s);

    n = va_arg(types, unsigned int);
    m = 2147483648; /* (2 ^ 31) */
    a[0] = n / m;
    for (i = 1; i < 32; i++)
    {
        m /= 2;
        a[i] = (n / m) % 2;
    }
    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];

            write(1, &z, 1);
            count++;
        }
    }
    return (count);
}
