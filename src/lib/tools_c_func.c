/*
** EPITECH PROJECT, 2024
** tools_c_func.c
** File description:
** The file for the tools functions.
*/
#include "../../include/header.h"

char *my_sec_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    char *res = malloc(sizeof(char) * (len_dest + len_src + 1));

    if (res == NULL)
        return NULL;
    for (int i = 0; i < len_dest; i++) {
        res[i] = dest[i];
    }
    for (int i = 0; i < len_src; i++) {
        res[len_dest + i] = src[i];
    }
    res[len_dest + len_src] = '\0';
    return res;
}

char *my_revstr(char *str)
{
    int len = 0;
    char temp;

    while (str[len] != '\0')
        len++;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}

char *my_its(int nbr)
{
    char *result = malloc(sizeof(char) * 12);

    if (!result)
        return NULL;
    sprintf(result, "%d", nbr);
    return result;
}

int my_getnbr(char *str)
{
    int res = 0;
    int i = 0;

    while (str[i] && (str[i] < '0' || str[i] > '9'))
        i++;
    while (str[i] >= '0' && str[i] <= '9') {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

int setsprite_rect(sprite_t *sprite, sfIntRect new)
{
    sprite->rect = new;
    sfSprite_setTextureRect(sprite->sprite, new);
    return SUCCESS;
}
