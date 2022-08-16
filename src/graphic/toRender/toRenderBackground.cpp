#include "graphic/toRender/toRender.h"
#include "logic/objects/world.h"
#include "graphic/mainWindow.h"

void toRenderBackground::draw(SDL_Renderer* r){

    int topX=Representation_coordinates.topX*BLOCK_WIDTH;
    int topY=Representation_coordinates.topY*BLOCK_HEIGHT;

    SDL_Rect dest={topX, topY, topX+library._mainWindow->SCREEN_WIDTH, topY+library._mainWindow->SCREEN_HEIGHT};

    SDL_Rect dest2={0,0,library._mainWindow->SCREEN_WIDTH, library._mainWindow->SCREEN_HEIGHT};

    SDL_RenderCopy(r,library._world->background,&dest,&dest2);
}