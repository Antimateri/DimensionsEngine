#include "logic/engines/behaviour/behaviourEngine.h"
#include "logic/objects/world.h"
#include "logic/game.h"
#include "logic/objects/components/component.h"
#include "logic/objects/worldView.h"
#include "control/command.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

bool planner(EntityID entityId, World* _world, std::unordered_map<int, planningParameter *>* state, std::unordered_map<int, planningParameter *>* goals, std::deque<command*>& bestP, int& best, int cost, short nrec=0){
    bool out=0;
    nrec++;
    if(nrec>6){
        return 0;
    }
    if(cost>=best){
        return 0;
    }
    bool ending = 1;
    for(auto [id, val]: (*goals)){
        if(!val->isSatisfied(state)){
            ending=false;
            break;
        }
    }
    if(ending){
        if(cost<best){
            best=cost;
            bestP.clear();
            return 1;
        }
        return 0;
    }
    for(command* i : _world->Get<posibleActionsComponent>(entityId)->posibilities){
        std::unordered_map<int, planningParameter *>* newGoals=nullptr;
        std::unordered_map<int, planningParameter *>* newState = nullptr;
        if(i->hasEffect(goals, state)){
            auto [pre,post] = i->getPrePost(state);
            for(auto [id,val]: (*pre)){
                if(newGoals==nullptr){
                    newGoals=new std::unordered_map<int, planningParameter*>();
                    for(auto [id2,val2]: (*goals)){
                        newGoals->insert({id2,val2->replicate()});
                    }
                }
                if(newGoals->count(id)==0){
                    if(val!=nullptr)
                        (*newGoals)[id]=val->setOwner(entityId);
                }
                else{
                    if((*newGoals)[id]->add(val)==nullptr){
                        delete (*newGoals)[id];
                        newGoals->erase(id);
                    }
                }
            }
            for(auto [id,val]: (*post)){
                if(newState==nullptr){
                    newState=new std::unordered_map<int, planningParameter*>();
                    for(auto [id2,val2]: (*state)){
                        newState->insert({id2,val2->replicate()});
                    }
                }
                if(newState->count(id)==0){
                    if(val!=nullptr)
                        (*newState)[id]=val->setOwner(entityId);
                }
                else{
                    if((*newState)[id]->add(val)==nullptr){
                        delete (*newState)[id];
                        newState->erase(id);
                    }
                }
            }
            if(newState==nullptr){
                newState=state;
            }
            if(newGoals==nullptr){
                newGoals=goals;
            }
            if(planner(entityId, _world, newState, newGoals, bestP, best, cost+i->getCost(), nrec)){
                bestP.push_back(i);
                out=1;
            }
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
        std::unordered_map<int, planningParameter *> status=_world->Get<actorComponent>(id)->getParameters();
        //TODO ready?
        if(!_world->Get<actorComponent>(id)->planValid() && _world->Get<currentActionComponent>(id)->current==nullptr){
            int best=5000;
            std::unordered_map<int, planningParameter *> goals;
            //TODO metelo en la funcion
            goals[goal->getID()]=goal;
            std::deque<command*> bestP;
            if(planner(id, _world, &status, &goals, bestP, best, 0)){
                _world->Get<actorComponent>(id)->setPlan(bestP);
            }
        }
        if(_world->Get<actorComponent>(id)->planReady(&status)){
            library._game->addCommand(_world->Get<actorComponent>(id)->getNextAction(&status)->replicate()->setSource(id));
        }
    }
}