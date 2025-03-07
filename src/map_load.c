/*
** EPITECH PROJECT, 2025
** map_load.c
** File description:
** The file that will handle the load of a project
*/
#include "../include/header.h"

static char *read_line(int fd, int size)
{
    char *buffer = malloc(sizeof(char) * size + 1);
    int i = 0;
    int res = 0;

    if (buffer == NULL)
        return NULL;
    res = read(fd, &buffer[i], 1);
    while (res > 0 && buffer[i] != '\n' && buffer[i] != '\0' && i < size) {
        i++;
        res = read(fd, &buffer[i], 1);
    }
    if (res <= 0 && i == 0) {
        free(buffer);
        return NULL;
    }
    buffer[i] = '\0';
    return buffer;
}

static int read_name_and_size(int fd, map_t *map)
{
    char *line = read_line(fd, 21);

    if (line == NULL)
        return ERROR;
    map->name = my_strdup(line);
    free(line);
    line = read_line(fd, 3);
    if (line == NULL)
        return ERROR;
    map->size.x = my_getnbr(line) - 1;
    map->size.y = map->size.x;
    free(line);
    return SUCCESS;
}

static int check_bounds(map_t *map, int i, int j)
{
    if (map->map[i][j] < -30 || map->map[i][j] > 50) {
        map->map[i][j] = 0;
        if (j > 0)
            map->map[i][j] = map->map[i][j - 1];
        if (i > 0)
            map->map[i][j] = map->map[i - 1][j];
    }
    return map->map[i][j];
}

static int read_map(int fd, map_t *map)
{
    char *line = NULL;
    char *cur = NULL;

    map->map = malloc(sizeof(float *) * map->size.x);
    if (map->map == NULL)
        return ERROR;
    for (int i = 0; i < map->size.x; i++) {
        map->map[i] = malloc(sizeof(float) * map->size.x);
        line = read_line(fd, map->size.x * 6);
        if (map->map[i] == NULL || line == NULL)
            return ERROR;
        cur = strtok(line, " ");
        for (int j = 0; j < map->size.x && cur != NULL; j++) {
            map->map[i][j] = (cur == NULL) ? 0.0 : atoi(cur);
            map->map[i][j] = check_bounds(map, i, j);
            cur = strtok(NULL, " ");
        }
        free(line);
    }
    return SUCCESS;
}

int load_map(char *file)
{
    char *fileinfolder = my_sec_strcat("target/", file);
    char *comp_file = my_sec_strcat(fileinfolder, ".legend");
    int fd;
    map_t *map = malloc(sizeof(map_t) * 1);

    fd = open(comp_file, O_RDONLY);
    free(comp_file);
    free(fileinfolder);
    if (map == NULL || fd < 0)
        return ERROR;
    if (read_name_and_size(fd, map) == ERROR || read_map(fd, map) == ERROR)
        return ERROR;
    close(fd);
    free_map();
    *get_map() = map;
    return SUCCESS;
}
