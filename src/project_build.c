/*
** EPITECH PROJECT, 2025
** project_build.c
** File description:
** The file that handle the program build.
*/
#include "../include/header.h"

static int init_sprite(sprite_t *cur, sfIntRect r, int type)
{
    cur->type = type;
    setsprite_rect(cur, r);
    sfSprite_setOrigin(cur->sprite, (sfVector2f){r.width / 2, r.height / 2});
    sfSprite_move(cur->sprite, (sfVector2f){r.width / 2, r.height / 2});
    return SUCCESS;
}

int init_project_2(void)
{
    sprite_t *current = find_sprite("SizePanel");

    sprite_create("Nuke", "img/nuke.png", (sfVector2f){290, 546});
    init_sprite(find_sprite("Nuke"), (sfIntRect){0, 0, 90, 90}, 1);
    setsprite_rect(current, (sfIntRect){188, 0, 188, 321});
    sfSprite_setOrigin(current->sprite, (sfVector2f){94, 160});
    sfSprite_setScale(current->sprite, (sfVector2f){0.25, 0.35});
    sprite_create("Bg", "img/Usagedark.png", (sfVector2f){0});
    create_text("Size", (sfVector2f){325, 760}, 2, "font/Consolas.ttf");
    sfText_setString(find_text("Size")->text, "5");
    find_text("Size")->hide = 5;
    create_text("AutoSave", (sfVector2f){10, 12}, 1.8, "font/Consolas.ttf");
    sfText_setString(find_text("AutoSave")->text, "Auto-Saving...");
    find_text("AutoSave")->hide = 1;
    return SUCCESS;
}

// pos * 0.947916667
int init_project_sprites(void)
{
    sprite_create("Cursor", "img/cursor.png", (sfVector2f){0, 0});
    sprite_create("File", "img/file.png", (sfVector2f){1579.8, 970});
    init_sprite(find_sprite("File"), (sfIntRect){0, 0, 93, 47}, 1);
    sprite_create("RaiseBut", "img/button_raise.png", (sfVector2f){55, 546});
    init_sprite(find_sprite("RaiseBut"), (sfIntRect){0, 0, 90, 90}, 1);
    sprite_create("CursorBut", "img/button_curs.png", (sfVector2f){172, 546});
    init_sprite(find_sprite("CursorBut"), (sfIntRect){0, 0, 90, 90}, 1);
    sprite_create("Theme", "img/theme.png", (sfVector2f){1305.2, 970});
    init_sprite(find_sprite("Theme"), (sfIntRect){0, 0, 93, 47}, 1);
    sprite_create("Close", "img/close.png", (sfVector2f){1717.6, 970});
    init_sprite(find_sprite("Close"), (sfIntRect){0, 0, 93, 47}, 1);
    sprite_create("SizePanel", "img/menu/panels.png", (sfVector2f){45, 800});
    init_project_2();
    return SUCCESS;
}
