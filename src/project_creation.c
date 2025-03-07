/*
** EPITECH PROJECT, 2025
** project_creation.c
** File description:
** The file that will handle the creation of a project
*/
#include "../include/header.h"

static int init_creation_sprites(void)
{
    sprite_t *current = NULL;

    sprite_create("SizePanel", "img/menu/panels.png", (sfVector2f){105, 583});
    current = find_sprite("SizePanel");
    setsprite_rect(current, (sfIntRect){0, 0, 188, 321});
    sfSprite_setOrigin(current->sprite, (sfVector2f){94, 160});
    sfSprite_setScale(current->sprite, (sfVector2f){0.25, 0.35});
    sprite_create("NewProject", "img/menu/nwprj.png", (sfVector2f){183, 0});
    current = find_sprite("NewProject");
    setsprite_rect(current, (sfIntRect){0, 0, 315, 167});
    sfSprite_setScale(current->sprite, (sfVector2f){1, 1});
    sprite_create("Flat", "img/menu/onoffb.png", (sfVector2f){859, 424});
    setsprite_rect(find_sprite("Flat"), (sfIntRect){0, 88, 88, 88});
    sprite_create("Background", "img/menu/creation_menu.png", (sfVector2f){0});
    create_text("Size", (sfVector2f){905, 563}, 1, "font/Lucidity-Expand.ttf");
    create_text("Name", (sfVector2f){105, 382}, 1, "font/Consolas.ttf");
    sfText_setString(find_text("Size")->text, "10");
    sfText_setString(find_text("Name")->text, "Type project name");
    make_map("map", 20, 20, 0);
    return SUCCESS;
}

static int analyse_sizebutton(sfEvent event)
{
    sprite_t *size = find_sprite("SizePanel");
    sfFloatRect sizepos = sfSprite_getGlobalBounds(size->sprite);

    if (event.type == sfEvtMouseButtonPressed) {
        if (sfFloatRect_contains(&sizepos,
            event.mouseButton.x, event.mouseButton.y) ||
            event.mouseButton.y >= 540 && event.mouseButton.y < 635) {
            size->other = 1;
            sfSprite_setScale(size->sprite, (sfVector2f){0.30, 0.40});
        }
    }
    if (event.type == sfEvtMouseButtonReleased) {
        size->other = 0;
        sfSprite_setScale(size->sprite, (sfVector2f){0.25, 0.35});
    }
    return SUCCESS;
}

static void analyse_pressed_name(sfEvent event)
{
    text_t *text = find_text("Name");
    sprite_t *flat = find_sprite("Flat");

    if (event.mouseButton.x >= 74 && event.mouseButton.x < 530 &&
        event.mouseButton.y >= 357 && event.mouseButton.y <= 450) {
        text->other = 1;
        sfText_setString(text->text, my_keybrd_to_str(text->string));
    } else {
        text->other = 0;
        if (text->string == NULL)
            sfText_setString(text->text, "Type project name");
    }
    if (event.mouseButton.x >= 859 && event.mouseButton.x < 947 &&
        event.mouseButton.y >= 424 && event.mouseButton.y <= 512) {
        setsprite_rect(flat, (sfIntRect){0, ((flat->other == 1) ? 88 : 0),
            88, 88});
        flat->other = (flat->other == 0) ? 1 : 0;
        make_map("map", (find_sprite("SizePanel")->pos.x / 4),
            (find_sprite("SizePanel")->pos.x / 4), flat->other);
    }
}

static int check_start_button(sfEvent event)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(WINDOW);
    sprite_t *new = find_sprite("NewProject");

    if (pos.y >= 0 && pos.y <= 172 && pos.x >= 183 && pos.x <= 498) {
        if (event.type == sfEvtMouseButtonPressed)
            new->other = 1;
        setsprite_rect(new, (sfIntRect){0, 168, 315, 167});
    } else {
        setsprite_rect(new, (sfIntRect){0, 0, 315, 167});
    }
    if (event.type == sfEvtMouseMoved && find_sprite("SizePanel")->other == 1)
        make_map(my_keybrd_to_str(find_text("Name")->string),
        (find_sprite("SizePanel")->pos.x / 4),
        (find_sprite("SizePanel")->pos.x / 4), find_sprite("Flat")->other);
    return SUCCESS;
}

static int analyse_events_creation(sfEvent event)
{
    text_t *text = find_text("Name");

    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed)
            end_it_all(SUCCESS);
        if (event.type == sfEvtMouseMoved || event.type
        == sfEvtMouseButtonPressed || event.type == sfEvtMouseButtonReleased)
            analyse_sizebutton(event);
        if (event.type == sfEvtMouseButtonPressed)
            analyse_pressed_name(event);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEnter)
            find_sprite("NewProject")->other = 1;
        if (text->other == 1 && event.type == sfEvtKeyPressed) {
            get_keyboard_input(event.key.code, &(text->string), 17);
            sfText_setString(text->text, my_keybrd_to_str(text->string));
        }
        check_start_button(event);
    }
    return SUCCESS;
}

static int update_sprites(void)
{
    sprite_t *size = find_sprite("SizePanel");
    sfVector2i pos = sfMouse_getPositionRenderWindow(WINDOW);
    text_t *text = *all_texts();

    draw_sprites_in_order();
    while (text != NULL) {
        if (text->hide != 1)
            sfRenderWindow_drawText(WINDOW, text->text, NULL);
        text = text->next;
    }
    if (size->other == 0)
        return SUCCESS;
    pos.x = (pos.x < 105) ? 105 : pos.x;
    pos.x = (pos.x > 755) ? 755 : pos.x;
    size->pos = (sfVector2f){pos.x, size->pos.y};
    sfSprite_setPosition(size->sprite, size->pos);
    sfText_setString(find_text("Size")->text, my_its(pos.x / 10));
    return SUCCESS;
}

int create_project(void)
{
    sfEvent event;

    init_creation_sprites();
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, (sfColor){106, 126, 152, 155});
        update_sprites();
        analyse_events_creation(event);
        map_to_isometrical(*get_map(), (sfIntRect){594, 7, 1070, 402}, event,
            sfFalse);
        if (find_sprite("NewProject")->other == 1)
            break;
        sfRenderWindow_display(WINDOW);
    }
    make_map(my_keybrd_to_str(find_text("Name")->string),
        (find_sprite("SizePanel")->pos.x / 4),
        (find_sprite("SizePanel")->pos.x / 4), find_sprite("Flat")->other);
    save_map((*get_map())->name);
    destroy_window();
    reset_all_sprites(get_sprites());
    return SUCCESS;
}
