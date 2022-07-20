#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/component.h"

int main(){
    game _game;
    EntityID ent=library._world->newEntity();
    library._world->Assign<positionComponent>(ent)->moveTo(1,1,library._world,ent);
    library._world->Assign<imageComponent>(ent)->img=library._textureManager->add();
    SDL_Renderer* r=library._textureManager->edit();
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent)->img.getRect());
    library._player=ent;
    EntityID ent2=library._world->newEntity();
    library._world->Assign<positionComponent>(ent2)->moveTo(1,2,library._world,ent2);
    library._world->Assign<imageComponent>(ent2)->img=library._textureManager->add();
    r=library._textureManager->edit();
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent2)->img.getRect());
    library._game->initGame();
    library._game->gameLoop();
    return 0;
}