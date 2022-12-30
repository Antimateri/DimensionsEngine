#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/textureManager.h"
#include "logic/automata/fsm.h"
#include "logic/objects/effects/effect.h"
#include "logic/engines/behaviour/goap/goals/planningParameter.h"

namespace directions{
        const int center=1;
        const int left=2;
        const int right=16;
        const int top=8;
        const int bottom=4;
        const int all=31;


    void dir2coord(int dir, int &dx, int &dy);

    int getOpposite(int dir);
}

class combatComponent{
public:
    int combatID;
    int combatPosition;
};

class imageComponent{
public:
    textureManager::imgDir img;
};

class positionComponent{
private:

    World* _world;
    std::list<EntityID>::iterator pos;
    
public:

    int tileX;
    int tileY;

    enum moveError{
        succes,
        indexOutOfBound,
        PositionOccupied
    };

    positionComponent():tileY(-1), tileX(-1){}

    ~positionComponent();

    moveError moveTo(int tileX, int tileY, World* world, EntityID id, int dir=directions::all);

    moveError changePos(int dx, int dy, World* world, EntityID id, int dir=directions::all);

    moveError moveInDirection(int dir, World* world, EntityID id);
};

class blockComponent{
private:
    int type;

public:

    void setBlock(int dir){
        type=dir;
    }

    bool getBlock(int dir){
        return (type&dir)==dir;
    }

};

class currentActionComponent{
public:
    command* current=nullptr;
};

class activationActionComponent{
public:
    command* action;
};

class posibleActionsComponent{
public:
    std::list<command*> posibilities;
};

/*class goalAutomataComponent{
public:

    FSM<goalState> goals;

    goalAutomataComponent(){}

};*/

class actorComponent{
private:
    std::map<int, planningParameter*> goals;
    std::unordered_map<int, planningParameter*> parameters;
    std::deque<command*> plan;

    bool updatePlan=1;
    int prevGoal;

public:

    bool planReady(){
        return !updatePlan;
    }

    void addParameter(planningParameter* param){
        parameters[param->getID()]=param;
        updatePlan=1;
    }

    actorComponent* addGoal(planningParameter* goal){
        goals[goal->getID()]=goal;
        updatePlan=1;
        return this;
    }

    planningParameter* getGoal(){
        planningParameter* out=nullptr;
        for(auto& i : goals){
            if(i.second->isSatisfied(&parameters)){
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

    void setPlan(std::deque<command*>& _plan){
        if(!_plan.empty()){
            plan=_plan;
            updatePlan=0;
        }
    }

    command* getNextAction(){
        command* out=nullptr;
        if(planReady()){
            out=plan.front();
            plan.pop_front();
            if(plan.empty()){
                updatePlan=1;
            }
        }
        return out;
    }
};

class plancomponent{
public:
    std::list<command*> plan;
};

class effectComponent{
public:
    std::list<effect*> effects;
};

class entityStateComponent{
public:
    planningState* state;
};

class valueComponent{
private:
    int val;
    int maxVal;

public:

    virtual valueComponent* setmax(int maxi){maxVal=maxi;val=maxi;return this;}
    virtual const int getVal(){return val;};
    virtual valueComponent* setVal(int val){this->val=std::max(std::min(val,maxVal),0);return this;}
    virtual valueComponent* addVal(int val){return setVal(this->val+val);}
    virtual valueComponent* subVal(int val){return setVal(this->val-val);}
    virtual const int getMaxVal(){return maxVal;}
};

class healthComponent: public valueComponent{};

class APComponent: public valueComponent{};