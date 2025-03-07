/*
** EPITECH PROJECT, 2025
** isometrical_view.c
** File description:
** The file that will handle the isometrical view.
*/
#include "../include/header.h"

static void analyse_sizebutton(sfEvent event, sprite_t *size)
{
    sfFloatRect sizepos = sfSprite_getGlobalBounds(size->sprite);
    sfVector2i pos = sfMouse_getPositionRenderWindow(WINDOW);

    if (event.type == sfEvtMouseButtonPressed) {
        if (sfFloatRect_contains(&sizepos, pos.x, pos.y) ||
            pos.y >= 753 && pos.y < 852 && pos.x >= 19 && pos.x < 280) {
            size->other = 1;
            sfSprite_setScale(size->sprite, (sfVector2f){0.30, 0.40});
        }
    }
    size->other = (event.type == sfEvtMouseButtonReleased) ? 0 : size->other;
    if (event.type == sfEvtMouseButtonReleased)
        sfSprite_setScale(size->sprite, (sfVector2f){0.25, 0.35});
    if (size->other == 0)
        return;
    pos.x = (pos.x < 19) ? 19 : pos.x;
    pos.x = (pos.x > 280) ? 280 : pos.x;
    sfSprite_setPosition(size->sprite, (sfVector2f){pos.x, size->pos.y});
    sfText_setString(find_text("Size")->text, my_its((int)(pos.x / 15)));
    find_text("Size")->hide = (int)(pos.x / 15);
}

static void get_tile(int map_width, int map_height, int size,
    sfVector2f *tile)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(WINDOW);
    float tile_width = (float)map_width / size;
    float tile_height = (float)map_height / size;
    int adjusted_x = mouse_pos.x - 400;
    int adjusted_y = mouse_pos.y;

    tile->x = (int)floor((float)adjusted_x / tile_width);
    tile->y = (int)floor((float)adjusted_y / tile_height);
}

int handle_mouse_input(map_t *map, sfIntRect pos, sfVector2f offset,
    sfVector2f angle)
{
    sfVector2f tile;

    get_tile(400, 400, map->size.x, &tile);
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        raise((*get_map()), (sfVector2f){tile.x, tile.y}, 0.4,
            find_text("Size")->hide);
    }
    if (sfMouse_isButtonPressed(sfMouseRight)) {
        drop((*get_map()), (sfVector2f){tile.x, tile.y}, 0.4,
        find_text("Size")->hide);
    }
    return SUCCESS;
}

static int key_pressed(int *moved, int *obj, sfEvent event, sfVector2f *angle)
{
    analyse_sizebutton(event, find_sprite("SizePanel"));
    if (event.type == sfEvtKeyPressed) {
        if (event.key.code == sfKeyLeft) {
            *moved = 1;
            *obj = angle->y - 16;
        }
        if (event.key.code == sfKeyRight) {
            *moved = 1;
            *obj = angle->y + 16;
        }
    }
    return SUCCESS;
}

int analyse_mouse_events(sfEvent event, sfVector2f *angle)
{
    static int reset = 0;
    static int moved = 0;
    static int obj = 0;

    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(WINDOW);
            end_it_all(SUCCESS);
        }
        key_pressed(&moved, &obj, event, angle);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace)
            reset = 1;
    }
    if (find_sprite("Nuke") != NULL && find_sprite("Nuke")->other == 1) {
        reset_map(*get_map());
        find_sprite("Nuke")->other = 0;
    }
    my_tween(&angle->y, 2, 1.1, &reset);
    my_tween(&angle->y, obj, 1.1, &moved);
    return SUCCESS;
}
