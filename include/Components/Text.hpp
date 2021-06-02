/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Text.hpp header
*/

#ifndef TEXT_HPP_PRIVATE
#define TEXT_HPP_PRIVATE

#include "Common/component/Text.hpp"

namespace arcade
{
    namespace component
    {
        inline Text create_text(const std::string& strText)
        {
            Text text;
            text.text = strText;
            return text;
        }
    }
}

#endif /* !TEXT_HPP_ */