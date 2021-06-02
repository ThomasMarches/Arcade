/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibNibbler.hpp header
*/

#ifndef LIBNIBBLER_H_
#define LIBNIBBLER_H_

#include "api.h"
#include "AGame.hpp"
#include "Core/Vec2.hpp"

namespace arcade
{
    namespace lib
    {
        class LibNibbler : public AGame
        {
        public:
            static const library_info_t INFO;

            LibNibbler();
            ~LibNibbler() override;

            void init(IScene &oScene) override;
            void update(IScene &oScene, float dt) override;
            void end(IScene &oScene) override;
            void onKeyEvent(const event::KeyboardEvent &key) override;
            void onMouseEvent(const event::MouseEvent &mouse) override;

            void createGameBox(IScene &oScene, int gameboxSize);

        private:
            float m_fDt;
            float m_fSpeed;
            IScene *m_pScene;
            Vec2 m_player_dir;
            bool m_bIsGameover;
        };

        const library_info_t LibNibbler::INFO = {
            library_info::GAME,
            "Nibbler",
            BUILD_TIME,
            "Nibbler game",
        };
    }
}

#endif /* !LIBNIBBLER_H_ */