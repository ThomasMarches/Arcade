/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibMenu.hpp header
*/

#ifndef LIBMENU_H_
#define LIBMENU_H_

#include "api.h"
#include "AGame.hpp"
#include "Core/EventManager.hpp"
#include "Core/Event.hpp"
#include "Core/World.hpp"

namespace arcade
{
    namespace lib
    {
        class LibMenu : public AGame
        {
        public:
            static const library_info_t INFO;

            LibMenu();
            ~LibMenu() override;

            void init(IScene &oScene) override;
            void update(IScene &oScene, float dt) override;
            void end(IScene &oScene) override;
            void onKeyEvent(const event::KeyboardEvent &key) override;
            void onMouseEvent(const event::MouseEvent &mouse) override;

        private:
        };

        const library_info_t LibMenu::INFO = {
            library_info::GAME,
            "Menu",
            BUILD_TIME,
            "Arcade menu",
        };
    }
}

#endif /* !LIBMENU_H_ */