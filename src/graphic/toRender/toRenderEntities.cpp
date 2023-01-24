#include "graphic/toRender/toRender.h"
#include "logic/objects/world.h"
#include "graphic/mainWindow.h"
#include "logic/objects/components/component.h"
#include "control/command.h"
#include "logic/game.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/algorithms.h"
#include "logic/objects/components/graphicComponent.h"
#include "control/control.h"

void toRenderEntities::draw(SDL_Renderer* r){
    for(int y=0; y < library._mainWindow->BLOCKS_HEIGHT; y++)
        for(int x=0; x < library._mainWindow->BLOCKS_WIDTH; x++){
            SDL_Rect dest={x*BLOCK_WIDTH, y*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};

            for(EntityID id : _game->getWorld()->_map.map[x+Representation_coordinates.topX][y+Representation_coordinates.topY]){
                if(id != INVALID_ENTITY && id != RESERVED_SPACE && _game->getWorld()->Get<imageComponent>(id)!=nullptr){
                    library._textureManager->draw(&_game->getWorld()->Get<imageComponent>(id)->img, &dest);
                }
            }

            if(Representation_coordinates.selectedX==x+Representation_coordinates.topX && Representation_coordinates.selectedY==y+Representation_coordinates.topY){
                SDL_SetRenderDrawColor(r,255,255,255,255);
                SDL_RenderDrawRect(r,&dest);
            }
        }
}

command* generatePathCommand(int endx, int endy, EntityID id, game* _game){
    std::list<Pair> in;
    command* out=new command();
    out->setSource(id);
    out->push_back(new setCurrentCommandComponent());
    int beginx= _game->getWorld()->Get<positionComponent>(id)->tileX;
    int beginy= _game->getWorld()->Get<positionComponent>(id)->tileY;
    if(getPath( _game->getWorld()->_map, beginx, beginy, endx, endy, in)){
        for(Pair i: in){
            out->push_back(new targetCommandComponent(i.first, i.second));
            out->push_back(new delayCommandComponent(100));
            out->push_back(new teleportCommandComponent(1));
        }
    }
    out->push_back(new resetCurrentCommandComponent());
    out->stopable=true;
    return out;
}

bool toRenderEntities::processInput(SDL_Event& _event, control* controller){
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
        /*command* _move=library.aux->replicate();
        _move->addInfoComponent(new targetCommandComponent(Representation_coordinates.selectedX, Representation_coordinates.selectedY));
        _move->addInfoComponent(new EntitySourceCommandComponent(library._player));*/
        command * move = generatePathCommand(Representation_coordinates.selectedX, Representation_coordinates.selectedY ,library._player, _game);
        static_cast<commandControl*>(controller)->addCommand(move);
        return 1;
    }
    if(_event.type==SDL_MOUSEBUTTONDOWN && _event.button.button==SDL_BUTTON_RIGHT){
        command* _move=library.aux->replicate();
        _move->push_front(new targetCommandComponent(Representation_coordinates.selectedX, Representation_coordinates.selectedY));
        _move->setSource(library._player);
        static_cast<commandControl*>(controller)->addCommand(_move);
        return 1;
    }
    return 0;
}