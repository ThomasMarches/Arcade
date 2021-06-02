/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** System.cpp
*/

#include "System.hpp"
#include "Components/Transform.hpp"
#include "Components/Sprite.hpp"
#include "Components/AsciiSprite.hpp"
#include "Event/Event.hpp"
#include "EventName.hpp"

using arcade::component::Transform;
using arcade::component::AsciiSprite;
using arcade::component::Sprite;
using arcade::event::KeyboardEvent;
using arcade::event::MouseEvent;

// void InputOnKeySystem(Event& ev, arcade::IEntity& e)
// {
//     Input* input = nullptr;
//     if (!GetComponent(e, input))
//         return;
//     auto key = ev.GetParam<KeyboardEvent>(AEvent::Input::Keyboard::KeyDown);
//     if (key.key == arcade::event::Key::KEY_D) {
//         input->horizontal = 1;
//         input->vertical = 0;
//     } else if (key.key == arcade::event::Key::KEY_Q) {
//         input->horizontal = -1;
//         input->vertical = 0;
//     } else if (key.key == arcade::event::Key::KEY_Z) {
//         input->vertical = -1;
//         input->horizontal = 0;
//     } else if (key.key == arcade::event::Key::KEY_S) {
//         input->vertical = 1;
//         input->horizontal = 0;
//     }
// }

// void UpdateMoveDataSystem(Event& ev, arcade::IEntity& e)
// {
//     Input* input = nullptr;
//     MoveData* move = nullptr;
//     if (!GetComponent(e, input, move))
//         return;
//     move->m_oDir.x = input->horizontal;
//     move->m_oDir.y = input->vertical;
// }

// void UpdateMovementSystem(Event& ev, arcade::IEntity& e)
// {
//     Transform* transform = nullptr;
//     MoveData* move = nullptr;
//     if (!GetComponent(e, transform, move))
//         return;
//     auto dt = ev.GetParam<float>(Ecs::System::DT);

//     transform->position.x += move->m_oDir.x * move->m_fSpeed * dt;
//     transform->position.y += move->m_oDir.y * move->m_fSpeed * dt;
// }

// void DetectCollisionSystem(Event& ev, arcade::IEntity& e1, const arcade::EntityList& m_vEntities)
// {
//     Transform* t1 = nullptr;
//     BoxCollider* box1 = nullptr;
//     if (!GetComponent(e1, t1, box1))
//         return;
//     box1->m_oPosition = t1->position;
//     if (box1->m_bIsCollide)
//         return;
//     for (int i = 0; i < m_vEntities.size(); ++i) {
//         auto& e2 = m_vEntities[i];
//         Transform* t2 = nullptr;
//         BoxCollider* box2 = nullptr;
//         if (!GetComponent(e1, t2, box2) || box1 == box2)
//             continue;
//         box2->m_oPosition = t2->position;
//         if (box1->isCollide(box2)) {
//             box1->m_bIsCollide = true;
//             box2->m_bIsCollide = true;
//             box1->emit(Collider(e1, e2, box2->m_strTag));
//             box2->emit(Collider(e2, e1, box1->m_strTag));
//         }
//     }
// }

// void ResetCollisionSystem(Event& ev, arcade::IEntity& e)
// {
//     BoxCollider* collider = nullptr;
//     if (!GetComponent(e, collider))
//         return;
//     collider->m_bIsCollide = false;
// }

// void ButtonNavigationSystem(Event& ev, arcade::IEntity& e)
// {
//     Button* button = nullptr;
//     Input* input = nullptr;
//     if (!GetComponent(e, button, input))
//         return;
//     if (button->m_bSelect) {
//         if (input->horizontal > 0 && button->m_pRight) {
//             button->m_pRight->m_bSelect = true;
//             button->m_bSelect = false;
//         } else if (input->horizontal < 0 && button->m_pLeft) {
//             button->m_pLeft->m_bSelect = true;
//             button->m_bSelect = false;
//         }
//         if (input->vertical < 0 && button->m_pUp) {
//             button->m_pUp->m_bSelect = true;
//             button->m_bSelect = false;
//         } else if (input->vertical > 0 && button->m_pDown) {
//             button->m_pDown->m_bSelect = true;
//             button->m_bSelect = false;
//         }
//     }
// }

// void SetButtonColorSystem(Event& ev, arcade::IEntity& e)
// {
//     Button* button = nullptr;
//     Sprite* sprite = nullptr;
//     if (!GetComponent(e, button, sprite))
//         return;
//     if (button->m_bSelect) {
//         set_sprite_color(sprite, button->m_oHightL);
//     } else {
//         set_sprite_color(sprite, button->m_oNormal);
//     }
// }

// void ButtonClickSystem(Event& ev, arcade::IEntity& e)
// {
//     Button* button = nullptr;
//     if (!GetComponent(e, button))
//         return;

//     auto key = ev.GetParam<KeyboardEvent>(AEvent::Input::Keyboard::KeyDown);
//     if (key.key == arcade::event::Key::KEY_SPACE && button->m_bSelect) {
//         button->emit();
//     }
// }