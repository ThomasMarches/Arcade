/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** game_null_lib_create_return.cpp
*/

#include <stdio.h>
#include "api.h"

const library_info_t INFO = {
    library_info::GAME,
    "Tests",
    BUILD_TIME,
    "Tests",
};
        
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

library_info_t library_get_data()
{
    printf("[libfoo] Meta for foo!\n");
    return INFO;
}

#ifdef __cplusplus
}
#endif