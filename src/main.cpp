#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/automata/fsm.h"
#include "logic/engines/behaviour/behaviourEngine.h"

int main(){
    game _game;

    EntityID ent=library._world->newEntity();
    library._world->Assign<positionComponent>(ent)->moveTo(1,1,library._world,ent);
    library._world->Assign<currentActionComponent>(ent);
    library._world->Assign<imageComponent>(ent)->img=library._textureManager->add();

    SDL_Renderer* r=library._textureManager->edit();
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent)->img.getRect());

    library._player=ent;

    EntityID ent2=library._world->newEntity();
    library._world->Assign<positionComponent>(ent2)->moveTo(1,2,library._world,ent2);
    library._world->Assign<imageComponent>(ent2)->img=library._textureManager->add();
    library._world->Assign<blockComponent>(ent2)->setBlock(directions::all);
    library._world->Assign<currentActionComponent>(ent2);
    library._world->Assign<goalAutomataComponent>(ent2)->goals.getCurrentState()->addGoal(goals::move);

    r=library._textureManager->edit();
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent2)->img.getRect());
    textureManager::imgDir au=library._textureManager->add();
    r=library._textureManager->edit();
    SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
    SDL_RenderFillRect(r,&au.getRect());

    innerAnimation* an=new innerAnimation();
    innerAnimation* an2=new innerAnimation();
    an2->addStep(au, 100);
    an->addStep(library._world->Get<imageComponent>(ent)->img, 100);
    an->addStep(au, 500);
    an2->addStep(library._world->Get<imageComponent>(ent)->img, 1);

    library.aux=new command();
    library.aux->addActionComponent(new innerAnimationCommandComponent(an));
    library.aux->addActionComponent(new setCurrentCommandComponent());
    library.aux->addActionComponent(new teleportCommandComponent(10));
    library.aux->addActionComponent(new innerAnimationCommandComponent(an2));
    library.aux->addActionComponent(new resetCurrentCommandComponent());

    command* rando= new command();
    rando->addActionComponent(new setCurrentCommandComponent());
    rando->addActionComponent(new delayCommandComponent(1000));
    rando->addActionComponent(new randomMoveCommandComponent(10));
    rando->addActionComponent(new resetCurrentCommandComponent());
    library._world->Assign<posibleActionsComponent>(ent2)->posibilities.push_back(rando);

    library._game->initGame();
    library._game->gameLoop();
    return 0;
}