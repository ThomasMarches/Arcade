/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** SharedLibraryTest.cpp
*/

#include <gtest/gtest.h>
#include "SharedLib.hpp"

TEST(TestTrue, firstTest)
{
    EXPECT_TRUE(1 == 1);
}

TEST(SharedLib, close_an_empty_lib)
{
    arcade::SharedLib lib;
    EXPECT_THROW(lib.close(), std::runtime_error);
}

TEST(SharedLib, sym_null_library)
{
    arcade::SharedLib lib;
    int *i;
    EXPECT_THROW(lib.sym("", i), std::runtime_error);
}

TEST(SharedLib, open_in_non_existing_lib)
{
    arcade::SharedLib lib;
    EXPECT_THROW(lib.open("lib_not_exist"), std::runtime_error);
}

TEST(SharedLib, open_existing_lib)
{
    arcade::SharedLib lib;
    EXPECT_NO_THROW(lib.open("lib/arcade_nibbler.so"));
}

TEST(SharedLib, close_existing_lib)
{
    EXPECT_NO_THROW({
        arcade::SharedLib lib("lib/arcade_nibbler.so");
        lib.close();
    });
}

TEST(SharedLib, sym_non_existing_symbol)
{
    EXPECT_THROW({
        arcade::SharedLib lib("lib/arcade_nibbler.so");
        int *i;
        lib.sym("unkonown", i);
    },
                 std::runtime_error);
}

TEST(SharedLib, sym_existing_symbol)
{
    EXPECT_NO_THROW({
        arcade::SharedLib lib("lib/arcade_nibbler.so");
        void *(*func)() = 0;
        lib.sym("library_create", func);
    });
}