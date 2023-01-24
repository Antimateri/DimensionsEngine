#include "control/command.h"
#include "logic/objects/components/component.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

void actorComponent::clearPlan(){
    plan.clear();
    updatePlan=1;
}

bool actorComponent::planValid(){
    return !updatePlan;
}

bool actorComponent::planReady(std::unordered_map<int, planningParameter *>* status, game* _game){
    return planValid() && !plan.empty() && plan.front()->canExecute(status, _game);
}

actorComponent* actorComponent::addParameter(planningParameter* param){
    parameters[param->getID()]=param;
    updatePlan=1;
    return this;
}

std::unordered_map<int, planningParameter*> actorComponent::getParameters(){
    return parameters;
}

actorComponent* actorComponent::addGoal(planningParameter* goal){
    goals[goal->getPriority()]=goal;
    updatePlan=1;
    return this;
}

planningParameter* actorComponent::getGoal(){
    //returns the lowest priority valid goal
    planningParameter* out=nullptr;
    for(auto& i : goals){
        if(i.second->aplicable(&parameters)){
            out=i.second;
            if(prevGoal!=i.first){
                updatePlan=1;
                prevGoal=i.first;
            }
            break;
        }
    }
    return out;
}

void actorComponent::setPlan(std::deque<command*>& _plan){
    if(!_plan.empty()){
        plan=_plan;
        updatePlan=0;
    }
}

command* actorComponent::getNextAction(std::unordered_map<int, planningParameter *>* status, game* _game){
    command* out=nullptr;
    //only act when possible
    if(planReady(status, _game)){
        out=plan.front();
        plan.pop_front();
        if(plan.empty()){
            updatePlan=1;
        }
    }
    return out;
}