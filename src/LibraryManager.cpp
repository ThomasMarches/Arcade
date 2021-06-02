/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibraryManager.cpp
*/

#include <cstring>
#include <memory>
#include "LibraryManager.hpp"
#include "api.h"
#include "Exceptions/InitException.hpp"
#include "Exceptions/CastException.hpp"
#include "Exceptions/EmptyLibraryList.hpp"

namespace arcade
{
    LibraryManager::LibraryManager()
    {
        m_graphicID = 0;
        m_pGraphic = nullptr;

        m_gameID = 0;
        m_pGame = nullptr;
    }

    LibraryManager::~LibraryManager()
    {
        m_vGames.clear();
        m_vGraphics.clear();
        m_vLibs.clear();
    }

    void LibraryManager::init(const std::string &path, const char *const *args)
    {
        for (int k = 0; args[k]; k++) {
            if (!std::strcmp(args[k], "-n")) {
                k++;
                continue;
            }
            add(args[k]);
        }
        load(Path(path));

        // set graphic
        if (args[0])
            setGraphic(args[0]);
        else
            setGraphic(0);

        // set game
        if (args[0] && args[1] && std::strcmp(args[1], "-n"))
            setGame(args[1]);
        else
        {
            try
            {
                setGame("Menu");
            }
            catch (...)
            {
                setGame(0);
            }
        }
    }

    bool LibraryManager::exist(const std::string &strPath)
    {
        for (int i = 0; i < m_vLibs.size(); ++i)
        {
            if (Path(m_vLibs[i]->getPath()).filename() == Path(strPath).filename())
                return true;
        }
        return false;
    }

    bool LibraryManager::add(const std::string &strPath)
    {
        library_info_t info;

        if (exist(strPath))
            return false;
        arcade::ArcadeLib::UPtr sharedLib = std::make_unique<arcade::ArcadeLib>(strPath);
        info = sharedLib->getInfo();

        if (info.type == library_info::GRAPHIC)
        {
            m_vGraphics.push_back(sharedLib.get());
        }
        else if (info.type == library_info::GAME)
        {
            m_vGames.push_back(sharedLib.get());
        }
        else
            throw InitException("LibraryManager: \"" + strPath + "\" Invalid type");
        m_vLibs.push_back(std::move(sharedLib));
        return true;
    }

    void LibraryManager::load(Path path)
    {
        Path::paths vPaths = path.get_all_files(DL_EXT);

        for (auto &path : vPaths)
            add(path.string());
        if (m_vGraphics.size() == 0)
            throw EmptyLibraryList("LibraryManager: Empty graphical library list.");
        if (m_vGames.size() == 0)
            throw EmptyLibraryList("LibraryManager: Empty game library list.");
    }

    void LibraryManager::unload()
    {
        m_pGraphic = nullptr;
        m_pGame = nullptr;
        m_spGraphicSharedLib = nullptr;;
        m_spGameSharedLib = nullptr;
        m_vGames.clear();
        m_vGraphics.clear();
        m_vLibs.clear();
    }

    void LibraryManager::unloadGraphic()
    {
        if (m_pGraphic)
        {
            m_spGraphicSharedLib->unload();
            m_pGraphic = nullptr;
        }
    }

    void LibraryManager::unloadGame()
    {
        if (m_pGame)
        {
            m_spGameSharedLib->unload();
            m_pGame = nullptr;
        }
    }

    void LibraryManager::setGraphic(std::size_t lIndex)
    {
        unloadGraphic();
        if (lIndex >= m_vGraphics.size())
            throw AException("LibraryManager: Index of graphic lib out of range.");
        m_spGraphicSharedLib = m_vGraphics.at(lIndex);
        m_spGraphicSharedLib->init();
        m_pGraphic = m_spGraphicSharedLib->get<arcade::lib::IGraphic>();
        m_graphicID = lIndex;
    }

    void LibraryManager::setGraphic(const std::string &alName)
    {
        if (alName.empty())
        {
            setGraphic(0);
            return;
        }
        unloadGraphic();
        for (int i = 0; i < m_vGraphics.size(); ++i)
        {
            if (m_vGraphics[i]->getPath() == alName || m_vGraphics[i]->getInfo().name == alName)
            {
                setGraphic(i);
                return;
            }
        }
        throw CastException("LibraryManager: Graphic library '" + alName + "' not found.");
    }

    void LibraryManager::setGame(std::size_t lIndex)
    {
        unloadGame();
        if (lIndex >= m_vGames.size())
            throw AException("LibraryManager: Index of game lib out of range.");
        m_spGameSharedLib = m_vGames.at(lIndex);
        m_spGameSharedLib->init();
        m_pGame = m_spGameSharedLib->get<arcade::lib::IGame>();
        m_gameID = lIndex;
    }

    void LibraryManager::setGame(const std::string &alName)
    {
        if (alName.empty())
        {
            setGame(0);
            return;
        }
        unloadGame();
        for (int i = 0; i < m_vGames.size(); ++i)
        {
            if (m_vGames[i]->getPath() == alName || m_vGames[i]->getInfo().name == alName)
            {
                setGame(i);
                return;
            }
        }
        throw CastException("LibraryManager: Game library '" + alName + "' not found.");
    }

    void LibraryManager::switchGraphic(IScene &scene, std::size_t lIndex)
    {
        getGraphic()->end(scene);
        setGraphic(lIndex);
        getGraphic()->init(scene);
    }

    void LibraryManager::switchGame(IScene &scene, std::size_t lIndex)
    {
        getGame()->end(scene);
        setGame(lIndex);
        getGame()->init(scene);
    }

    void LibraryManager::switchGraphic(IScene &scene, const SwitchType &switchType)
    {
        if (switchType == SwitchType::Nothing)
            return;

        if (switchType == SwitchType::Previous)
        {
            if (m_graphicID == 0)
                m_graphicID = getGraphicsSize() - 1;
            else
                m_graphicID--;
        }
        else
        {
            m_graphicID++;
            if (m_graphicID >= getGraphicsSize())
                m_graphicID = 0;
        }
        switchGraphic(scene, m_graphicID);
    }

    void LibraryManager::switchGame(IScene &scene, const SwitchType &switchType)
    {
        if (switchType == SwitchType::Nothing)
            return;

        if (switchType == SwitchType::Previous)
        {
            if (m_gameID == 0)
                m_gameID = getGamesSize() - 1;
            else
                m_gameID--;
        }
        else
        {
            m_gameID++;
            if (m_gameID >= getGamesSize())
                m_gameID = 0;
        }
        switchGame(scene, m_gameID);
    }

    lib::IGraphic *LibraryManager::getGraphic()
    {
        return m_pGraphic;
    }

    lib::IGame *LibraryManager::getGame()
    {
        return m_pGame;
    }

    ArcadeLib &LibraryManager::getGraphicLib()
    {
        return *m_spGraphicSharedLib;
    }

    ArcadeLib &LibraryManager::getGameLib()
    {
        return *m_spGameSharedLib;
    }

    std::size_t LibraryManager::getGamesSize()
    {
        return m_vGames.size();
    }

    std::size_t LibraryManager::getGraphicsSize()
    {
        return m_vGraphics.size();
    }
}