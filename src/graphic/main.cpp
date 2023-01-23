#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/automata/fsm.h"
#include "logic/engines/behaviour/behaviourEngine.h"
#include "control/command.h"
#include "logic/objects/components/graphicComponent.h"
#include "control/control.h"
#include "graphic/mainWindow.h"
#include "graphic/IO.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

int main(){
    game _game;
    _game.addControlUnit(new commandControl());
    _game.addIOUnit(new SDLIO());
    
    library._mainWindow=new mainWindow();
    library._world=new World(100, 100);
    library._innerAnimationManager=new toRenderInnerAnimation();
    library._mainWindow->addLayer(library._innerAnimationManager);
    library._mainWindow->addLayer(new toRenderBackground());
    library._mainWindow->addLayer(new toRenderEntities());
    library._outerAnimationManager=new toRenderOuterAnimation();
    library._mainWindow->addLayer(library._outerAnimationManager);

    EntityID ent=library._world->newEntity();
    library._world->Assign<positionComponent>(ent)->moveTo(1,1,library._world,ent);
    library._world->Assign<currentActionComponent>(ent);
    library._world->Assign<imageComponent>(ent)->img=library._textureManager->add();

    SDL_Renderer* r=library._textureManager->edit(&library._world->Get<imageComponent>(ent)->img);
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent)->img.getRect());

    library._player=ent;

    EntityID ent2=library._world->newEntity();
    library._world->Assign<positionComponent>(ent2)->moveTo(9,9,library._world,ent2);
    library._world->Assign<imageComponent>(ent2)->img=library._textureManager->add();
    library._world->Assign<blockComponent>(ent2)->setBlock(directions::all);
    library._world->Assign<currentActionComponent>(ent2);
    library._world->Assign<actorComponent>(ent2)->addGoal((new planMove())->setOwner(ent2));
    library._world->Assign<APComponent>(ent2)->setmax(100)->setVal(100);

    r=library._textureManager->edit(&library._world->Get<imageComponent>(ent2)->img);
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    SDL_RenderFillRect(r,&library._world->Get<imageComponent>(ent2)->img.getRect());
    textureManager::imgDir au=library._textureManager->add();
    r=library._textureManager->edit(&au);
    SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
    SDL_RenderFillRect(r,&au.getRect());

    innerAnimation* an=new innerAnimation();
    innerAnimation* an2=new innerAnimation();
    outerAnimation* an3=new outerAnimation();
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an2->addStep(au, 100.0);
    an->addStep(library._world->Get<imageComponent>(ent)->img, 100.0);
    an->addStep(au, 500.0);
    an2->addStep(library._world->Get<imageComponent>(ent)->img, 1.0);

    library.aux=new command();
    library.aux->push_back(new innerAnimationCommandComponent(an));
    library.aux->push_back(new outerAnimationCommandComponent(an3));
    library.aux->push_back(new delayCommandComponent(an->getMs()));
    library.aux->push_back(new setCurrentCommandComponent());
    library.aux->push_back(new teleportCommandComponent(10));
    library.aux->push_back(new innerAnimationCommandComponent(an2));
    library.aux->push_back(new delayCommandComponent(an2->getMs()));
    library.aux->push_back(new resetCurrentCommandComponent());

    command* rando= new command();
    rando->push_back(new setCurrentCommandComponent());
    rando->push_back(new delayCommandComponent(100));
    rando->push_back(new randomMoveCommandComponent(10));
    rando->push_back(new resetCurrentCommandComponent());
    rando->stopable=false;
    library._world->Assign<posibleActionsComponent>(ent2)->posibilities.push_back(rando->setSource(ent2));

    innerAnimation* an4=new innerAnimation();
    an4->addStep(library._world->Get<imageComponent>(ent2)->img, 100.0);
    an4->addStep(au, 500.0);
    an4->addStep(library._world->Get<imageComponent>(ent2)->img, 100.0);

    command* recover= new command();
    recover->push_back(new setCurrentCommandComponent());
    recover->push_back(new innerAnimationCommandComponent(an4));
    recover->push_back(new delayCommandComponent(an4->getMs()));
    recover->push_back(new recoverAPCommandComponent(105));
    recover->push_back(new resetCurrentCommandComponent());
    recover->stopable=false;
    library._world->Get<posibleActionsComponent>(ent2)->posibilities.push_back(recover->setSource(ent2));

    library._game->initGame();
    library._game->gameLoop();
    return 0;
}