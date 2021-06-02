/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibMenu.cpp
*/

#include <stdio.h>

#include "LibMenu.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/AsciiSprite.hpp"
#include "Components/Text.hpp"
#include "EventName.hpp"
#include "IEntity.hpp"
#include "System.hpp"

INIT_LIB_API(LibMenu)

// // Fonction de test de collision
// void onCollidePlayer(const Collider& c)
// {
//     static int i = 0;
//     if (c.CompareTag("Box"))
//         std::cout << "Is Collide with Box!! " << i++ << std::endl;
// }

// // Fonction de test de collision
// void onCollideBox(const Collider& c)
// {
//     static int i = 0;
//     if (c.CompareTag("Player"))
//         std::cout << "Is Collide with Player!!" << i++  << std::endl;
// }

// void onGamePlusButton(void* data)
// {
//     using arcade::IScene;
//     using arcade::event::KeyboardEvent;
//     using arcade::event::Key;
//     IScene* pScene = static_cast<IScene*>(data);
//     KeyboardEvent key;
//     key.key = Key::KEY_F10;
//     key.action = KeyboardEvent::PRESSED;
//     pScene->pushEvent(key);
//     std::cout << "Game++!!" << std::endl;
// }

// void onGameMoinsButton(void* data)
// {
//     using arcade::IScene;
//     using arcade::event::KeyboardEvent;
//     using arcade::event::Key;
//     IScene* pScene = static_cast<IScene*>(data);
//     KeyboardEvent key;
//     key.key = Key::KEY_F9;
//     key.action = KeyboardEvent::PRESSED;
//     pScene->pushEvent(key);
//     std::cout << "Game--!!" << std::endl;
// }

// void onPlayButton(void* data)
// {
//     using arcade::IScene;
//     using arcade::event::KeyboardEvent;
//     using arcade::event::Key;
//     IScene* pScene = static_cast<IScene*>(data);
//     KeyboardEvent key;
//     key.key = Key::KEY_F11;
//     key.action = KeyboardEvent::PRESSED;
//     pScene->pushEvent(key);
//     std::cout << "Play!!" << std::endl;
// }

namespace arcade {
    namespace lib {
        LibMenu::LibMenu() : AGame()
        {
        }

        LibMenu::~LibMenu() {}

        void LibMenu::init(IScene& oScene)
        {
            std::cout << "[LibMenu] Init!" << std::endl;

            // auto pKeyUpSys = m_pSystemManager->CreateSystem(oScene, *m_pEventManager);
            // pKeyUpSys->kind(AEvent::Input::Keyboard::OnKeyUp, [pKeyUpSys](IEntity& e) {

            //     if (!HasComponent<Input>(e))
            //         return;

            //     auto key = pKeyUpSys->getEvent().GetParam<event::KeyboardEvent>(AEvent::Input::Keyboard::KeyUp);
            //     Input* input = GetComponent<Input>(e);
            //     if (key.key == arcade::event::Key::KEY_D) {
            //         input->horizontal = 0;
            //     } else if (key.key == arcade::event::Key::KEY_Q) {
            //         input->horizontal = 0;
            //     } else if (key.key == arcade::event::Key::KEY_Z) {
            //         input->vertical = 0;
            //     } else if (key.key == arcade::event::Key::KEY_S) {
            //         input->vertical = 0;
            //     }
            // });

            // m_pSystemManager->CreateSystem(oScene, *m_pEventManager)
            //     ->kind(AEvent::Input::Keyboard::OnKeyDown, InputOnKeySystem);
            // m_pSystemManager->CreateSystem(oScene, *m_pEventManager)
            //     ->kind(AEvent::Ecs::OnPreUpdate, ButtonNavigationSystem);
            // m_pSystemManager->CreateSystem(oScene, *m_pEventManager)
            //     ->kind(AEvent::Ecs::OnPostUpdate, SetButtonColorSystem);
            // m_pSystemManager->CreateSystem(oScene, *m_pEventManager)
            //     ->kind(AEvent::Input::Keyboard::OnKeyDown, ButtonClickSystem);
            // m_pSystemManager->CreateSystem(oScene, *m_pEventManager)
            //     ->kind(AEvent::Ecs::OnStart, [](Event& ev, arcade::IEntity& e) {
            //         arcade::component::Transform* pTransform = nullptr;
            //         if (GetComponent(e, pTransform)) {
            //             pTransform->position.x *= CELL_SIZE;
            //             pTransform->position.y *= CELL_SIZE;
            //         }
            // });

            // auto& gamePlus = oScene.newEntity();
            // gamePlus.addComponent(component::create_transform({27, 18, 0}));
            // gamePlus.addComponent(component::create_sprite(3, 1, {255, 255, 255, 255}));
            // // gamePlus.addComponent(Input());
            // // gamePlus.addComponent(Button(onGameMoinsButton, &oScene, true));

            // auto& gameMoins = oScene.newEntity();
            // gameMoins.addComponent(component::create_transform({33, 18, 0}));
            // gameMoins.addComponent(component::create_sprite(3, 1, {255, 255, 255, 255}));
            // // // gameMoins.addComponent(component::create_text("Lol"));
            // // gameMoins.addComponent(Input());
            // // gameMoins.addComponent(Button(onGamePlusButton, &oScene));

            // // auto& graphicPlus = oScene.newEntity();
            // // graphicPlus.addComponent(component::create_transform({400, 720/2, 0}));
            // // graphicPlus.addComponent(component::create_sprite(120, 50, {255, 255, 255, 255}));
            // // graphicPlus.addComponent(Input());
            // // graphicPlus.addComponent(Button(onGameMoinsButton, &oScene, true));

            // // auto& graphicMoins = oScene.newEntity();
            // // graphicMoins.addComponent(component::create_transform({600, 720/2, 0}));
            // // graphicMoins.addComponent(component::create_sprite(120, 50, {255, 255, 255, 255}));
            // // graphicMoins.addComponent(Input());
            // // graphicMoins.addComponent(Button(onGamePlusButton, &oScene));

            // auto& playBtn = oScene.newEntity();
            // playBtn.addComponent(component::create_transform({30, 20, 0}));
            // playBtn.addComponent(component::create_sprite(3, 1, {255, 255, 255, 255}));
            // // playBtn.addComponent(Input());
            // // playBtn.addComponent(Button(onPlayButton, &oScene));

            // // Button* bGamePlus = GetComponent<Button>(gamePlus);
            // Button* bGameMoins = GetComponent<Button>(gameMoins);
            // // Button* bGraphicPlus = GetComponent<Button>(graphicPlus);
            // // Button* bGraphicMoins = GetComponent<Button>(graphicMoins);
            // Button* bPlay = GetComponent<Button>(playBtn);
            // bGamePlus->setRight(bGameMoins);
            // bGameMoins->setLeft(bGamePlus);
            // bGameMoins->setDown(bPlay);
            // bPlay->setUp(bGamePlus);
            // m_pEventManager->SendEvent(AEvent::Ecs::OnStart);
        }

        void LibMenu::update(IScene &oScene, float dt)
        {
            // Event ev(Ecs::System::OnUpdate);
            // ev.SetParam(Ecs::System::DT, dt);
            // m_pEventManager->SendEvent(AEvent::Ecs::OnPreUpdate);
            // m_pEventManager->SendEvent(ev);
            // m_pEventManager->SendEvent(AEvent::Ecs::OnPostUpdate);
            // m_pEventManager->SendEvent(AEvent::Ecs::NewFrame);
        }

        void LibMenu::end(IScene &oScene)
        {
            oScene.removeEntity("");
            // m_pSystemManager->clear();
            // m_pEventManager->clear();
        }

        void LibMenu::onKeyEvent(const event::KeyboardEvent& key)
        {
            Event ev(-1);
            if (key.action == event::KeyboardEvent::PRESSED) {
                ev.SetType(AEvent::Input::Keyboard::OnKeyDown);
                ev.SetParam(AEvent::Input::Keyboard::KeyDown, const_cast<event::KeyboardEvent&>(key));
                // m_pEventManager->SendEvent(ev);
            } else if (key.action == event::KeyboardEvent::RELEASED) {
                ev.SetType(AEvent::Input::Keyboard::OnKeyUp);
                ev.SetParam(AEvent::Input::Keyboard::KeyUp, const_cast<event::KeyboardEvent&>(key));
                // m_pEventManager->SendEvent(ev);
            }
        }

        void LibMenu::onMouseEvent(const event::MouseEvent& mouse)
        {
        }
    }
}