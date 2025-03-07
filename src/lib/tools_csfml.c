/*
** EPITECH PROJECT, 2024
** tools_csfml.c
** File description:
** The file for the csfml tools.
*/
#include "../../include/header.h"

void my_tween(float *nb, float endval, float intensity, int *condition)
{
    if (*condition == 0)
        return;
    if (*nb >= *condition - 0.5 && *nb <= *condition + 0.5)
        *condition = 0;
    *nb = endval - (endval - *nb) / intensity;
}

int change_texture_from_file(sprite_t *sprite, char *filepath)
{
    sfTexture_destroy(sprite->texture);
    sprite->texture = sfTexture_createFromFile(filepath, NULL);
    sfSprite_setTexture(sprite->sprite, sprite->texture, sfTrue);
    return SUCCESS;
}
