/*
** EPITECH PROJECT, 2025
** isometrical_view.c
** File description:
** The file that will handle the isometrical view.
*/
#include "../include/header.h"

static float deg_to_rad(float degrees)
{
    return degrees * PI / 180.0;
}

static sfVector2f calculate_rotation_point(sfVector3f origin, float center_x,
    float center_y, sfVector2f angle)
{
    float rad_y = deg_to_rad(angle.y);
    sfVector2f rotated;

    rotated.x = (origin.x - center_x) * cos(rad_y) -
                (origin.y - center_y) * sin(rad_y) + center_x;
    rotated.y = (origin.x - center_x) * sin(rad_y) +
                (origin.y - center_y) * cos(rad_y) + center_y;
    return rotated;
}

static sfVector2f project_iso_point(sfVector3f origin, sfVector2f offset,
    sfVector2f angle)
{
    sfVector2f point_2d;
    sfVector2f rotated = calculate_rotation_point(origin, 200, 200, angle);

    point_2d.x = (rotated.x - rotated.y) * cos(deg_to_rad(30)) + offset.x;
    point_2d.y = (rotated.x + rotated.y) * sin(deg_to_rad(30)) -
        (origin.z * 5) + offset.y;
    return point_2d;
}

static sfVertex create_grid_vertex(map_t *map, sfVector3f origin,
    sfVector2f offset, sfVector2f angle)
{
    sfVertex vertex;

    if (origin.z < -155 || origin.z > 175)
        origin.z = 0;
    if (map->event_active == 1)
        vertex.position = project_iso_point((sfVector3f){origin.x * 675.0 /
            map->size.x, origin.y * 675.0 / map->size.x, origin.z},
            offset, angle);
    else
        vertex.position = project_iso_point((sfVector3f){origin.x * 255.0 /
            map->size.x, origin.y * 255.0 / map->size.x, origin.z},
            offset, angle);
    vertex.color = get_terrain_color(origin.z);
    return vertex;
}

static sfVector2f calculate_map_offset(sfIntRect pos, sfBool event_active)
{
    sfVector2f offset;

    if (event_active == 1) {
        offset.x = (pos.left + pos.width) / 2.0 + 250;
        offset.y = (pos.top + pos.height) / 2.0 - 250;
    }
    if (event_active == 0) {
        offset.x = (pos.left + pos.width) / 2.0;
        offset.y = (pos.top + pos.height) / 2.0 - 180;
    }
    if (event_active == -1) {
        offset.x = (pos.left + pos.width) / 2.0;
        offset.y = (pos.top + pos.height) / 2.0 - 120;
    }
    return offset;
}

static void add_horizontal_lines(map_t *map, sfVertexArray *iso_grid,
    sfVector2f offset, sfVector2f angle)
{
    sfVertex v1;
    sfVertex v2;

    for (int y = 0; y < map->size.y; y++) {
        for (int x = 0; x < map->size.x - 1; x++) {
            v1 = create_grid_vertex(map,
                (sfVector3f){x, y, map->map[y][x]}, offset, angle);
            v2 = create_grid_vertex(map,
                (sfVector3f){x + 1, y, map->map[y][x + 1]}, offset, angle);
            sfVertexArray_append(iso_grid, v1);
            sfVertexArray_append(iso_grid, v2);
        }
    }
}

static void add_vertical_lines(map_t *map, sfVertexArray *iso_grid,
    sfVector2f offset, sfVector2f angle)
{
    sfVertex v1;
    sfVertex v2;

    for (int x = 0; x < map->size.x; x++) {
        for (int y = 0; y < map->size.y - 1; y++) {
            v1 = create_grid_vertex(map,
                (sfVector3f){x, y, map->map[y][x]}, offset, angle);
            v2 = create_grid_vertex(map,
                (sfVector3f){x, y + 1, map->map[y + 1][x]}, offset, angle);
            sfVertexArray_append(iso_grid, v1);
            sfVertexArray_append(iso_grid, v2);
        }
    }
}

int map_to_isometrical(map_t *map, sfIntRect pos, sfEvent event,
    int event_active)
{
    static sfVector2f angle = {MAP_ANGLE_X, MAP_ANGLE_Y};
    sfVector2f offset = calculate_map_offset(pos, event_active);
    sfVertexArray *iso_grid = sfVertexArray_create();

    if (!sfRenderWindow_isOpen(WINDOW))
        return ERROR;
    map->event_active = event_active;
    if (event_active == 1) {
        handle_mouse_input(map, pos, offset, angle);
        analyse_mouse_events(event, &angle);
    }
    angle.y = (event_active == 1) ? angle.y : angle.y + 0.06;
    sfVertexArray_setPrimitiveType(iso_grid, sfLines);
    add_horizontal_lines(map, iso_grid, offset, angle);
    add_vertical_lines(map, iso_grid, offset, angle);
    sfRenderWindow_drawVertexArray(WINDOW, iso_grid, NULL);
    sfVertexArray_destroy(iso_grid);
    return SUCCESS;
}
