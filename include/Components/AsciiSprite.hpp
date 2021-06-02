/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** AsciiSprite.hpp header
*/

#ifndef ASCIISPRITE_HPP_PRIVATE
#define ASCIISPRITE_HPP_PRIVATE

#include "Common/component/AsciiSprite.hpp"
#include "IComponent.hpp"
#include <memory>
#include <vector>

namespace arcade
{
    namespace component
    {
        inline AsciiSprite create_ascii_sprite(size_t w, size_t h, char c)
        {
            AsciiSprite Ascii_sprite;
            Ascii_sprite.sprite = std::make_shared<std::vector<char>>(w * h);
            for (auto &pixel : *Ascii_sprite.sprite) {
                pixel = c;
            }
            Ascii_sprite.height = h;
            Ascii_sprite.width = w;
            return Ascii_sprite;
        }
    }
}

#endif /* !ASCIISPRITE_HPP_PRIVATE */