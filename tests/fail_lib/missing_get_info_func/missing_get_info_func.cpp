/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** missing_get_info_func.cpp
*/

#include <stdio.h>
#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

void *library_create()
{
    printf("[libfoo] Loading foo library ...\n");
    return nullptr;
}

void library_delete(void *library)
{
    printf("[libfoo] foo closing ...\n");
}

#ifdef __cplusplus
}
#endif