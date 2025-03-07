/*
** EPITECH PROJECT, 2024
** time_lib.c
** File description:
** The file for the times stuffs.
*/
#include "../../include/header.h"

sfClock **get_clock(void)
{
    static sfClock *clock;

    return (&clock);
}

float get_time(void)
{
    return (sfClock_getElapsedTime(*get_clock()).microseconds / 1000000.0);
}

int get_seconds(void)
{
    static float seconds = 0;
}

int diceroll(int low, int high)
{
    if (high < low)
        return high;
    return low + rand() % (high - low);
}
