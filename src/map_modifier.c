/*
** EPITECH PROJECT, 2025
** map_modifier.c
** File description:
** The file that will modify the map.
*/
#include "../include/header.h"

static int drop_loop(sfVector2i ij, sfVector2i xy, float intensite, int size)
{
    map_t *map = *get_map();
    float value = 0;

    if (xy.x >= 0 && xy.y >= 0 && xy.x < map->size.x && xy.y < map->size.y) {
        value = 1.0 - ((abs(ij.x) + abs(ij.y)) / (2.0 * size));
        if (value > 0)
            map->map[xy.x][xy.y] -= intensite * value;
    }
    return SUCCESS;
}

int drop(map_t *map, sfVector2f pos, float intensite, int size)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= map->size.x || pos.y >= map->size.y)
        return ERROR;
    if (map->map[(int)pos.x][(int)pos.y] <= -30)
        return ERROR;
    for (int i = size * (-1); i <= size; i++) {
        for (int j = size * (-1); j <= size; j++) {
            drop_loop((sfVector2i){i, j}, (sfVector2i){pos.x + i, pos.y + j},
                intensite, size);
        }
    }
    return SUCCESS;
}

static int raise_loop(sfVector2i ij, sfVector2i xy, float intensite, int size)
{
    map_t *map = *get_map();
    float value = 0;

    if (xy.x >= 0 && xy.y >= 0 && xy.x < map->size.x && xy.y < map->size.y) {
        value = 1.0 - ((abs(ij.x) + abs(ij.y)) / (2.0 * size));
        if (value > 0)
            map->map[xy.x][xy.y] += intensite * value;
    }
    return SUCCESS;
}

int raise(map_t *map, sfVector2f pos, float intensite, int size)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= map->size.x || pos.y >= map->size.y)
        return ERROR;
    if (map->map[(int)pos.x][(int)pos.y] >= 50)
        return ERROR;
    for (int i = size * (-1); i <= size; i++) {
        for (int j = size * (-1); j <= size; j++) {
            raise_loop((sfVector2i){i, j}, (sfVector2i){pos.x + i, pos.y + j},
                intensite, size);
        }
    }
    return SUCCESS;
}

void reset_map(map_t *map)
{
    for (int y = 0; y < map->size.y; y++) {
        for (int x = 0; x < map->size.x; x++) {
            map->map[y][x] = 0.0;
        }
    }
}
