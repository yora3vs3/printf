#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;
    char *str;

    va_start(args, format);

    while (format && format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == '\0')
                return (-1); // Incomplete format specifier

            switch (format[i])
            {
                // Handle custom conversion specifiers
                case 'b':
                    count += printf_binary(va_arg(args, unsigned int));
                    break;

                case 'S':
                    str = va_arg(args, char *);
                    count += printf_custom_string(str);
                    break;

                case 'r':
                    str = va_arg(args, char *);
                    count += printf_reversed_string(str);
                    break;

                case 'R':
                    str = va_arg(args, char *);
                    count += printf_rot13_string(str);
                    break;

                // Handle other conversion specifiers
                case 'c':
                    count += printf_char(va_arg(args, int));
                    break;

                case 's':
                    str = va_arg(args, char *);
                    count += printf_string(str);
                    break;

                case '%':
                    count += printf("%%");
                    break;

                case 'd':
                case 'i':
                    count += printf_int(va_arg(args, int));
                    break;

                case 'u':
                    count += printf_unsigned(va_arg(args, unsigned int));
                    break;

                case 'o':
                    count += printf_octal(va_arg(args, unsigned int));
                    break;

                case 'x':
                    count += printf_hex(va_arg(args, unsigned int), 0);
                    break;

                case 'X':
                    count += printf_hex(va_arg(args, unsigned int), 1);
                    break;

                case 'p':
                    count += printf_pointer(va_arg(args, void *));
                    break;

                default:
                    printf("%%");
                    printf("%c", format[i]);
                    count += 2;
                    break;
            }
        }
        else
        {
            printf("%c", format[i]);
            count++;
        }
        i++;
    }

    va_end(args);

    return (count);
}

// Implement other printing functions as previously shown.

