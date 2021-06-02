/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** missing_delete_func.cpp
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

library_info_t library_get_data()
{
    printf("[libfoo] Meta for foo!\n");
    library_info_t info;
    info.type = library_info::GRAPHIC;
    return info;
}

#ifdef __cplusplus
}
#endif