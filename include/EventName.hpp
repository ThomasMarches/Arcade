/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** EventName.hpp header
*/

#ifndef ARCADE_EVENT_HPP
#define ARCADE_EVENT_HPP

#include "Core/Event.hpp"

namespace AEvent {
    const EventId OnStartGame = "Arcade::Event::Engine::OnStartGame"_hash;
    const EventId OnQuitGame = "Arcade::Event::Engine::OnQuitGame"_hash;

    namespace Gfx {
        const EventId OnRender = "Arcade::Event::Engine::Gfx::OnRender"_hash;
    }

    namespace Ecs {
        const EventId OnStart = "Arcade::Event::Engine::Ecs::OnStart"_hash;
        const EventId OnPreUpdate = "Arcade::Event::Engine::Ecs::OnPreUpdate"_hash;
        const EventId OnPostUpdate = "Arcade::Event::Engine::Ecs::OnPostUpdate"_hash;
        const EventId NewFrame = "Arcade::Event::Engine::Ecs::NewFrame"_hash;
    }

    namespace Input {
        namespace Keyboard {
            const EventId OnKey = "Arcade::Event::Engine::Input::Keyboard::OnKey"_hash;
            const EventId OnKeyDown = "Arcade::Event::Engine::Input::Keyboard::OnKeyDown"_hash;
            const EventId OnKeyUp = "Arcade::Event::Engine::Input::Keyboard::OnKeyUp"_hash;

            const ParamId Key = "Arcade::Event::Engine::Input::Keyboard::Key"_hash;
            const ParamId KeyDown = "Arcade::Event::Engine::Input::Keyboard::KeyDown"_hash;
            const ParamId KeyUp = "Arcade::Event::Engine::Input::Keyboard::KeyUp"_hash;
        }

        namespace Mouse {
            const EventId OnMouse = "Arcade::Event::Engine::Input::Mouse::OnMouse"_hash;
            const EventId OnMouseDown = "Arcade::Event::Engine::Input::Mouse::OnMouseDown"_hash;
            const EventId OnMouseUp = "Arcade::Event::Engine::Input::Mouse::OnMouseUp"_hash;
            const EventId OnMouseMoved = "Arcade::Event::Engine::Input::Mouse::OnMouseMoved"_hash;

            const ParamId MouseButton = "Arcade::Event::Engine::Input::Mouse::MouseButton"_hash;
            const ParamId MouseButtonDown = "Arcade::Event::Engine::Input::Mouse::MouseButtonDown"_hash;
            const ParamId MouseButtonUp = "Arcade::Event::Engine::Input::Mouse::MouseButtonUp"_hash;
            const ParamId MouseMoved = "Arcade::Event::Engine::Input::Mouse::MouseMoved"_hash;
        }
    }
}

#endif