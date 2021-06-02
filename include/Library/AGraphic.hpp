/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** AGraphic.hpp header
*/

#ifndef AGRAPHIC_HPP_
#define AGRAPHIC_HPP_

#include "IGraphic.hpp"

namespace arcade {
namespace lib {

    class AGraphic : public IGraphic {
    public:
        explicit AGraphic()
        {
        }
        virtual ~AGraphic() = default;

        bool quitRequested() const override { return m_bQuit; };

    protected:
        bool m_bQuit;
    private:
    };

}
}

#endif /* !AGRAPHIC_HPP_ */