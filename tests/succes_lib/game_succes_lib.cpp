/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** game_succes_lib.cpp
*/

#include <stdio.h>
#include "api.h"
#include "IScene.hpp"
#include "IGame.hpp"

class GameSuccessLib : public arcade::lib::IGame
{
    public:
    GameSuccessLib() { }
    ~GameSuccessLib() { }
    virtual void init(arcade::IScene& oWorld) override
    {
        printf("[GameSuccessLib] Init!\n");
    }

    void update(arcade::IScene& scene, float dt) override { }

    void end(arcade::IScene& oWorld) override { }

    virtual void onKeyEvent(const arcade::event::KeyboardEvent& key) override
    {   
    }

    virtual void onMouseEvent(const arcade::event::MouseEvent& mouse) override
    {
    }
};

#ifdef __cplusplus
extern "C" {
#endif

void *library_create()
{
    printf("[GameSuccessLib] Loading GameSuccessLib library ...\n");
    return new GameSuccessLib();
}

void library_delete(void *library)
{
    printf("[GameSuccessLib] GameSuccessLib closing ...\n");
    delete static_cast<GameSuccessLib*>(library);
}

library_info_t library_get_data()
{
    printf("[GameSuccessLib] Meta for GameSuccessLib!\n");
    library_info_t info;
    info.type = library_info::GAME;
    info.name = nullptr;
    return info;
}

#ifdef __cplusplus
}
#endif