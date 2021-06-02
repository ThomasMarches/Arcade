/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Sprite.hpp header
*/

#ifndef SPRITE_HPP_PRIVATE
#define SPRITE_HPP_PRIVATE

#include "Common/component/Sprite.hpp"
#include "Library/AGame.hpp"

namespace arcade
{
    namespace component
    {

        inline Sprite create_sprite(float w, float h, Color c)
        {
            Sprite sprite;
            std::vector<Color> v((w * CELL_SIZE) * (h * CELL_SIZE));
            for (auto& pixel : v)
            {
                pixel = c;
            }
            sprite.pixels = std::make_shared<std::vector<Color>>(std::vector<Color>(v));
            sprite.height = h * CELL_SIZE;
            sprite.width = w * CELL_SIZE;
            return sprite;
        }

        inline Sprite create_sprite(Color c)
        {
            Sprite sprite;
            std::vector<Color> v(CELL_SIZE * CELL_SIZE);
            for (auto& pixel : v)
            {
                pixel = c;
            }
            sprite.pixels = std::make_shared<std::vector<Color>>(std::vector<Color>(v));
            sprite.height = CELL_SIZE;
            sprite.width = CELL_SIZE;
            return sprite;
        }

        inline void set_sprite_color(Sprite *sprite, Color c)
        {
            for (auto &pixel : *sprite->pixels)
            {
                pixel = c;
            }
        }
    }
}

#endif /* !SPRITE_HPP_PRIVATE */