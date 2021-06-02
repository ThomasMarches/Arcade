/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibraryManagerTest.cpp
*/

#include <gtest/gtest.h>
#include "LibraryManager.hpp"
#include "Exceptions/CastException.hpp"
#include "Exceptions/EmptyLibraryList.hpp"

TEST(LibraryManager, game_null_lib_create_return)
{
    Path libPath = "tests/fail_lib/game_null_lib_create_return/";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), std::exception);
}

TEST(LibraryManager, graphic_null_lib_create_return)
{
    Path libPath = "tests/fail_lib/graphic_null_lib_create_return/";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), std::exception);
}

TEST(LibraryManager, missing_create_func)
{
    Path libPath = "tests/fail_lib/missing_create_func/";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), std::exception);
}

TEST(LibraryManager, missing_delete_func)
{
    Path libPath = "tests/fail_lib/missing_delete_func/";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), std::exception);
}

TEST(LibraryManager, missing_get_info_func)
{
    Path libPath = "tests/fail_lib/missing_get_info_func/";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), std::exception);
}

TEST(LibraryManager, empty_lib)
{
    Path libPath = "tests/fail_lib";
    arcade::LibraryManager manager;
    EXPECT_THROW(manager.load(libPath), EmptyLibraryList);
}

TEST(LibraryManager, success_load_correct_lib)
{
    Path libPath = "tests/succes_lib";
    arcade::LibraryManager manager;
    EXPECT_NO_THROW(manager.load(libPath));
}