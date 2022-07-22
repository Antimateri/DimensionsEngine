#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/renderer.h"

class mainWindow{
private:
    SDL_Renderer *renderer;
	SDL_Window *window;

public:

    Renderer _render;

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BLOCKS_WIDTH;
    int BLOCKS_HEIGHT;

    mainWindow();

    ~mainWindow();

    void presentScene();

    void processInput(SDL_Event& _event);

    void addLayer(toRender* render);

    void removeLastLayer();

    void addAnimation(innerAnimation* in);
};