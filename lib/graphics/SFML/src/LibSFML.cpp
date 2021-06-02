/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** LibSFML.cpp
*/

#include "LibSFML.hpp"
#include "math.h"
#include "EventName.hpp"
#include "Components/IComponent.hpp"
#include "Components/Transform.hpp"
#include "Components/Text.hpp"
#include "Components/AsciiSprite.hpp"
#include "Exceptions/InitException.hpp"
#include "IEntity.hpp"
#include "arial.ttf.h"

INIT_LIB_API(LibSFML)

namespace arcade
{
    namespace lib
    {
        LibSFML::LibSFML() : AGraphic()
        {
            m_bQuit = false;
            m_bMouseLeft = false;
            m_bWasMouseLeft = false;
            m_bMouseRight = false;
            m_bWasMouseRight = false;
            m_bMouseMiddle = false;
            m_bWasMouseMiddle = false;
        }

        LibSFML::~LibSFML()
        {
        }

        void LibSFML::init(IScene &oScene)
        {
            std::cout << "[LibSFML] Init!" << std::endl;

            m_oWindow.create({1280, 720}, "Arcade - LibSFML");
            m_oWindow.setKeyRepeatEnabled(false);

            if (!m_font.loadFromMemory(ARIALTTF, ARIALTTF_LENGTH))
                throw InitException("LibSFML: Can not load arial font");
        }

        void LibSFML::update(IScene &oScene, float dt)
        {
            using arcade::event::KeyboardEvent;
            using arcade::event::MouseEvent;
            MouseEvent mouse;

            while (m_oWindow.pollEvent(m_oEvent))
            {
                switch (m_oEvent.type)
                {
                case sf::Event::Closed:
                    m_bQuit = true;
                    break;

                case sf::Event::Resized:
                {
                    sf::FloatRect visibleArea(0, 0, m_oEvent.size.width, m_oEvent.size.height);
                    m_oWindow.setView(sf::View(visibleArea));
                    break;
                }

                case sf::Event::MouseButtonPressed:
                {
                    mouse.x = m_oEvent.mouseButton.x;
                    mouse.y = m_oEvent.mouseButton.y;
                    mouse.action = MouseEvent::DOWN;

                    if (m_oEvent.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        mouse.button = MouseEvent::MOUSE_PRIMARY;
                        oScene.pushEvent(mouse);
                    }
                    else if (m_oEvent.mouseButton.button == sf::Mouse::Button::Right)
                    {
                        mouse.button = MouseEvent::MOUSE_SECONDARY;
                        oScene.pushEvent(mouse);
                    }
                    else if (m_oEvent.mouseButton.button == sf::Mouse::Button::Middle)
                    {
                        mouse.button = MouseEvent::MOUSE_AUXILIARY;
                        oScene.pushEvent(mouse);
                    }
                    break;
                }

                case sf::Event::MouseButtonReleased:
                {
                    mouse.x = m_oEvent.mouseButton.x;
                    mouse.y = m_oEvent.mouseButton.y;
                    mouse.action = MouseEvent::RELEASED;

                    if (m_oEvent.mouseButton.button == sf::Mouse::Button::Left)
                    {
                        mouse.button = MouseEvent::MOUSE_PRIMARY;
                        oScene.pushEvent(mouse);
                    }
                    else if (m_oEvent.mouseButton.button == sf::Mouse::Button::Right)
                    {
                        mouse.button = MouseEvent::MOUSE_SECONDARY;
                        oScene.pushEvent(mouse);
                    }
                    else if (m_oEvent.mouseButton.button == sf::Mouse::Button::Middle)
                    {
                        mouse.button = MouseEvent::MOUSE_AUXILIARY;
                        oScene.pushEvent(mouse);
                    }
                    break;
                }

                    // case sf::Event::MouseMoved:
                    // {
                    //     break;
                    // }

                case sf::Event::KeyReleased:
                {
                    KeyboardEvent key;
                    key.key = SFMLKeyEventMap[m_oEvent.key.code];
                    key.action = KeyboardEvent::RELEASED;
                    oScene.pushEvent(key);
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    KeyboardEvent key;
                    key.key = SFMLKeyEventMap[m_oEvent.key.code];
                    key.action = KeyboardEvent::DOWN;
                    oScene.pushEvent(key);
                    break;
                }

                default:
                    break;
                }
            }

            if (mousePressed(mouse))
                oScene.pushEvent(mouse);

            clear();
            display(oScene);
        }

        void LibSFML::clear()
        {
            m_oWindow.clear();
        }

        void LibSFML::display(IScene &oScene)
        {
            using arcade::component::AsciiSprite;
            using arcade::component::Sprite;
            using arcade::component::Text;
            using arcade::component::Transform;

            oScene.forEach([this](arcade::IEntity &e) {
                Sprite *sprite = nullptr;
                AsciiSprite *asciiSprite = nullptr;
                Transform *transform = nullptr;
                if (GetComponent(e, sprite, transform))
                {
                    sf::Uint8 pixels[sprite->width * sprite->height * 4];

                    for (int i = 0; i < sprite->pixels->size(); ++i)
                    {
                        Color &color = sprite->pixels->at(i);
                        pixels[i * 4] = color.r;
                        pixels[i * 4 + 1] = color.g;
                        pixels[i * 4 + 2] = color.b;
                        pixels[i * 4 + 3] = color.a;
                    }
                    sf::Texture sfTexture;
                    sfTexture.create(sprite->width, sprite->height);
                    sfTexture.update(pixels);
                    sf::Sprite sfSprite(sfTexture);
                    sfSprite.setPosition(sf::Vector2f(transform->position.x * CELL_SIZE, transform->position.y * CELL_SIZE));
                    if (GetComponent(e, asciiSprite))
                    {
                        sfSprite.setScale(sf::Vector2f(
                            (float)(CELL_SIZE * asciiSprite->width) / (float)(sprite->width),
                            (float)(CELL_SIZE * asciiSprite->height) / (float)sprite->height));
                    }
                    m_oWindow.draw(sfSprite);
                }
            });
            oScene.forEach([this](arcade::IEntity &e) {
                Text *text = nullptr;
                Transform *transform = nullptr;
                if (GetComponent(e, text, transform))
                {
                    std::cout << transform->position.x << std::endl;
                    sf::Text sfText;
                    sfText.setFont(m_font);
                    sfText.setString(text->text.c_str());
                    sfText.setPosition(sf::Vector2f{transform->position.x * CELL_SIZE, transform->position.y * CELL_SIZE});
                    sfText.setCharacterSize(CELL_SIZE);
                    sfText.setFillColor(sf::Color::White);
                    m_oWindow.draw(sfText);
                }
            });
            m_oWindow.display();
        }

        bool LibSFML::mousePressed(arcade::event::MouseEvent &mouse)
        {
            using arcade::event::MouseEvent;
            bool ret = false;
            if (!m_bWasMouseLeft && m_bMouseLeft)
            {
                mouse.action = MouseEvent::PRESSED;
                mouse.button = MouseEvent::MOUSE_PRIMARY;
                ret = true;
            }
            if (!m_bWasMouseRight && m_bMouseRight)
            {
                mouse.action = MouseEvent::PRESSED;
                mouse.button = MouseEvent::MOUSE_SECONDARY;
                ret = true;
            }
            if (!m_bWasMouseMiddle && m_bMouseMiddle)
            {
                mouse.action = MouseEvent::PRESSED;
                mouse.button = MouseEvent::MOUSE_AUXILIARY;
                ret = true;
            }
            m_bWasMouseLeft = m_bMouseLeft;
            m_bWasMouseRight = m_bMouseRight;
            m_bWasMouseMiddle = m_bMouseMiddle;
            return ret;
        }

        void LibSFML::end(IScene &oScene)
        {
            m_oWindow.close();
        }

        sf::Color getColor(arcade::Color color)
        {
            return sf::Color(color.r,
                             color.g,
                             color.b,
                             color.a);
        }
    }
}