#include "graphic/toRender.h"
#include "logic/objects/world.h"
#include "graphic/mainWindow.h"
#include "logic/objects/component.h"
#include "control/command.h"
#include "control/commandComponents.h"

void toRenderEntities::draw(SDL_Renderer* r){
    for(int y=0; y < library._mainWindow->BLOCKS_HEIGHT; y++)
        for(int x=0; x < library._mainWindow->BLOCKS_WIDTH; x++){
            SDL_Rect dest={x*BLOCK_WIDTH, y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};
            EntityID id = library._world->map[x+Representation_coordinates.topX][y+Representation_coordinates.topY];
            if(id != INVALID_ENTITY && id != RESERVED_SPACE && library._world->Get<imageComponent>(id)!=nullptr){
                library._textureManager->draw(&library._world->Get<imageComponent>(id)->img, &dest);
            }
            if(Representation_coordinates.selectedX==x+Representation_coordinates.topX && Representation_coordinates.selectedY==y+Representation_coordinates.topY){
                SDL_SetRenderDrawColor(r,255,255,255,255);
                SDL_RenderDrawRect(r,&dest);
            }
        }
}

bool toRenderEntities::processInput(SDL_Event& _event){
    if(_event.type==SDL_MOUSEMOTION){
        int x,y;
        SDL_GetMouseState(&x, &y);
        y+=Representation_coordinates.topY*BLOCK_HEIGHT;
        x+=Representation_coordinates.topX*BLOCK_WIDTH;
        x/=BLOCK_WIDTH;
        y/=BLOCK_HEIGHT;
        Representation_coordinates.selectedX=x;
        Representation_coordinates.selectedY=y;
        return 1;
    }
    if(_event.type==SDL_MOUSEBUTTONDOWN && _event.button.button==SDL_BUTTON_LEFT){
        command* _move=new command();
        _move->addActionComponent(new innerAnimationCommandComponent(library.an));
        _move->addActionComponent(new teleportCommandComponent(10));
        _move->addInfoComponent(new targetCommandComponent(Representation_coordinates.selectedX, Representation_coordinates.selectedY));
        _move->addInfoComponent(new EntitySourceCommandComponent(library._player));
        library._game->addCommand(_move);
        return 1;
    }
    return 0;
}