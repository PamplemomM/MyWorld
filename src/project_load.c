/*
** EPITECH PROJECT, 2025
** project_load.c
** File description:
** The file that will handle the load of a project
*/
#include "../include/header.h"
#include <dirent.h>

static int dirctory_len(char *directory)
{
    DIR *dirp;
    struct dirent *dp;
    int size = 0;

    dirp = opendir(directory);
    if (dirp == NULL)
        return ERROR;
    dp = readdir(dirp);
    while (dp != NULL) {
        if (dp->d_name[0] != '.')
            size++;
        dp = readdir(dirp);
    }
    closedir(dirp);
    return size;
}

char **open_directory(char *directory)
{
    char **str = malloc(sizeof(char *) * (dirctory_len(directory) + 1));
    DIR *dirp;
    struct dirent *dp;
    int i = 0;

    dirp = opendir(directory);
    if (dirp == NULL)
        return NULL;
    dp = readdir(dirp);
    while (dp != NULL) {
        if (dp->d_name[0] != '.') {
            str[i] = my_strdup(dp->d_name);
            str[i][my_strlen(str[i]) - 7] = '\0';
            i++;
        }
        dp = readdir(dirp);
    }
    str[i] = NULL;
    closedir(dirp);
    return str;
}

static int init_loading_sprites(void)
{
    text_t *text;
    char **str = open_directory("target");
    int i = 0;

    sprite_create("UpArrw", "img/menu/Arrow.png", (sfVector2f){805, 436});
    sprite_create("DownArrow", "img/menu/Arrow.png", (sfVector2f){865, 689});
    sfSprite_setRotation(find_sprite("DownArrow")->sprite, 180);
    sprite_create("Selected", "img/menu/ldselec.png", (sfVector2f){253, 430});
    sprite_create("Background", "img/menu/load_menu.png", (sfVector2f){0});
    while (str[i] != NULL) {
        create_text(str[i], (sfVector2f){265, 452 + i * 80}, 1,
            "font/Lucidity-Expand.ttf");
        text = find_text(str[i]);
        sfText_setScale(text->text, (sfVector2f){0.70, 0.70});
        text->other = 5;
        i++;
    }
    find_sprite("Selected")->delay = i;
    free_word_array(str);
    return SUCCESS;
}

static int change_up(void)
{
    text_t *texts = *all_texts();
    sprite_t *selec = find_sprite("Selected");

    if ((int)selec->dest.y - 1 < 0)
        return SUCCESS;
    if (selec->other <= 0) {
        while (texts != NULL) {
            texts->pos.y += 81;
            texts->hide = (texts->pos.y < 430 || texts->pos.y > 700) ? 1 : 0;
            sfText_setPosition(texts->text, texts->pos);
            texts = texts->next;
        }
    }
    selec->dest.y--;
    if (selec->other > 0 && selec->dest.y + 1 > 0) {
        selec->pos.y -= 81;
        selec->other--;
    }
    sfSprite_setPosition(selec->sprite, selec->pos);
    return SUCCESS;
}

static int change_down(void)
{
    text_t *texts = *all_texts();
    sprite_t *selec = find_sprite("Selected");

    if ((int)selec->dest.y + 1 >= selec->delay)
        return SUCCESS;
    if (selec->other >= 2) {
        while (texts != NULL) {
            texts->pos.y -= 81;
            texts->hide = (texts->pos.y < 430 || texts->pos.y > 700) ? 1 : 0;
            sfText_setPosition(texts->text, texts->pos);
            texts = texts->next;
        }
    }
    selec->dest.y++;
    if (selec->other < 2) {
        selec->pos.y += 81;
        selec->other++;
    }
    sfSprite_setPosition(selec->sprite, selec->pos);
    return SUCCESS;
}

static int launch_load_project(void)
{
    char *name;
    sprite_t *selec = find_sprite("Selected");
    int number = selec->dest.y;
    text_t *texts = *all_texts();

    for (int i = 0; texts != NULL; i++) {
        if (selec->delay - 1 - i == number)
            name = my_strdup(texts->name);
        texts = texts->next;
    }
    load_map(name);
    free(name);
    return SUCCESS;
}

static int analyse_events_loading(sfEvent event)
{
    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(WINDOW);
            end_it_all(SUCCESS);
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEnter) {
            sfRenderWindow_close(WINDOW);
            launch_load_project();
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyDown) {
            change_down();
            launch_load_project();
        }
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyUp) {
            change_up();
            launch_load_project();
        }
    }
    return SUCCESS;
}

int load_project(void)
{
    sfEvent event;

    make_map("map", 20, 20, 0);
    init_loading_sprites();
    launch_load_project();
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, (sfColor){106, 126, 152, 155});
        draw_sprites_in_order();
        draw_texts_in_order();
        map_to_isometrical(*get_map(), (sfIntRect){18, 14, 1063, 361}, event,
            -1);
        analyse_events_loading(event);
        sfRenderWindow_display(WINDOW);
    }
    destroy_window();
    reset_all_sprites(get_sprites());
    reset_all_texts();
    return SUCCESS;
}
