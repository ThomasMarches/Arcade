/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibNCurses.hpp header
*/

#ifndef LIBNCURSES_H_
#define LIBNCURSES_H_

#include <unordered_map>
#include <ncurses.h>
#include <memory>

#include "api.h"
#include "IGraphic.hpp"
#include "AGraphic.hpp"
#include "Event/Event.hpp"

namespace arcade
{
    namespace lib
    {
        class LibNCurses : public AGraphic
        {
        public:
            static const library_info_t INFO;
            static std::unordered_map<int, arcade::event::Key> NcursesKeyEventMap;

            LibNCurses();
            ~LibNCurses();
            void init(IScene &oScene) override;
            void update(IScene &oScene, float dt) override;
            void end(IScene &oScene) override;

            void clear();
            void display(IScene &oScene);

        private:
            // WINDOW *m_oWindow;
        };

        const library_info_t LibNCurses::INFO = {
            library_info::GRAPHIC,
            "NCurses",
            BUILD_TIME,
            "NCurses: terminal rendering",
        };

        std::unordered_map<int, arcade::event::Key> LibNCurses::NcursesKeyEventMap{
            {27, arcade::event::Key::KEY_ESCAPE},
            {KEY_BACKSPACE, arcade::event::Key::KEY_BACK_SPACE},
            {KEY_LEFT, arcade::event::Key::KEY_ARROW_LEFT},
            {KEY_RIGHT, arcade::event::Key::KEY_ARROW_RIGHT},
            {KEY_UP, arcade::event::Key::KEY_ARROW_UP},
            {KEY_DOWN, arcade::event::Key::KEY_ARROW_DOWN},
            {KEY_SLEFT, arcade::event::Key::KEY_SHIFT_LEFT},
            {KEY_SRIGHT, arcade::event::Key::KEY_SHIFT_RIGHT},
            // {SDLK_LCTRL, arcade::event::Key::KEY_CTRL_LEFT};
            // {SDLK_RCTRL, arcade::event::Key::KEY_CTRL_RIGHT};
            // {SDLK_LALT, arcade::event::Key::KEY_ALT_LEFT};
            // {SDLK_RALT, arcade::event::Key::KEY_ALT_RIGHT};
            {KEY_PPAGE, arcade::event::Key::KEY_PAGE_UP},
            {KEY_NPAGE, arcade::event::Key::KEY_PAGE_DOWN},
            {KEY_DC, arcade::event::Key::KEY_DELETE},
            {10, arcade::event::Key::KEY_INSERT},
            {KEY_END, arcade::event::Key::KEY_END_FILE},
            {32, arcade::event::Key::KEY_SPACE},
            {KEY_F(1), arcade::event::Key::KEY_F1},
            {KEY_F(2), arcade::event::Key::KEY_F2},
            {KEY_F(3), arcade::event::Key::KEY_F3},
            {KEY_F(4), arcade::event::Key::KEY_F4},
            {KEY_F(5), arcade::event::Key::KEY_F5},
            {KEY_F(6), arcade::event::Key::KEY_F6},
            {KEY_F(7), arcade::event::Key::KEY_F7},
            {KEY_F(8), arcade::event::Key::KEY_F8},
            {KEY_F(9), arcade::event::Key::KEY_F9},
            {KEY_F(10), arcade::event::Key::KEY_F10},
            {KEY_F(11), arcade::event::Key::KEY_F11},
            {KEY_F(12), arcade::event::Key::KEY_F12},
            {97, arcade::event::Key::KEY_A},
            {98, arcade::event::Key::KEY_B},
            {99, arcade::event::Key::KEY_C},
            {100, arcade::event::Key::KEY_D},
            {101, arcade::event::Key::KEY_E},
            {102, arcade::event::Key::KEY_F},
            {103, arcade::event::Key::KEY_G},
            {104, arcade::event::Key::KEY_H},
            {105, arcade::event::Key::KEY_I},
            {106, arcade::event::Key::KEY_J},
            {107, arcade::event::Key::KEY_K},
            {108, arcade::event::Key::KEY_L},
            {109, arcade::event::Key::KEY_M},
            {110, arcade::event::Key::KEY_N},
            {111, arcade::event::Key::KEY_O},
            {112, arcade::event::Key::KEY_P},
            {113, arcade::event::Key::KEY_Q},
            {114, arcade::event::Key::KEY_R},
            {115, arcade::event::Key::KEY_S},
            {116, arcade::event::Key::KEY_T},
            {117, arcade::event::Key::KEY_U},
            {118, arcade::event::Key::KEY_V},
            {119, arcade::event::Key::KEY_W},
            {120, arcade::event::Key::KEY_X},
            {121, arcade::event::Key::KEY_Y},
            {122, arcade::event::Key::KEY_Z},
            {48, arcade::event::Key::KEY_0},
            {49, arcade::event::Key::KEY_1},
            {50, arcade::event::Key::KEY_2},
            {51, arcade::event::Key::KEY_3},
            {52, arcade::event::Key::KEY_4},
            {53, arcade::event::Key::KEY_5},
            {54, arcade::event::Key::KEY_6},
            {55, arcade::event::Key::KEY_7},
            {56, arcade::event::Key::KEY_8},
            {57, arcade::event::Key::KEY_9},
        };
    }
}

#endif /* !LIBNCURSES_H_ */