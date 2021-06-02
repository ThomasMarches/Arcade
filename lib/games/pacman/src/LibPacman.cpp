/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibPacman.cpp
*/

#include <stdio.h>

#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/AsciiSprite.hpp"
#include "IEntity.hpp"
#include "LibPacman.hpp"
#include "EventName.hpp"
#include "System.hpp"
#include "PacmanMap.hpp"
#include <iostream>

INIT_LIB_API(LibPacman)

int count_cells(const char *str, char cell)
{
    int count = 0;

    while (str[count] && str[count] == cell)
        count++;
    return count;
}

namespace arcade
{
    namespace lib
    {
        LibPacman::LibPacman() : AGame()
        {
            m_bIsGameover = false;
            m_pScene = nullptr;
        }

        LibPacman::~LibPacman() {}

        void LibPacman::init(IScene &oScene)
        {
            std::cout << "[LibPacman] Init!" << std::endl;
            m_pScene = &oScene;

            for (int y = 0; pacman_map[y]; y++)
            {
                for (int x = 0; pacman_map[y][x]; x++)
                {
                    if (pacman_map[y][x] == '#')
                    {
                        int width = count_cells(&(pacman_map[y][x]), '#');
                        auto &wall = oScene.newEntity("pacman_awall");
                        wall.addComponent(component::create_transform({(float)x, (float)y, 0}));
                        wall.addComponent(component::create_sprite(width, 1, {255, 255, 255, 255}));
                        wall.addComponent(component::create_ascii_sprite(width, 1, '#'));
                        x += width - 1;
                    }
                    else if (pacman_map[y][x] == 'T')
                    {
                        // teleporter
                    }
                    else if (pacman_map[y][x] == 'P')
                    {
                        auto &player = oScene.newEntity("pacman_zplayer");
                        player.addComponent(component::create_transform({(float)x, (float)y, 0}));
                        player.addComponent(component::create_sprite(1, 1, {255, 255, 0, 255}));
                        player.addComponent(component::create_ascii_sprite(1, 1, 'C'));
                    }
                    else if (pacman_map[y][x] == 'G')
                    {
                        // gost area
                    }
                    else if (pacman_map[y][x] == '@')
                    {
                        auto &specialPacgum = oScene.newEntity("pacman_special_pill");
                        specialPacgum.addComponent(component::create_transform({(float)x, (float)y, 0}));
                        specialPacgum.addComponent(component::create_sprite(1, 1, {255, 255, 255, 0}));
                        specialPacgum.addComponent(component::create_ascii_sprite(1, 1, '$'));
                    }
                    else if (pacman_map[y][x] == ' ')
                    {
                        auto &pill = oScene.newEntity("pacman_pill");
                        pill.addComponent(component::create_transform({(float)x, (float)y, 0}));
                        pill.addComponent(component::create_sprite(1, 1, {0, 255, 255, 255}));
                        pill.addComponent(component::create_ascii_sprite(1, 1, '.'));
                    }
                }
            }
        }

        void LibPacman::update(IScene &oScene, float dt)
        {
            if (m_bIsGameover)
                return;
            arcade::component::Transform *transform = nullptr;
            arcade::component::Sprite *sprite = nullptr;

            m_pScene->forEach([&transform, &sprite](IEntity &e) {
                GetComponent(e, transform, sprite);
            },
                              "pacman_zplayer");
            if (transform)
            {
                transform->position.x += m_player_dir.x;
                transform->position.y += m_player_dir.y;
            }
        }

        void LibPacman::end(IScene &oScene)
        {
            oScene.removeEntity("pacman_special_pill");
            oScene.removeEntity("pacman_awall");
            oScene.removeEntity("pacman_zplayer");
            oScene.removeEntity("pacman_pill");
        }

        void LibPacman::onKeyEvent(const event::KeyboardEvent &key)
        {
            if (key.key == arcade::event::Key::KEY_D)
            {
                m_player_dir = Vec2(1, 0);
            }
            else if (key.key == arcade::event::Key::KEY_Q)
            {
                m_player_dir = Vec2(-1, 0);
            }
            else if (key.key == arcade::event::Key::KEY_Z)
            {
                m_player_dir = Vec2(0, -1);
            }
            else if (key.key == arcade::event::Key::KEY_S)
            {
                m_player_dir = Vec2(0, 1);
            }
        }

        void LibPacman::onMouseEvent(const event::MouseEvent &mouse)
        {
        }
    }
}