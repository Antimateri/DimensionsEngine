#include "logic/engines/behaviour/behaviourEngine.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/objects/worldView.h"
#include "control/command.h"
#include "control/commandComponents/commandComponents.h"

bool planner(EntityID id, int cost, World* _world, std::list<command*>& bestP, int& best){
    bool out=0;
    for(command* i : _world->Get<posibleActionsComponent>(id)->posibilities){
        if(_world->Get<goalAutomataComponent>(id)->goals.getCurrentState()->isGoal(i->getEffect())){
            if(i->Accepted(library._game)){
                if(cost+i->getTime()<best){
                    best=cost+i->getTime();
                    out=1;
                    bestP.clear();
                    bestP.push_front(i);
                }
                i->ReverseAccepted(library._game);
            }
        }
    }
    for(command* i : _world->Get<posibleActionsComponent>(id)->posibilities){
        if(!_world->Get<goalAutomataComponent>(id)->goals.getCurrentState()->isGoal(i->getEffect())){
            if(i->Accepted(library._game)){
                if(planner(id, cost+i->getTime(), _world, bestP, best)){
                    out=1;
                    bestP.push_front(i);
                }
                i->ReverseAccepted(library._game);
            }
        }
    }
    return out;
}

void behaviourEngine(World* _world){
    for(EntityID id : worldView<posibleActionsComponent,goalAutomataComponent>(*_world)){
        int best=5000;
        std::list<command*> bestP;
        if(planner(id, 0, _world, bestP, best)){
            library._game->addCommand(bestP.front()->replicate()->addInfoComponent(new EntitySourceCommandComponent(id)));
        }
    }
}