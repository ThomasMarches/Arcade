/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibNCurses.cpp
*/

#include <cmath>
#include "LibNCurses.hpp"
#include "EventName.hpp"
#include "Components/Transform.hpp"
#include "Components/AsciiSprite.hpp"
#include "Components/Text.hpp"
#include "IEntity.hpp"

INIT_LIB_API(LibNCurses)

namespace arcade
{
    namespace lib
    {
        LibNCurses::LibNCurses() : AGraphic()
        {
            m_bQuit = false;
        }

        LibNCurses::~LibNCurses()
        {
            std::cout << "[LibNCurses] Destroy!" << std::endl;
        }

        void LibNCurses::init(IScene &oScene)
        {
            std::cout << "[LibNCurses] Init!" << std::endl;

            initscr();
            raw();
            noecho();
            cbreak();
            curs_set(0);
            // mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
            keypad(stdscr, TRUE);
            nodelay(stdscr, TRUE);
            // mouseinterval(0);
            // std::cout << "\033[?1003h" << std::endl;
        }

        void LibNCurses::update(IScene &oScene, float dt)
        {
            using arcade::event::KeyboardEvent;
            using arcade::event::MouseEvent;

            int ch;
            MouseEvent mouse;
            MEVENT event;

            while ((ch = getch()) != ERR)
            {
                if (ch == 'e')
                {
                    m_bQuit = true;
                    return;
                }

                switch (ch)
                {
                case KEY_END:
                    m_bQuit = true;
                case KEY_RESIZE:
                    break;
                case KEY_MOUSE:
                    if (getmouse(&event) == OK)
                    {
                        mouse.x = event.x;
                        mouse.y = event.y;

                        if (event.bstate & BUTTON1_PRESSED)
                        {
                            mouse.button = MouseEvent::MOUSE_PRIMARY;
                            mouse.action = MouseEvent::PRESSED;
                        }
                        if (event.bstate & BUTTON1_RELEASED)
                        {
                            mouse.button = MouseEvent::MOUSE_PRIMARY;
                            mouse.action = MouseEvent::RELEASED;
                        }
                        if (event.bstate & BUTTON1_CLICKED)
                        {
                            mouse.button = MouseEvent::MOUSE_PRIMARY;
                            mouse.action = MouseEvent::DOWN;
                        }
                        if (event.bstate & BUTTON2_PRESSED)
                        {
                            mouse.button = MouseEvent::MOUSE_AUXILIARY;
                            mouse.action = MouseEvent::PRESSED;
                        }
                        if (event.bstate & BUTTON2_RELEASED)
                        {
                            mouse.button = MouseEvent::MOUSE_AUXILIARY;
                            mouse.action = MouseEvent::RELEASED;
                        }
                        if (event.bstate & BUTTON2_CLICKED)
                        {
                            mouse.button = MouseEvent::MOUSE_AUXILIARY;
                            mouse.action = MouseEvent::DOWN;
                        }
                        if (event.bstate & BUTTON3_PRESSED)
                        {
                            mouse.button = MouseEvent::MOUSE_SECONDARY;
                            mouse.action = MouseEvent::PRESSED;
                        }
                        if (event.bstate & BUTTON3_RELEASED)
                        {
                            mouse.button = MouseEvent::MOUSE_SECONDARY;
                            mouse.action = MouseEvent::RELEASED;
                        }
                        if (event.bstate & BUTTON3_CLICKED)
                        {
                            mouse.button = MouseEvent::MOUSE_SECONDARY;
                            mouse.action = MouseEvent::DOWN;
                        }
                        oScene.pushEvent(mouse);
                    }
                default:
                    auto it = NcursesKeyEventMap.find(ch);
                    if (it == NcursesKeyEventMap.end())
                        break;
                    else
                    {
                        KeyboardEvent key;
                        key.key = NcursesKeyEventMap[ch];
                        key.action = KeyboardEvent::DOWN;
                        oScene.pushEvent(key);
                    }
                    break;
                }
            }
            clear();
            display(oScene);
        }

        void LibNCurses::clear()
        {
            wclear(stdscr);
        }

        void LibNCurses::display(IScene &oScene)
        {
            using arcade::component::AsciiSprite;
            using arcade::component::Text;
            using arcade::component::Transform;

            oScene.forEach([this](arcade::IEntity &e) {
                AsciiSprite *ascii_sprite = nullptr;
                Transform *transform = nullptr;
                if (GetComponent(e, ascii_sprite, transform))
                {
                    if (ascii_sprite->sprite) {
                        for (int i = 0; i < ascii_sprite->sprite->size(); ++i)
                        {
                            int x = i % ascii_sprite->width;
                            int y = floor(i / ascii_sprite->width);
                            mvaddch(transform->position.y + y, transform->position.x + x, ascii_sprite->sprite->at(i));
                        }
                    }
                }
            });
            oScene.forEach([this](arcade::IEntity &e) {
                Text *text = nullptr;
                Transform *transform = nullptr;
                if (GetComponent(e, text, transform))
                {
                    mvprintw(transform->position.y, transform->position.x, text->text.c_str());
                }
            });
            refresh();
        }

        void LibNCurses::end(IScene &oScene)
        {
            endwin();
        }
    }
}