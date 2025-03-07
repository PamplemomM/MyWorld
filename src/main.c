/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** The temp file with the main.
*/
#include "../include/header.h"

const sfColor SLATEGRAY = {112, 128, 145, 255};
const sfColor DARKSLATEGRAY = {47, 79, 79, 255};
const sfColor BACKGROUND = {106, 126, 152, 155};

static int check_buttons(sprite_t *sprite, sfVector2i event)
{
    sfFloatRect position = sfSprite_getGlobalBounds(sprite->sprite);

    if (sfFloatRect_contains(&position, event.x, event.y)) {
        if (sfMouse_isButtonPressed(sfMouseLeft))
            sprite->other = 1;
        sfSprite_setScale(sprite->sprite, (sfVector2f){1.15, 1.15});
        return 1;
    }
    sfSprite_setScale(sprite->sprite, (sfVector2f){1, 1});
    return SUCCESS;
}

static int analyse_buttons_events(void)
{
    sprite_t *current = *get_sprites();
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(WINDOW);
    sprite_t *cursor = find_sprite("Cursor");

    if (cursor != NULL)
        move_sprite(cursor, mouse_pos.x - cursor->pos.x,
            mouse_pos.y - cursor->pos.y);
    while (current != NULL) {
        if (current->type == 1)
            check_buttons(current, mouse_pos);
        current = current->next;
    }
    return SUCCESS;
}

static int change_back(int *onoff, sprite_t *current)
{
    sfTexture_destroy(current->texture);
    current->texture = sfTexture_createFromFile((*onoff == 1) ?
        "img/Usage.png" : "img/Usagedark.png", NULL);
    *onoff = (*onoff == 0) ? 1 : 0;
    find_sprite("Theme")->other = 0;
    sfSprite_setTexture(current->sprite, current->texture, sfTrue);
    setsprite_rect(find_sprite("SizePanel"),
        (sfIntRect){(*onoff == 1) ? 188 : 0, 0, 188, 321});
    return SUCCESS;
}

static int auto_save(void)
{
    static int time = 0.0;
    static int time_respawn = 0.0;
    static int cpt = 0.0;
    text_t *autosave = find_text("AutoSave");

    if (autosave->hide == 0)
        sfRenderWindow_drawText(WINDOW, autosave->text, NULL);
    if (autosave->hide == 0) {
        if (get_time() - time_respawn >= 2) {
            autosave->hide = 1;
        }
    }
    if (get_time() - time < 10)
        return 1;
    time_respawn = get_time();
    time = get_time();
    save_map((*get_map())->name);
    autosave->hide = 0;
}

static int next_detect_button(void)
{
    sprite_t *current = find_sprite("Bg");
    static int onoff = 1;
    static float time = 0.0;

    if (get_time() - time < 0.5)
        return 1;
    time = get_time();
    if (find_sprite("File")->other == 1) {
        find_sprite("File")->other == 0;
        save_map((*get_map())->name);
    }
    if (find_sprite("Theme")->other == 1)
        change_back(&onoff, current);
    return SUCCESS;
}

static int detect_buttons(void)
{
    sprite_t *current = find_sprite("RaiseBut");

    if (find_sprite("Close")->other == 1) {
        sfRenderWindow_close(WINDOW);
        end_it_all(SUCCESS);
    }
    if (current->other == 1) {
        change_texture_from_file(find_sprite("Cursor"), "img/raise.png");
        current->other = 0;
    }
    current = find_sprite("CursorBut");
    if (current->other == 1) {
        change_texture_from_file(find_sprite("Cursor"), "img/cursor.png");
        current->other = 0;
    }
    next_detect_button();
    return SUCCESS;
}

int execute_program(void)
{
    sfEvent event;
    map_t *map = *get_map();

    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        draw_sprites_in_order();
        analyse_buttons_events();
        detect_buttons();
        draw_map(*get_map(), (sfIntRect){425, 0, 408, 398});
        map_to_isometrical(*get_map(),
            (sfIntRect){120, 0, 1820, 1024}, event, sfTrue);
        auto_save();
        sfRenderWindow_drawText(WINDOW, find_text("Size")->text, NULL);
        sfRenderWindow_drawSprite(WINDOW, find_sprite("Cursor")->sprite, NULL);
        sfRenderWindow_display(WINDOW);
    }
    return SUCCESS;
}

int launch_program(void)
{
    char *name = my_sec_strcat("MyWorld - ", (*get_map())->name);

    init_window(name, 1820, 1024);
    sfRenderWindow_setMouseCursorVisible(WINDOW, sfFalse);
    free(name);
    init_project_sprites();
    execute_program();
    destroy_window();
    reset_all_sprites(get_sprites());
    reset_all_texts();
    return SUCCESS;
}

static int display_usage(void)
{
    mini_printf("-- my_world --\n\n");
    mini_printf("my_world is a simple 3D word editing software.\n\n");
    mini_printf("Usage\n");
    mini_printf("Create/Load Project: Choose at startup.\n");
    mini_printf("Controls:\n");
    mini_printf("Up/Down arrows: Select project\n");
    mini_printf("Enter: Launch project\n");
    mini_printf("Left/Right click: Raise/Drop map\n");
    mini_printf("Left/Right arrows: Change view\n");
    mini_printf("Click nuclear icon: Reset map\n");
    mini_printf("Size bar: Adjust brush size\n");
    mini_printf("Bottom right: Save, change theme, or exit\n\n");
    mini_printf("Enjoy editing with my_world!\n");
    return SUCCESS;
}

int main(int argc, char **argv)
{
    int nb = 15;

    if (argc > 1 && my_strcmp(argv[1], "-h") == 0) {
        display_usage();
        return SUCCESS;
    }
    srand(time(NULL));
    *get_clock() = sfClock_create();
    init_log();
    if (launch_fileprompt() == 1)
        load_project();
    else
        create_project();
    launch_program();
    return SUCCESS;
}
