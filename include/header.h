/*
** EPITECH PROJECT, 2024
** header.h
** File description:
** Header of the my_radar project.
*/
#ifndef HEADER_H
    #define HEADER_H

    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <time.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <fcntl.h>

    #include "start.h"

    //macros :
    #define SQ(a) (a * a)
    #define PI 3.141592653589793238462
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX(a, b) intmap[0][h] != -1((a) > (b) ? (a) : (b))

    //defines :
    #define SUCCESS 0
    #define ERROR 84
    #define MAP_SIZE 15
    #define WINDOW *get_window()

    // map :

    #define SCALE 300.0
    #define MAP_ANGLE_X 180.0
    #define MAP_ANGLE_Y 2.0


typedef struct map_s {
    char *name;
    float **map;
    int event_active;
    sfVector2i size;
    sfTexture *texture;
    sfRenderStates *state;
} map_t;

typedef struct log_s {
    int menu;
    int mode;
    int file;
    int edit;
    struct map_s *map;
} log_t;

typedef struct sprite_s {
    char *name;
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    sfVector2f pos;
    sfVector2f dest;
    sfVector2f velocity;
    float speed;
    int delay;
    float rotation;
    int type;
    int hide;
    int other;
    struct sprite_s *next;
} sprite_t;

typedef struct text_s {
    char *name;
    sfFont *font;
    struct name_s *string;
    sfText *text;
    sfVector2f pos;
    sfVector2f move;
    sfVector2f velocity;
    float rotation;
    int size;
    int hide;
    float other;
    struct text_s *next;
} text_t;

typedef struct rect_s {
    char *name;
    sfRectangleShape *shape;
    sfSprite *sprite;
    sfVector2f pos;
    sfColor color;
    sfColor outline;
    float height;
    float distance;
    int thickness;
    float rotation;
    int hide;
    float other;
    float speed;
    struct rect_s *next;
} rect_t;

// ------------ LIB FUNCTIONS ------------

// --- c_functions.c ---
int my_strlen(char const *str);
char *my_strdup(char const *src);
int my_putstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int mini_printf(const char *format, ...);

// --- keyoard_lib.c ---
// Get the keyboard intputs and fill the linked list
int get_keyboard_input(sfKeyCode event, name_t **list, int limit);
// Transform the linked list into a functional string
char *my_keybrd_to_str(name_t *list);

// --- my_str_to_word_array ---
char **my_str_to_word_array(char *str);
void free_word_array(char **wa);
int my_print_wa(char **wa);

// --- sprite_lib.c ---
// Get the linked list of the sprites
sprite_t **get_sprites(void);
// Create a new sprite (Auto update in the linked list)
void sprite_create(char *name, char const *texture_path, sfVector2f position);
// Find a specific sprite with his name
sprite_t *find_sprite(char *name);
// Destroy all the sprites
void reset_all_sprites(sprite_t **all_sprite);
// Move a sprite
void move_sprite(sprite_t *sprite, float x, float y);

// --- text_lib ---
// Get the linked list of the texts
text_t **all_texts(void);
// Find a specific text with his name
text_t *find_text(char *name);
// Create a new text (Auto update in the linked list)
void create_text(char *name, sfVector2f position, int size,
    char const *font_path);
// Destroy all the text linked list
void reset_all_texts(void);
// Draw all the texts in order
int draw_texts_in_order(void);

// --- time_lib ---
// Get the current running clock
sfClock **get_clock(void);
// Get the current time spend
float get_time(void);
// Get the current seconds spends
int get_seconds(void);
// Rolls a random dice "(1, 2) == 1" -> 1 chance out of 2
int diceroll(int low, int high);

// --- tools_c_func.c ---
// Concatenates two strings with a malloc (don't forget to free it)
char *my_sec_strcat(char *dest, char const *src);
// Reverse a string
char *my_revstr(char *str);
// Transform an int to a string
char *my_its(int nbr);
// Transform a string into an int
int my_getnbr(char *str);
// Set the int rect of a sprite
int setsprite_rect(sprite_t *sprite, sfIntRect new);

// --- tools_csfml.c ---
void my_tween(float *nb, float endval, float intensity, int *condition);
int change_texture_from_file(sprite_t *sprite, char *filepath);

// --- window_lib ---
// Get the current displayed window
sfRenderWindow **get_window(void);
// Create a new window (Auto edit get_window)
void init_window(char *name, unsigned int width, unsigned int height);
// Destroy the actual window
void destroy_window(void);
// Finish the program and destroy everything
int end_it_all(int exiting_number);
// Draw all the sprites in the creation order
int draw_sprites_in_order(void);

// ------------ MAP FUNCTIONS ------------

// --- map_draw.c ---
sfColor get_terrain_color(float height);
int draw_map(map_t *map, sfIntRect pos);

// --- map_gen_random.c ---
int make_floor(float **map, int width, int height);

// --- map_gen.c ---
map_t **get_map(void);
float *map_to_int(float **map, int rows, int cols);
void free_map(void);
int make_flat(float **map, int x, int y);
int make_map(char *name, int x, int y, int flat);

// --- map_modifier.c ---
int raise(map_t *map, sfVector2f pos, float intensite, int size);
int drop(map_t *map, sfVector2f pos, float intensite, int size);
void reset_map(map_t *map);

// --- map_save.c ---
int save_map(char *file);

// --- map_load.c ---
int load_map(char *file);

// ------------ MY WORLD FUNCTIONS ------------

// --- logstuffs.c ---
log_t **get_log(void);
int init_log(void);

// --- isometrical_analisis.c ---
int handle_mouse_input(map_t *map, sfIntRect pos, sfVector2f offset,
    sfVector2f angle);
int analyse_mouse_events(sfEvent event, sfVector2f *angle);

// --- isometrical_view.c ---
int map_to_isometrical(map_t *map, sfIntRect pos, sfEvent event,
    int event_active);

// --- file_prompt ---
int launch_fileprompt(void);

// --- project_build.c ---
int init_project_sprites(void);

// --- project_load.c ---
int load_project(void);

// --- project_creation.c ---
int create_project(void);

int main(int argc, char **argv);

#endif /* HEADER_H */
