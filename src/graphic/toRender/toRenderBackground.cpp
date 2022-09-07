#include "graphic/toRender/toRender.h"
#include "logic/objects/world.h"
#include "graphic/mainWindow.h"

void toRenderBackground::draw(SDL_Renderer* r){

    if(Representation_coordinates.topY+down-up>=0 && Representation_coordinates.topY+down-up+library._mainWindow->BLOCKS_HEIGHT<library._world->_map.nYTiles)
        Representation_coordinates.topY+=down-up;
    if(Representation_coordinates.topX+right-left>=0 && Representation_coordinates.topX+right-left+library._mainWindow->BLOCKS_WIDTH<library._world->_map.nXTiles)
        Representation_coordinates.topX+=right-left;
    
    int topX=Representation_coordinates.topX*BLOCK_WIDTH;
    int topY=Representation_coordinates.topY*BLOCK_HEIGHT;

    SDL_Rect dest={topX, topY, topX+library._mainWindow->SCREEN_WIDTH, topY+library._mainWindow->SCREEN_HEIGHT};

    SDL_Rect dest2={0,0,library._mainWindow->SCREEN_WIDTH, library._mainWindow->SCREEN_HEIGHT};

    SDL_RenderCopy(r,library._world->background,&dest,&dest2);
}

bool toRenderBackground::processInput(SDL_Event& _event){
    if(_event.type==SDL_KEYUP && !_event.key.repeat){
        if (_event.key.keysym.scancode==controls.mapUp){
            up=0;
        }
        else if(_event.key.keysym.scancode==controls.mapDown){
            down=0;
        }
        else if(_event.key.keysym.scancode==controls.mapLeft){
            left=0;
        }
        else if(_event.key.keysym.scancode==controls.mapRight){
            right=0;
        }
        else
            return 0;
        return 1;
    }
    else if(_event.type==SDL_KEYDOWN && !_event.key.repeat){
        if (_event.key.keysym.scancode==controls.mapUp){
            up=speed;
        }
        else if(_event.key.keysym.scancode==controls.mapDown){
            down=speed;
        }
        else if(_event.key.keysym.scancode==controls.mapLeft){
            left=speed;
        }
        else if(_event.key.keysym.scancode==controls.mapRight){
            right=speed;
        }
        else 
            return 0;
        return 1;
    }
    return 0;
}