/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** AGame.hpp header
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"
#include "Core/EventManager.hpp"

namespace arcade {

namespace lib {

    class AGame : public IGame {
    public:
        explicit AGame()
        {
        }
        virtual ~AGame() = default;

    protected:
    private:
    };

}

}

#endif /* !IGAME_HPP_ */