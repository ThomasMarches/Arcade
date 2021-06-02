/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibPacman.hpp header
*/

#ifndef LIBPACMAN_H_
#define LIBPACMAN_H_

#include "api.h"
#include "AGame.hpp"
#include "Core/EventManager.hpp"
#include "Core/Event.hpp"
#include "Core/World.hpp"
#include "Core/Vec2.hpp"

namespace arcade
{
    namespace lib
    {
        class LibPacman : public AGame
        {
        public:
            static const library_info_t INFO;

            LibPacman();
            ~LibPacman() override;

            void init(IScene &oScene) override;
            void update(IScene &oScene, float dt) override;
            void end(IScene &oScene) override;
            void onKeyEvent(const event::KeyboardEvent& key) override;
            void onMouseEvent(const event::MouseEvent& mouse) override;
        private:
            Vec2 m_player_dir;
            IScene *m_pScene;
            bool m_bIsGameover;
        };

        const library_info_t LibPacman::INFO = {
            library_info::GAME,
            "Pacman",
            BUILD_TIME,
            "Pacman game",
        };
    }
}

#endif /* !LIBPACMAN_H_ */