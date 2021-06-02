/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Scene.hpp header
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <utility>
#include "FrameRate.hpp"
#include "IScene.hpp"
#include "LibraryManager.hpp"
#include "AEntity.hpp"
#include "IGame.hpp"
#include "Core/World.hpp"

namespace arcade
{
    class Scene : public IScene
    {
    public:
        Scene(World& oWorld, LibraryManager &libraryManager);
        ~Scene();
        void exit() override;
        void pushEvent(const event::IEvent &event) override;

        IEntity &newEntity(std::string name) override;
        IEntity &newEntity() override;
        EntityList getEntity(const std::string &name) override;
        void removeEntity(const std::string &name) override;
        void removeEntity(const IEntity &entity) override;

        void addScore(float score) override;

        void forEach(std::function<void(IEntity &)>) override;
        void forEach(std::function<void(IEntity&)>, const std::string& name);

        void setWindowSize(int x, int y) override;
        math::Vector2 getWindowSize() const override;

        void init();
        void update(arcade::FrameRate &frameRate);
        bool running();
        void end();

    protected:
    private:
        LibraryManager& m_rLibraryManager;
        World& m_oWorld;
        EntityMap m_vEntities;

        // builtin lib switching
        SwitchType m_graphicSwitchType;
        SwitchType m_gameSwitchType;

        // menu lib switching
        int m_newGraphicLibId;
        int m_newGameLibId;
        bool m_bSwitchGame;
        bool m_bSwitchGraphic;

        bool m_exitRequested;
        bool m_gamePaused;
    };
}

#endif /* !SCENE_HPP_ */