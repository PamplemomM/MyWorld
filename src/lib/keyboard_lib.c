/*
** EPITECH PROJECT, 2024
** keyboard_lib.c
** File description:
** The lib for the keyboard recuperation functions.
*/
#include "../../include/header.h"

static int add_to_keyb(name_t **list, char value, int *cpt)
{
    name_t *new = malloc(sizeof(name_t));

    if (new == NULL)
        return ERROR;
    new->letter = value;
    new->next = *list;
    *list = new;
    (*cpt)++;
    return SUCCESS;
}

int get_keyboard_input(sfKeyCode event, name_t **list, int limit)
{
    name_t *next;
    static int cpt = 0;

    if (event >= sfKeyA && event <= sfKeyZ && cpt < limit)
        add_to_keyb(list, 'a' + (event - sfKeyA), &cpt);
    if ((event == sfKeyDelete || event == sfKeyBackspace) && *list != NULL) {
        cpt--;
        next = (*list)->next;
        free(*list);
        *list = next;
    }
    if (event == sfKeySpace)
        add_to_keyb(list, ' ', &cpt);
    if (event >= sfKeyNum0 && event <= sfKeyNum9 && cpt < limit)
        add_to_keyb(list, '0' + (event - sfKeyNum0), &cpt);
    return SUCCESS;
}

char *my_keybrd_to_str(name_t *list)
{
    char *str;
    name_t *current = list;
    int i = 0;

    while (current != NULL) {
        i++;
        current = current->next;
    }
    str = malloc(sizeof(char) * (i + 1));
    if (str == NULL)
        return NULL;
    current = list;
    for (int j = 0; j < i; j++) {
        str[j] = current->letter;
        current = current->next;
    }
    str[i] = '\0';
    return my_revstr(str);
}
