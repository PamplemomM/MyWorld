/*
** EPITECH PROJECT, 2025
** map_save.c
** File description:
** The file that will handle the save of a project
*/
#include "../include/header.h"

static char *my_fts(double nbr)
{
    int int_part = (int)nbr;
    int precision = 100;
    int decimal_part = (int)((nbr - int_part) * precision);
    char *int_str = my_its(int_part);
    char *dec_str = my_its(abs(decimal_part));
    char *concat = my_sec_strcat(int_str, ".");
    char *result = my_sec_strcat(concat, dec_str);

    if (result == NULL)
        return NULL;
    free(int_str);
    free(dec_str);
    free(concat);
    return result;
}

static int write_map_value(int fd, float value)
{
    char *temp = my_its((int)value);
    int result = SUCCESS;

    if (write(fd, temp, my_strlen(temp)) < 0)
        result = ERROR;
    if (result == SUCCESS && write(fd, " ", 1) < 0)
        result = ERROR;
    free(temp);
    return result;
}

static int write_map_row(int fd, float *row, int size)
{
    int result = SUCCESS;

    for (int j = 0; j < size && result == SUCCESS; j++) {
        result = write_map_value(fd, row[j]);
    }
    if (result == SUCCESS && write(fd, "\n", 1) < 0)
        result = ERROR;
    return result;
}

static int write_map(int fd, map_t *map)
{
    int result = SUCCESS;

    for (int i = 0; i < map->size.x && result == SUCCESS; i++) {
        result = write_map_row(fd, map->map[i], map->size.y);
    }
    return result;
}

static int write_map_header(int fd, map_t *map)
{
    char *temp = my_its(map->size.x);
    int result = SUCCESS;

    if (write(fd, map->name, my_strlen(map->name)) < 0)
        result = ERROR;
    if (result == SUCCESS && write(fd, "\n", 1) < 0)
        result = ERROR;
    if (result == SUCCESS && write(fd, temp, my_strlen(temp)) < 0)
        result = ERROR;
    if (result == SUCCESS && write(fd, "\n", 1) < 0)
        result = ERROR;
    free(temp);
    return result;
}

int save_map(char *file)
{
    char *file_infolder = my_sec_strcat("target/", file);
    char *complete_file = my_sec_strcat(file_infolder, ".legend");
    int fd = open(complete_file, O_CREAT | O_WRONLY | O_TRUNC, 00664);
    map_t *map = *get_map();
    int result = SUCCESS;

    mini_printf("Saving... %s\n", complete_file);
    if (fd < 0)
        result = ERROR;
    if (result == SUCCESS && write_map_header(fd, map) == ERROR)
        result = ERROR;
    if (result == SUCCESS && write_map(fd, map) == ERROR)
        result = ERROR;
    free(file_infolder);
    free(complete_file);
    close(fd);
    return result;
}
