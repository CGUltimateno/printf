#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
/* Define STRING */
#define STRING ((str) ? str : "(null)")
/* Create the functions  */
int _printf(const char *format, ...);
int print_char(char c);
int print_string(char *s);
void print_number(int n);
int num_length(int n);
int checker(char c, va_list args);
int print_binary(unsigned int n);

#endif