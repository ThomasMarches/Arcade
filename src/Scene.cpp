/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include "Components/Transform.hpp"
#include "Components/AsciiSprite.hpp"
#include "Components/Sprite.hpp"
#include "Exceptions/AException.hpp"
#include "Save.hpp"

namespace arcade
{
    Scene::Scene(World &oWorld, LibraryManager &libraryManager)
        : m_oWorld(oWorld), m_rLibraryManager(libraryManager)
    {
        m_graphicSwitchType = SwitchType::Nothing;
        m_gameSwitchType = SwitchType::Nothing;
        m_newGraphicLibId = 0;
        m_newGameLibId = 0;
        m_bSwitchGame = false;
        m_bSwitchGraphic = false;

        m_exitRequested = false;
        m_gamePaused = false;

        oWorld.RegisterComponent<arcade::component::Transform>();
        oWorld.RegisterComponent<arcade::component::Sprite>();
        oWorld.RegisterComponent<arcade::component::AsciiSprite>();
    }

    Scene::~Scene() {}

    void Scene::exit()
    {
        m_exitRequested = true;
    }

    void Scene::pushEvent(const event::IEvent &event)
    {
        auto *k = dynamic_cast<const arcade::event::KeyboardEvent *>(&event);
        auto *m = dynamic_cast<const arcade::event::MouseEvent *>(&event);

        if (k && k->action == event::KeyboardEvent::DOWN)
        {
            switch (k->key)
            {
            case event::Key::KEY_ESCAPE:
            case event::Key::KEY_E:
                m_exitRequested = true;
                break;
            case event::Key::KEY_P:
                m_gamePaused = !m_gamePaused;
                if (m_gamePaused)
                    std::cout << "Game paused" << std::endl;
                else
                    std::cout << "Game resumed" << std::endl;
                break;
            case event::Key::KEY_F1:
                m_graphicSwitchType = SwitchType::Previous;
                break;
            case event::Key::KEY_F2:
                m_graphicSwitchType = SwitchType::Next;
                break;
            case event::Key::KEY_F3:
                m_gameSwitchType = SwitchType::Previous;
                break;
            case event::Key::KEY_F4:
                m_gameSwitchType = SwitchType::Next;
                break;
            case event::Key::KEY_F5:
                m_bSwitchGame = true;
                break;
            case event::Key::KEY_F9:
                if (m_newGameLibId > 0)
                {
                    m_newGameLibId--;
                    std::cerr << "Game--" << std::endl;
                }
                break;
            case event::Key::KEY_F10:
                if (m_newGameLibId < m_rLibraryManager.getGamesSize())
                {
                    m_newGameLibId++;
                    std::cerr << "Game++" << std::endl;
                }
                break;
            case event::Key::KEY_F11:
                m_bSwitchGame = true;
                break;
            }
        }

        if (!m_gamePaused)
        {
            if (lib::IGame *game = m_rLibraryManager.getGame())
            {
                if (k)
                    game->onKeyEvent(*k);
                else if (m)
                    game->onMouseEvent(*m);
            }
        }
    }

    IEntity &Scene::newEntity(std::string name)
    {
        std::unique_ptr<AEntity> ent = std::make_unique<AEntity>(m_oWorld.CreateEntity());
        AEntity &entity = *ent;

        if (!ent)
            throw AException("Entity's Shared pointer creation failed.");
        // if (m_vEntities.find(name) == m_vEntities.end())
            // m_vEntities[name] = std::vector<std::unique_ptr<IEntity>>();
        m_vEntities[name].emplace_back(std::move(ent));
        return entity;
    }

    IEntity &Scene::newEntity()
    {
        return newEntity("");
    }

    EntityList Scene::getEntity(const std::string &name)
    {
        EntityList vList;
        auto vEntities = m_vEntities.find(name);

        if (vEntities != m_vEntities.end())
            for (auto &it : vEntities->second)
                vList.push_back(*it);
        return vList;
    }

    template <typename ContainerT, typename PredicateT>
    void erase_if(ContainerT &items, const PredicateT &predicate)
    {
        for (auto it = items.begin(); it != items.end();)
        {
            if (predicate(*it))
                it = items.erase(it);
            else
                ++it;
        }
    }

    void Scene::removeEntity(const std::string& name)
    {
        if (m_vEntities.find(name) != m_vEntities.end())
            m_vEntities.erase(name);
    }

    void Scene::removeEntity(const IEntity& entity)
    {
        for (auto& vList : m_vEntities)
            vList.second.erase(std::remove_if(vList.second.begin(), vList.second.end(), [&entity](const auto& oEnt)
            {
                return oEnt.get() == &entity;
            }), vList.second.end());
    }

    void Scene::addScore(float score)
    {
        saveNameAndScore(getNameFromSave(), getScoreFromSave() + static_cast<int>(score));
    }

    void Scene::forEach(std::function<void(IEntity &)> fun)
    {
        for (auto &vList : m_vEntities)
            for (auto &it : vList.second)
                fun(*it);
    }

    void Scene::forEach(std::function<void(IEntity &)> fun, const std::string &name)
    {
        auto vList = m_vEntities.find(name);

        if (vList != m_vEntities.end())
            for (auto &it : vList->second)
                fun(*it);
    }

    void Scene::init()
    {
        m_rLibraryManager.getGame()->init(*this);
        m_rLibraryManager.getGraphic()->init(*this);
    }

    void Scene::update(arcade::FrameRate &frameRate)
    {
        float deltaTime = frameRate.getDeltaTime();
        if (!m_gamePaused)
            m_rLibraryManager.getGame()->update(*this, deltaTime);
        frameRate.synchronize();
        m_rLibraryManager.getGraphic()->update(*this, deltaTime);

        if (m_bSwitchGraphic)
        {
            m_rLibraryManager.switchGraphic(*this, m_newGraphicLibId);
            m_bSwitchGraphic = false;
        }
        if (m_graphicSwitchType != SwitchType::Nothing)
        {
            m_rLibraryManager.switchGraphic(*this, m_graphicSwitchType);
            m_graphicSwitchType = SwitchType::Nothing;
        }
        if (m_bSwitchGame)
        {
            m_rLibraryManager.switchGame(*this, m_newGameLibId);
            m_bSwitchGame = false;
        }
        if (m_gameSwitchType != SwitchType::Nothing)
        {
            m_rLibraryManager.switchGame(*this, m_gameSwitchType);
            m_gameSwitchType = SwitchType::Nothing;
        }
    }

    bool Scene::running()
    {
        return m_exitRequested || m_rLibraryManager.getGraphic()->quitRequested();
    }

    void Scene::end()
    {
        m_rLibraryManager.getGame()->end(*this);
        m_rLibraryManager.getGraphic()->end(*this);
    }

    void Scene::setWindowSize(int x, int y) {}
    math::Vector2 Scene::getWindowSize() const { return math::Vector2{}; }

} // namespace arcade