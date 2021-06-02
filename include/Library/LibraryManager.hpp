/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibraryManager.hpp header
*/

#ifndef ARCADE_LIBRARY_MANAGER_HPP
#define ARCADE_LIBRARY_MANAGER_HPP

#include <functional>
#include <vector>
#include <utility>
#include <memory>
#include "Path.hpp"
#include "ArcadeLib.hpp"
#include "IGraphic.hpp"
#include "IGame.hpp"
#include "api.h"

namespace arcade
{
    enum class SwitchType
    {
        Nothing,
        Previous,
        Next,
    };

    class LibraryManager
    {
    public:
        LibraryManager();
        ~LibraryManager();

        void init(const std::string &path, const char *const *args);
        bool add(const std::string &strPath);
        bool exist(const std::string &strPath);

        void load(Path path);

        void unload();
        void unloadGraphic();
        void unloadGame();

        void setGraphic(std::size_t lIndex);
        void setGraphic(const std::string &alName);
        void setGame(std::size_t lIndex);
        void setGame(const std::string &alName);

        void switchGraphic(IScene& scene, std::size_t lIndex);
        void switchGame(IScene& scene, std::size_t lIndex);
        void switchGraphic(IScene& scene, const SwitchType &switchType);
        void switchGame(IScene& scene, const SwitchType &switchType);

        lib::IGraphic *getGraphic();
        lib::IGame *getGame();
        ArcadeLib &getGraphicLib();
        ArcadeLib &getGameLib();
        std::size_t getGamesSize();
        std::size_t getGraphicsSize();

    private:
        std::vector<ArcadeLib::UPtr> m_vLibs;
        std::vector<ArcadeLib*> m_vGraphics;
        std::vector<ArcadeLib*> m_vGames;

        std::size_t m_graphicID;
        lib::IGraphic *m_pGraphic;
        ArcadeLib* m_spGraphicSharedLib;

        std::size_t m_gameID;
        lib::IGame *m_pGame;
        ArcadeLib* m_spGameSharedLib;
    };
}
#endif