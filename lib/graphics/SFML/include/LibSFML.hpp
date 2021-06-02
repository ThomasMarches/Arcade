/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibSFML.hpp header
*/

#ifndef LIBSFML_H_
#define LIBSFML_H_

#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#include "api.h"
#include "IGraphic.hpp"
#include "AGraphic.hpp"
#include "Core/EventManager.hpp"
#include "Components/Sprite.hpp"

namespace arcade
{
    namespace lib
    {
        class LibSFML : public AGraphic
        {
        public:
            static const library_info_t INFO;
            static std::unordered_map<sf::Keyboard::Key, arcade::event::Key> SFMLKeyEventMap;

            LibSFML();
            ~LibSFML();
            void init(IScene &oScene) override;
            void update(IScene &oScene, float dt) override;
            void end(IScene &oScene) override;

            void clear();
            void display(IScene &oScene);
            bool mousePressed(arcade::event::MouseEvent& mouse);

        private:
            sf::RenderWindow m_oWindow;
            sf::Event m_oEvent;

            sf::Font m_font;

            bool m_bMouseLeft, m_bWasMouseLeft;
            bool m_bMouseRight, m_bWasMouseRight;
            bool m_bMouseMiddle, m_bWasMouseMiddle;
        };

        static sf::Color getColor(arcade::Color color);

        const library_info_t LibSFML::INFO = {
            library_info::GRAPHIC,
            "SFML",
            BUILD_TIME,
            "SFML: graphical rendering",
        };

        std::unordered_map<sf::Keyboard::Key, arcade::event::Key> LibSFML::SFMLKeyEventMap = {
            {sf::Keyboard::Escape, arcade::event::Key::KEY_ESCAPE},
            {sf::Keyboard::Backspace, arcade::event::Key::KEY_BACK_SPACE},
            {sf::Keyboard::Left, arcade::event::Key::KEY_ARROW_LEFT},
            {sf::Keyboard::Right, arcade::event::Key::KEY_ARROW_RIGHT},
            {sf::Keyboard::Up, arcade::event::Key::KEY_ARROW_UP},
            {sf::Keyboard::Down, arcade::event::Key::KEY_ARROW_DOWN},
            {sf::Keyboard::LShift, arcade::event::Key::KEY_SHIFT_LEFT},
            {sf::Keyboard::RShift, arcade::event::Key::KEY_SHIFT_RIGHT},
            {sf::Keyboard::LControl, arcade::event::Key::KEY_CTRL_LEFT},
            {sf::Keyboard::RControl, arcade::event::Key::KEY_CTRL_RIGHT},
            {sf::Keyboard::LAlt, arcade::event::Key::KEY_ALT_LEFT},
            {sf::Keyboard::RAlt, arcade::event::Key::KEY_ALT_RIGHT},
            {sf::Keyboard::PageUp, arcade::event::Key::KEY_PAGE_UP},
            {sf::Keyboard::PageDown, arcade::event::Key::KEY_PAGE_DOWN},
            {sf::Keyboard::Delete, arcade::event::Key::KEY_DELETE},
            {sf::Keyboard::Insert, arcade::event::Key::KEY_INSERT},
            {sf::Keyboard::End, arcade::event::Key::KEY_END_FILE},
            {sf::Keyboard::Space, arcade::event::Key::KEY_SPACE},
            {sf::Keyboard::F1, arcade::event::Key::KEY_F1},
            {sf::Keyboard::F2, arcade::event::Key::KEY_F2},
            {sf::Keyboard::F3, arcade::event::Key::KEY_F3},
            {sf::Keyboard::F4, arcade::event::Key::KEY_F4},
            {sf::Keyboard::F5, arcade::event::Key::KEY_F5},
            {sf::Keyboard::F6, arcade::event::Key::KEY_F6},
            {sf::Keyboard::F7, arcade::event::Key::KEY_F7},
            {sf::Keyboard::F8, arcade::event::Key::KEY_F8},
            {sf::Keyboard::F9, arcade::event::Key::KEY_F9},
            {sf::Keyboard::F10, arcade::event::Key::KEY_F10},
            {sf::Keyboard::F11, arcade::event::Key::KEY_F11},
            {sf::Keyboard::F12, arcade::event::Key::KEY_F12},
            {sf::Keyboard::A, arcade::event::Key::KEY_A},
            {sf::Keyboard::B, arcade::event::Key::KEY_B},
            {sf::Keyboard::C, arcade::event::Key::KEY_C},
            {sf::Keyboard::D, arcade::event::Key::KEY_D},
            {sf::Keyboard::E, arcade::event::Key::KEY_E},
            {sf::Keyboard::F, arcade::event::Key::KEY_F},
            {sf::Keyboard::G, arcade::event::Key::KEY_G},
            {sf::Keyboard::H, arcade::event::Key::KEY_H},
            {sf::Keyboard::I, arcade::event::Key::KEY_I},
            {sf::Keyboard::J, arcade::event::Key::KEY_J},
            {sf::Keyboard::K, arcade::event::Key::KEY_K},
            {sf::Keyboard::L, arcade::event::Key::KEY_L},
            {sf::Keyboard::M, arcade::event::Key::KEY_M},
            {sf::Keyboard::N, arcade::event::Key::KEY_N},
            {sf::Keyboard::O, arcade::event::Key::KEY_O},
            {sf::Keyboard::P, arcade::event::Key::KEY_P},
            {sf::Keyboard::Q, arcade::event::Key::KEY_Q},
            {sf::Keyboard::R, arcade::event::Key::KEY_R},
            {sf::Keyboard::S, arcade::event::Key::KEY_S},
            {sf::Keyboard::T, arcade::event::Key::KEY_T},
            {sf::Keyboard::U, arcade::event::Key::KEY_U},
            {sf::Keyboard::V, arcade::event::Key::KEY_V},
            {sf::Keyboard::W, arcade::event::Key::KEY_W},
            {sf::Keyboard::X, arcade::event::Key::KEY_X},
            {sf::Keyboard::Y, arcade::event::Key::KEY_Y},
            {sf::Keyboard::Z, arcade::event::Key::KEY_Z},
            {sf::Keyboard::Num1, arcade::event::Key::KEY_1},
            {sf::Keyboard::Num2, arcade::event::Key::KEY_2},
            {sf::Keyboard::Num3, arcade::event::Key::KEY_3},
            {sf::Keyboard::Num4, arcade::event::Key::KEY_4},
            {sf::Keyboard::Num5, arcade::event::Key::KEY_5},
            {sf::Keyboard::Num6, arcade::event::Key::KEY_6},
            {sf::Keyboard::Num7, arcade::event::Key::KEY_7},
            {sf::Keyboard::Num8, arcade::event::Key::KEY_8},
            {sf::Keyboard::Num9, arcade::event::Key::KEY_9},
            {sf::Keyboard::Num0, arcade::event::Key::KEY_0},
        };
    }
}

#endif /* !LIBSFML_H_ */