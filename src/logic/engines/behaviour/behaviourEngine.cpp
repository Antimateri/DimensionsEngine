#include "logic/engines/behaviour/behaviourEngine.h"
#include "logic/objects/world.h"
#include "logic/game.h"
#include "logic/objects/components/component.h"
#include "logic/objects/worldView.h"
#include "control/command.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

std::unordered_map<int, planningParameter*>* updateGoals(std::unordered_map<int, planningParameter*>* out, std::unordered_map<int, planningParameter*>* newGoals){
    for(auto [id,val]: (*newGoals)){
        //TODO meter informacion del tipo
        if(val->isSatisfied(nullptr))
            continue;
        if(out->count(id)==0){
            (*out)[id]=val;
        }
        else{
            (*out)[id]=max((*out)[id],val);
        }
    }
    return out;
}

bool planner(EntityID id, World* _world, std::unordered_map<int, planningParameter *>* goals, std::deque<command*>& bestP, int& best, int cost){
    bool out=0;
    if(cost>=best){
        return 0;
    }
    if(goals->empty()){
        if(cost<best){
            best=cost;
            bestP.clear();
            return 1;
        }
        return 0;
    }
    for(command* i : _world->Get<posibleActionsComponent>(id)->posibilities){
        std::unordered_map<int, planningParameter *>* newGoals=nullptr;
        for(auto [id2,goal] : (*goals)){
            if(i->hasEffect(goal)){
                if(newGoals==nullptr){
                    newGoals=new std::unordered_map<int, planningParameter*>(*goals);
                }
                newGoals=updateGoals(newGoals,i->getPreconditions(goal));
                newGoals->erase(id2);
            }
        }
        if( newGoals!= nullptr && planner(id, _world, newGoals, bestP, best, cost+i->getCost())){
            out=1;
            bestP.push_back(i);
        }
    }
    return out;
}

void behaviourEngine(World* _world){
    for(EntityID id : worldView<actorComponent>(*_world)){
        planningParameter* goal = _world->Get<actorComponent>(id)->getGoal();
        if(goal==nullptr){
            continue;
        }
        if(!_world->Get<actorComponent>(id)->planReady()){
            int best=5000;
            std::unordered_map<int, planningParameter *> goals;
            goals[goal->getID()]=goal;
            std::deque<command*> bestP;
            if(planner(id, _world, &goals, bestP, best, 0)){
                _world->Get<actorComponent>(id)->setPlan(bestP);
            }
        }
        if(_world->Get<actorComponent>(id)->planReady()){
            library._game->addCommand(_world->Get<actorComponent>(id)->getNextAction()->replicate()->setSource(id));
        }
    }
}