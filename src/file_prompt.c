/*
** EPITECH PROJECT, 2025
** file_prompt.c
** File description:
** The file that will handle the start of the project (create/ load a project)
*/
#include "../include/header.h"

static int init_menusprites(void)
{
    sprite_t *current = NULL;

    sprite_create("CreateMap", "img/menu/newPrj.png", (sfVector2f){75, 200});
    current = find_sprite("CreateMap");
    setsprite_rect(current, (sfIntRect){0, 0, 440, 283});
    sprite_create("LoadMap", "img/menu/loadPrj.png", (sfVector2f){555, 200});
    current = find_sprite("LoadMap");
    setsprite_rect(current, (sfIntRect){0, 0, 440, 284});
    return SUCCESS;
}

static int startpress(sfMouseButtonEvent mousepos, sprite_t *c, sprite_t *l)
{
    sfFloatRect createpos = sfSprite_getGlobalBounds(c->sprite);
    sfFloatRect loadpos = sfSprite_getGlobalBounds(l->sprite);

    if (sfFloatRect_contains(&createpos, mousepos.x, mousepos.y)) {
        c->other = 1;
        return 1;
    } else if (sfFloatRect_contains(&loadpos, mousepos.x, mousepos.y)) {
        l->other = 1;
        return 1;
    }
    return SUCCESS;
}

static int startmove(sfVector2i mousepos, sprite_t *c, sprite_t *l)
{
    sfFloatRect createpos = sfSprite_getGlobalBounds(c->sprite);
    sfFloatRect loadpos = sfSprite_getGlobalBounds(l->sprite);

    if (sfFloatRect_contains(&createpos, mousepos.x, mousepos.y))
        setsprite_rect(c, (sfIntRect){c->rect.left, 284, c->rect.width,
            c->rect.height});
    else
        setsprite_rect(c, (sfIntRect){c->rect.left, 0, c->rect.width,
            c->rect.height});
    if (sfFloatRect_contains(&loadpos, mousepos.x, mousepos.y))
        setsprite_rect(l, (sfIntRect){l->rect.left, 284, l->rect.width,
            l->rect.height});
    else
        setsprite_rect(l, (sfIntRect){l->rect.left, 0, l->rect.width,
            l->rect.height});
    return SUCCESS;
}

static int analyse_events_start(sfEvent event)
{
    sprite_t *c;
    sprite_t *l;

    draw_sprites_in_order();
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(WINDOW);
            end_it_all(SUCCESS);
        }
        c = find_sprite("CreateMap");
        l = find_sprite("LoadMap");
        if (event.type == sfEvtMouseMoved) {
            return startmove(sfMouse_getPositionRenderWindow(WINDOW), c, l);
        }
        if (event.type == sfEvtMouseButtonPressed) {
            return startpress(event.mouseButton, c, l);
        }
    }
    return SUCCESS;
}

int launch_fileprompt(void)
{
    sfEvent event;
    int result = 0;

    init_window("MyWorld Setup", 1080, 720);
    init_menusprites();
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, (sfColor){106, 126, 152, 155});
        if (analyse_events_start(event) == 1)
            break;
        sfRenderWindow_display(WINDOW);
    }
    if (find_sprite("LoadMap")->other == 1) {
        sfRenderWindow_setTitle(WINDOW, "MyWorld Load");
        result = 1;
    } else {
        sfRenderWindow_setTitle(WINDOW, "MyWorld Creation");
    }
    reset_all_sprites(get_sprites());
    return result;
}
