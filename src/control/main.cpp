//main to test the control part of the engine, doesnt work right now
#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/automata/fsm.h"
#include "logic/engines/behaviour/behaviourEngine.h"
#include "control/command.h"
#include "logic/objects/components/graphicComponent.h"
#include "control/control.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

int main(){
    game _game;
    _game.addControlUnit(new commandControl());
    
    library._world=new World(100, 100);

    EntityID ent=library._world->newEntity();
    library._world->Assign<positionComponent>(ent)->moveTo(1,1,library._world,ent);
    library._world->Assign<currentActionComponent>(ent);

    library._player=ent;

    EntityID ent2=library._world->newEntity();
    library._world->Assign<positionComponent>(ent2)->moveTo(9,9,library._world,ent2);
    library._world->Assign<blockComponent>(ent2)->setBlock(directions::all);
    library._world->Assign<currentActionComponent>(ent2);
    library._world->Assign<actorComponent>(ent2)->addGoal((new planMove())->setOwner(ent2));
    library._world->Assign<APComponent>(ent2)->setmax(100)->setVal(100);

    library.aux=new command();
    library.aux->push_back(new delayCommandComponent(10));
    library.aux->push_back(new setCurrentCommandComponent());
    library.aux->push_back(new teleportCommandComponent(10));
    library.aux->push_back(new delayCommandComponent(10));
    library.aux->push_back(new resetCurrentCommandComponent());

    command* rando= new command();
    rando->push_back(new setCurrentCommandComponent());
    rando->push_back(new delayCommandComponent(100));
    rando->push_back(new randomMoveCommandComponent(10));
    rando->push_back(new resetCurrentCommandComponent());
    rando->stopable=false;
    library._world->Assign<posibleActionsComponent>(ent2)->posibilities.push_back(rando->setSource(ent2));

    command* recover= new command();
    recover->push_back(new setCurrentCommandComponent());
    recover->push_back(new delayCommandComponent(100));
    recover->push_back(new recoverAPCommandComponent(105));
    recover->push_back(new resetCurrentCommandComponent());
    recover->stopable=false;
    library._world->Get<posibleActionsComponent>(ent2)->posibilities.push_back(recover->setSource(ent2));

    library._game->initGame();
    std::cout<<"Game working..."<<std::endl;
    return 0;
}