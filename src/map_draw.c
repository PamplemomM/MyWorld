/*
** EPITECH PROJECT, 2025
** map_draw.c
** File description:
** The file that will drzw the map.
*/
#include "../include/header.h"

static sfColor get_color_for_range(float height, sfVector2f minmax,
    sfColor low_color, sfColor high_color)
{
    float normalized = (height - minmax.x) / (minmax.y - minmax.x);
    unsigned char r;
    unsigned char g;
    unsigned char b;

    normalized = normalized < 0.0 ? 0.0 : normalized;
    normalized = normalized > 1.0 ? 1.0 : normalized;
    r = low_color.r + (high_color.r - low_color.r) * normalized;
    g = low_color.g + (high_color.g - low_color.g) * normalized;
    b = low_color.b + (high_color.b - low_color.b) * normalized;
    return sfColor_fromRGB(r, g, b);
}

sfColor get_terrain_color(float height)
{
    sfColor purple = sfColor_fromRGB(75, 0, 130);
    sfColor blue = sfColor_fromRGB(0, 0, 255);
    sfColor yellow = sfColor_fromRGB(255, 255, 0);
    sfColor light_gren = sfColor_fromRGB(144, 238, 144);
    sfColor green = sfColor_fromRGB(0, 128, 0);
    sfColor white = sfColor_fromRGB(255, 255, 255);
    float diff[] = {-25, -10, -5, 10, 25, 35, 45};
    sfColor colors[] = {purple, blue, yellow, light_gren, green, white, white};
    int i = 0;

    if (height <= -155 || height > 175)
        return sfBlack;
    while (i < 6 && height >= diff[i + 1])
        i++;
    return get_color_for_range(height, (sfVector2f){diff[i], diff[i + 1]},
        colors[i], colors[i + 1]);
}

static void add_cell_quad(sfVertexArray *grid, sfVector2f pos, sfVector2f size,
    sfColor color)
{
    sfVertex topLeft;
    sfVertex topRight;
    sfVertex bottomRight;
    sfVertex bottomLeft;

    topLeft.position = (sfVector2f){pos.x, pos.y};
    topRight.position = (sfVector2f){pos.x + size.x, pos.y};
    bottomRight.position = (sfVector2f){pos.x + size.x, pos.y + size.y};
    bottomLeft.position = (sfVector2f){pos.x, pos.y + size.y};
    topLeft.color = color;
    topRight.color = color;
    bottomRight.color = color;
    bottomLeft.color = color;
    sfVertexArray_append(grid, topLeft);
    sfVertexArray_append(grid, topRight);
    sfVertexArray_append(grid, bottomRight);
    sfVertexArray_append(grid, bottomLeft);
}

static sfVertexArray *build_terrain_grid(map_t *map, sfIntRect pos)
{
    sfVertexArray *grid = sfVertexArray_create();
    float cell_width = (float)pos.width / map->size.x;
    float cell_height = (float)pos.height / map->size.y;
    float height = 0;
    sfColor color = sfWhite;
    sfVector2f position = {0};
    sfVector2f size = {0};

    sfVertexArray_setPrimitiveType(grid, sfQuads);
    for (int y = 0; y < map->size.y; y++) {
        for (int x = 0; x < map->size.x; x++) {
            height = map->map[y][x];
            color = get_terrain_color(height);
            position = (sfVector2f){pos.left + x * cell_width,
                pos.top + y * cell_height};
            size = (sfVector2f){cell_width, cell_height};
            add_cell_quad(grid, position, size, color);
        }
    }
    return grid;
}

int draw_map(map_t *map, sfIntRect pos)
{
    sfVertexArray *grid = build_terrain_grid(map, pos);

    sfRenderWindow_drawVertexArray(WINDOW, grid, NULL);
    sfVertexArray_destroy(grid);
    return 0;
}
