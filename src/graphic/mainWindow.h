//Class to manage the window
#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/renderer.h"

class mainWindow{
private:
    SDL_Renderer *renderer; //The window renderer
	SDL_Window *window;     //The window component for SDL

public:

    Renderer _render;       //The renderer for the window, manages input and output

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BLOCKS_WIDTH;
    int BLOCKS_HEIGHT;

    mainWindow();

    ~mainWindow();

    void presentScene();                                        //Draws the scene

    void processInput(SDL_Event& _event, control* controller);  //Process input adding changes to the controller

    void addLayer(toRender* render);                            //Add a layer to the Renderer

    void removeLastLayer();                                     //Remove the last layer from the Renderer

};