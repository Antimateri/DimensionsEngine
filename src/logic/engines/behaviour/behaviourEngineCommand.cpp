#include "logic/engines/behaviour/behaviourEngine.h"
#include "logic/objects/world.h"
#include "logic/game.h"
#include "logic/objects/components/component.h"
#include "logic/objects/worldView.h"
#include "control/command.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"
#include "control/control.h"

//bfs over the action space to find a plan
/*
EntityID entityId                                       the entity to plan for
World* _world                                           the world
std::unordered_map<int, planningParameter *>* state     the state produced during the bfs
std::unordered_map<int, planningParameter *>* goals     the goals to reach
std::deque<command*>& bestP                             the best plan found
int& best                                               the cost of the best plan found
int cost                                                the cost of the current plan
short nrec=0                                            the number of recursive calls to force a recursion limit   

out                                                     if the plan is valid
*/
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
        if(!val->isSatisfied(state, _world)){
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
        if(i->hasEffect(goals, state, _world)){
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

void behaviourEngine(game* _game, control* _controller){
    World* _world=_game->getWorld();
    for(EntityID id : worldView<actorComponent>(*_world)){
        planningParameter* goal = _world->Get<actorComponent>(id)->getGoal();
        if(goal==nullptr){
            continue;
        }
        std::unordered_map<int, planningParameter *> status=_world->Get<actorComponent>(id)->getParameters();
        //make a plan if plan is not ready
        if(!_world->Get<actorComponent>(id)->planValid() && (_world->Get<currentActionComponent>(id)->current==nullptr || _world->Get<currentActionComponent>(id)->current->abort(_controller))){
            int best=5000;
            std::unordered_map<int, planningParameter *> goals;
            goals[goal->getID()]=goal;
            std::deque<command*> bestP;
            if(planner(id, _world, &status, &goals, bestP, best, 0)){
                _world->Get<actorComponent>(id)->setPlan(bestP);
            }
        }
        //execute a plan if possible
        if(_world->Get<actorComponent>(id)->planReady(&status, _game) && _world->Get<currentActionComponent>(id)->current==nullptr){
            command* nextCommand = _world->Get<actorComponent>(id)->getNextAction(&status, _game);
            if(nextCommand!=nullptr)
                static_cast<commandControl*>(_controller)->addCommand(nextCommand->replicate()->setSource(id));
        }
    }
}