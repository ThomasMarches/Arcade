/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Transform.hpp header
*/

#ifndef TRANSFORM_HPP_PRIVATE
#define TRANSFORM_HPP_PRIVATE

#include "Common/component/Transform.hpp"
#include "Library/AGame.hpp"

namespace arcade
{
    namespace component
    {
        inline Transform create_transform(math::Vector3 pos,
                                          math::Vector3 rot = math::Vector3{0, 0, 0},
                                          math::Vector3 scale = math::Vector3{1, 1, 1})
        {
            Transform t;
            t.position = pos;
            t.rotation = rot;
            t.scale = scale;
            return t;
        }
    }
}

#endif /* !TRANSFORM_HPP_PRIVATE */