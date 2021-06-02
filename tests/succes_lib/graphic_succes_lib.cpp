/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** graphic_succes_lib.cpp
*/

#include <stdio.h>
#include "api.h"
#include "IGraphic.hpp"

class GraphicSuccessLib : public arcade::lib::IGraphic
{
    public:
    GraphicSuccessLib() { }
    ~GraphicSuccessLib() { }
    virtual void init(arcade::IScene& oWorld) override
    {
        printf("[GraphicSuccessLib] Init!\n");
    }

    void update(arcade::IScene& scene, float dt) override { }

    void end(arcade::IScene& oWorld) override { }

    virtual bool quitRequested() const
    {
        return false;
    }
};

#ifdef __cplusplus
extern "C" {
#endif

void *library_create()
{
    printf("[GraphicSuccessLib] Loading GraphicSuccessLib library ...\n");
    return new GraphicSuccessLib();
}

void library_delete(void *library)
{
    printf("[GraphicSuccessLib] GraphicSuccessLib closing ...\n");
    delete static_cast<GraphicSuccessLib*>(library);
}

library_info_t library_get_data()
{
    printf("[GraphicSuccessLib] Meta for GraphicSuccessLib!\n");
    library_info_t info;
    info.type = library_info::GRAPHIC;
    info.name = nullptr;
    return info;
}

#ifdef __cplusplus
}
#endif