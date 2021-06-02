/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** main.cpp
*/

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include "FrameRate.hpp"
#include "IGraphic.hpp"
#include "IGame.hpp"
#include "LibraryManager.hpp"
#include "EventName.hpp"
#include "Scene.hpp"
#include "Core/World.hpp"
#include "Style.hpp"
#include "Exceptions/InitException.hpp"
#include "Save.hpp"

void init_libraries()
{
}

int handleArg(int ac, char **av)
{
    if (ac >= 2 && (!std::strcmp(av[1], "-h") || !std::strcmp(av[1], "--help")))
    {
        std::cout << "./arcade" << std::endl;
        std::cout << "./arcade path_to_graphic_lib" << std::endl;
        std::cout << "./arcade path_to_graphic_lib path_to_game_lib" << std::endl;
        std::cout << "./arcade path_to_graphic_lib -n username" << std::endl;
        std::cout << "./arcade path_to_graphic_lib path_to_game_lib -n username" << std::endl;
        return 0;
    }
    for (int i = 0; i != ac; i++) {
        if (!std::strcmp(av[i], "-n") && i < ac - 1) {
            saveNameAndScore(av[i + 1], 0);
            return (1);
        }
    }
    if (ac > 3)
    {
        std::cerr << "Invalid argument count, try './arcade -h'" << std::endl;
        return 84;
    }
    return 1;
}

#ifndef TESTS_RUN
int main(int ac, char **av)
{
    int tmp = handleArg(ac, av);
    if (tmp == 0 || tmp == 84)
        return (tmp);

    World oWorld;
    arcade::LibraryManager oLibManager;
    arcade::Scene oScene(oWorld, oLibManager);
    arcade::FrameRate frameRate(1);
    srand((unsigned) time(0));
    try
    {
        oLibManager.init("./lib", &av[1]);
        oScene.init();
        while (!oScene.running())
        {
            oScene.update(frameRate);
        }
        oScene.end();
        oLibManager.unload();
    }
    catch (const std::exception &e)
    {
        std::cerr << mecli::style::bold;
        std::cerr << mecli::style::red << "/!\\ [ERROR]: ";
        std::cerr << mecli::style::blue << e.what();
        std::cerr << mecli::style::red << " /!\\" << mecli::style::reset << std::endl;
        return 84;
    }
    return 0;
}
#endif /* TESTS_RUN */