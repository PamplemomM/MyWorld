/*
** EPITECH PROJECT, 2025
** map_gen_random.c
** File description:
** The file that generates the random map.
*/
#include "../include/header.h"

static float distance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    return sqrt(dx * dx + dy * dy);
}

static int generate_this_moutain(int height_value, sfVector2i m, float **map,
    int condition)
{
    float influence = 5;

    if (condition) {
        influence = height_value;
        map[m.x][m.y] += influence;
        map[m.x][m.y] = (map[m.x][m.y] > 1.0) ? 1.0 : map[m.x][m.y];
    }
    return SUCCESS;
}

static void generate_mountains(float **map, int width, int height)
{
    sfVector2i xy = {rand() % width, rand() % height};
    float height_value = diceroll(5, 10) / 10;
    float radius = diceroll(5, 15);
    float dist = 0.0;

    for (int mx = 0; mx < width; mx++) {
        for (int my = 0; my < height; my++) {
            dist = distance(mx, my, xy.x, xy.y);
            generate_this_moutain(height_value, (sfVector2i){mx, my}, map,
                (dist < radius));
        }
    }
}

static void add_noise(float **map, int width, int height)
{
    float noise = 0;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            noise = (diceroll(0, 10000) / 10000.0 * 0.1) - 0.05;
            map[i][j] += noise;
            map[i][j] = (map[i][j] < 0) ? 0 : 1;
        }
    }
}

int make_floor(float **map, int width, int height)
{
    make_flat(map, width, height);
    generate_mountains(map, width, height);
    add_noise(map, width, height);
    return SUCCESS;
}
