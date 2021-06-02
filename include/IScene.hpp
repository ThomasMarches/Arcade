/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** IScene.hpp header
*/

#ifndef ISCENE_HPP_PRIVATE
#define ISCENE_HPP_PRIVATE

#include <memory>
#include <unordered_map>
#include "Common/IScene.hpp"

namespace arcade
{
    using EntityList = std::vector<std::reference_wrapper<IEntity>>;
    using EntityMap = std::unordered_map<std::string, std::vector<std::unique_ptr<IEntity>>>;
}

#endif /* !ISCENE_HPP_PRIVATE */