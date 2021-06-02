/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibNibbler.cpp
*/

#include <stdio.h>
#include <cstdlib>

#include "LibNibbler.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/AsciiSprite.hpp"
#include "Components/Text.hpp"
#include "IEntity.hpp"

INIT_LIB_API(LibNibbler)

namespace arcade
{
    namespace lib
    {
        LibNibbler::LibNibbler() : AGame()
        {
            m_pScene = nullptr;
            m_fSpeed = 50;
            m_bIsGameover = false;
        }

        LibNibbler::~LibNibbler()
        {
            // end(*m_pScene);
            m_pScene = nullptr;
            std::cout << "[LibNibbler] Destroy!" << std::endl;
        }

        void LibNibbler::init(IScene &oScene)
        {
            m_pScene = &oScene;
            printf("[LibNibbler] Init!\n");
            createGameBox(oScene, 13);

            // CREATION PLAYER
            auto &player = oScene.newEntity("nibbler_player");
            player.addComponent(component::create_transform({5, 5, 0}));
            player.addComponent(component::create_ascii_sprite(1, 1, 'C'));
            player.addComponent(component::create_sprite({255, 0, 255, 0}));

            auto &gum1 = oScene.newEntity("nibbler_gum");
            gum1.addComponent(component::create_transform({8, 10, 0}));
            gum1.addComponent(component::create_ascii_sprite(1, 1, 'o'));
            gum1.addComponent(component::create_sprite({255, 255, 0, 0}));
        }

        void LibNibbler::update(IScene &oScene, float dt)
        {
            if (m_bIsGameover)
                return;
            static int th = 0;
            m_fDt = dt;
            m_pScene->forEach([&](IEntity &player) {
                arcade::component::Transform *transform = nullptr;
                arcade::component::AsciiSprite *sprite = nullptr;
                if (GetComponent(player, transform, sprite))
                {
                    transform->position.x += m_player_dir.x;
                    transform->position.y += m_player_dir.y;
                    float px = transform->position.x;
                    float py = transform->position.y;
                    m_pScene->forEach([&](IEntity &gum) {
                        arcade::component::Transform *t2 = nullptr;
                        arcade::component::Sprite *s2 = nullptr;
                        if (GetComponent(gum, t2, s2))
                        {
                            if (px == t2->position.x && py == t2->position.y)
                            {
                                oScene.removeEntity(gum);

                                int rand_x = (rand() % 11) + 1;
                                int rand_y = (rand() % 11) + 1;

                                auto &gum = oScene.newEntity("nibbler_gum");
                                gum.addComponent(component::create_transform({static_cast<float>(rand_x),
                                                                              static_cast<float>(rand_y), 0}));
                                gum.addComponent(component::create_ascii_sprite(1, 1, 'o'));
                                gum.addComponent(component::create_sprite(.8f, .8f, {255, 255, 0, 0}));

                                oScene.addScore(100);
                            }
                        }
                    },
                                      "nibbler_gum");

                    m_pScene->forEach([&](IEntity &e) {
                        arcade::component::Transform *t2 = nullptr;
                        arcade::component::AsciiSprite *as2 = nullptr;
                        if (GetComponent(e, t2, as2))
                        {
                            if (transform->position.x + sprite->width < t2->position.x ||
                                transform->position.x > t2->position.x + as2->width ||
                                transform->position.y + sprite->height < t2->position.y ||
                                transform->position.y > t2->position.y + as2->height)
                                return;
                            m_bIsGameover = true;
                            std::cout << "GameOver" << std::endl;
                            auto &gameOver = oScene.newEntity("gameover");
                            gameOver.addComponent(component::create_transform({16, 5, -1}));
                            gameOver.addComponent(component::create_text("GAME OVER"));
                            auto &gameOver1 = oScene.newEntity("gameover");
                            gameOver1.addComponent(component::create_transform({13, 6, -1}));
                            gameOver1.addComponent(component::create_text("Press F5 to reload the game"));
                        }
                    },
                                      "nibbler_gamebox");
                }
            },
                              "nibbler_player");
        }

        void LibNibbler::createGameBox(IScene &oScene, int gameboxSize)
        {
            auto &gamebox1 = oScene.newEntity("nibbler_gamebox");
            gamebox1.addComponent(component::create_transform({0, 0, -1}));
            gamebox1.addComponent(component::create_ascii_sprite(1, gameboxSize, '#'));
            gamebox1.addComponent(component::create_sprite(1, gameboxSize, {255, 255, 255, 255}));
            auto &gamebox2 = oScene.newEntity("nibbler_gamebox");
            gamebox2.addComponent(component::create_transform({float(gameboxSize) - 1.0f, 0, -1}));
            gamebox2.addComponent(component::create_ascii_sprite(1, gameboxSize, '#'));
            gamebox2.addComponent(component::create_sprite(1, gameboxSize, {255, 255, 255, 255}));
            auto &gamebox3 = oScene.newEntity("nibbler_gamebox");
            gamebox3.addComponent(component::create_transform({0, 0, -1}));
            gamebox3.addComponent(component::create_ascii_sprite(float(gameboxSize) - 1.0f, 1, '#'));
            gamebox3.addComponent(component::create_sprite(gameboxSize, 1, {255, 255, 255, 255}));
            auto &gamebox4 = oScene.newEntity("nibbler_gamebox");
            gamebox4.addComponent(component::create_transform({0, float(gameboxSize) - 1.0f, -1}));
            gamebox4.addComponent(component::create_ascii_sprite(gameboxSize, 1, '#'));
            gamebox4.addComponent(component::create_sprite(gameboxSize, 1, {255, 255, 255, 255}));
        }

        void LibNibbler::end(IScene &oScene)
        {
            oScene.removeEntity("nibbler_player");
            oScene.removeEntity("nibbler_gamebox");
            oScene.removeEntity("nibbler_gum");
            oScene.removeEntity("gameover");
        }

        void LibNibbler::onKeyEvent(const event::KeyboardEvent &key)
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

        void LibNibbler::onMouseEvent(const event::MouseEvent &mouse)
        {
        }
    }
}