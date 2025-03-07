/*
** EPITECH PROJECT, 2025
** map_gen.c
** File description:
** The file that generates the map.
*/
#include "../include/header.h"
#include <stdio.h>

map_t **get_map(void)
{
    static map_t *map = NULL;

    return &map;
}

float *map_to_int(float **map, int x, int y)
{
    float *final = malloc(sizeof(float) * x * y);

    if (final == NULL)
        return NULL;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            final[i * y + j] = map[i][j];
        }
    }
    return final;
}

void free_map(void)
{
    map_t *map = *get_map();
    int i = 0;

    if (map == NULL)
        return;
    if (map->name)
        free(map->name);
    if (map->map) {
        for (i = 0; i < map->size.x; i++) {
            free(map->map[i]);
        }
        free(map->map);
    }
    free(map);
}

static char *generate_name(void)
{
    char *first[] = {"Goofy_", "Beautiful_", "New_", "", "Best_",
        "Cartography_", "My_", NULL};
    char *last[] = {"Project", "Map", "Masterpiece", "Creation", "World",
        NULL};
    char *result = malloc(sizeof(char) * 2);

    result = my_sec_strcat(first[diceroll(0, 7) % 7],
        last[diceroll(0, 5) % 5]);
    return result;
}

int make_flat(float **map, int x, int y)
{
    for (int i = 0; i < x; i++) {
        map[i] = malloc(sizeof(float) * (y + 1));
        if (map[i] == NULL)
            return ERROR;
        for (int j = 0; j < y; j++)
            map[i][j] = 0.0;
        map[i][y] = -1.0;
    }
    map[x] = NULL;
    return SUCCESS;
}

int make_map(char *name, int x, int y, int flat)
{
    map_t *map = malloc(sizeof(map_t));
    float **intmap = malloc(sizeof(float *) * (x + 1));

    if (map == NULL || intmap == NULL)
        exit(ERROR);
    if (flat == 1)
        make_flat(intmap, x, y);
    else
        make_floor(intmap, x, y);
    free_map();
    if (name != NULL && name[0] != '\0')
        map->name = my_strdup(name);
    else
        map->name = generate_name();
    map->size = (sfVector2i){x, y};
    map->map = intmap;
    *get_map() = map;
    return SUCCESS;
}
