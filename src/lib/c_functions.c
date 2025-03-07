/*
** EPITECH PROJECT, 2024
** c_functions.c
** File description:
** The C functions.
*/
#include "../../include/header.h"
#include <stdarg.h>

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }
    return i;
}

char *my_strdup(char const *src)
{
    int i = 0;
    char *str;

    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (str == NULL)
        return NULL;
    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return str;
}

int my_putstr(char const *str)
{
    int i = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        write(1, &str[i], 1);
    }
    return i;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putstr("-");
        nb = nb * (-1);
    }
    if (nb == -2147483648) {
        my_putstr("2147483648");
    }
    if (nb <= 9 && nb >= 0) {
        my_putchar(nb + 48);
    } else if (nb > 9) {
        my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    }
}

static int condition_flag(const char *s, int i, va_list arg)
{
    if (s[i + 1] == 's') {
        my_putstr(va_arg(arg, char *));
    }
    if (s[i + 1] == 'd' || s[i + 1] == 'i') {
        my_put_nbr(va_arg(arg, int));
    }
    if (s[i + 1] == 'c') {
        my_putchar(va_arg(arg, int));
    }
    if (s[i + 1] == '%') {
        my_putchar('%');
    }
    return i;
}

int mini_printf(const char *format, ...)
{
    va_list arg;

    va_start(arg, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i = condition_flag(format, i, arg);
            i += 1;
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(arg);
    return 1;
}
