/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** api.h header
*/

#ifndef API_H_PRIVATE
#define API_H_PRIVATE

#include "Common/api.h"

// BUILD_TIME defined in CMake
#ifndef BUILD_TIME
#define BUILD_TIME 0
#endif /* !__BUILD_TIME */

#ifdef __cplusplus
#define PRIVATE_EXTERN_C extern "C" {
#define PRIVATE_EXTERN_C_END }
#else
#define PRIVATE_EXTERN_C
#define PRIVATE_EXTERN_C_END
#endif

#define INIT_LIB_API(class)                                      \
    PRIVATE_EXTERN_C                                             \
    void *library_create()                                       \
    {                                                            \
        printf("[" #class "] Loading " #class " library ...\n"); \
        return new arcade::lib::class();                         \
    }                                                            \
    void library_delete(void *library)                           \
    {                                                            \
        printf("[" #class "] " #class " closing ...\n");         \
        delete static_cast<arcade::lib::class *>(library);       \
    }                                                            \
    library_info_t library_get_data()                            \
    {                                                            \
        printf("[" #class "] Meta for " #class "!\n");           \
        return arcade::lib::class ::INFO;                        \
    }                                                            \
    PRIVATE_EXTERN_C_END

#endif /* !API_H_PRIVATE */