/*
** EPITECH PROJECT, 2025
** logstuffs.c
** File description:
** The file that will handle the log/info of the user.
*/
#include "../include/header.h"

log_t **get_log(void)
{
    static log_t *log = NULL;

    return &log;
}

int init_log(void)
{
    log_t *log = malloc(sizeof(log_t) * 1);

    if (log == NULL)
        return ERROR;
    log->menu = 0;
    log->mode = 0;
    log->file = 0;
    log->edit = 0;
    *get_log() = log;
    return SUCCESS;
}
