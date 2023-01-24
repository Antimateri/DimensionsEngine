#pragma once

#include "common.h"

//a couple of constants and functions to work with directions
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

//TODO
class combatComponent{
public:
    int combatID;
    int combatPosition;
};

//represents the position of an entity in the world
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

//represents how the presence of the entity affects movement in its tile
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

//represent an action the entity is performing
class currentActionComponent{
public:
    command* current=nullptr;
};

class activationActionComponent{
public:
    command* action;
};

//represents the possible actions a entity can perform
class posibleActionsComponent{
public:
    std::list<command*> posibilities;
};

//stores the information relative to the planner of an entity
class actorComponent{
private:

    std::map<int, planningParameter*> goals;
    std::unordered_map<int, planningParameter*> parameters;
    std::deque<command*> plan;

    bool updatePlan=1;
    int prevGoal;

public:

    //remove the active plan
    void clearPlan();

    //check if the plan is valid
    bool planValid();

    //check if the plan is ready to be executed
    bool planReady(std::unordered_map<int, planningParameter *>* status, game* _game);

    //changes the state of the entity
    actorComponent* addParameter(planningParameter* param);

    //gets the parameters of the entity
    std::unordered_map<int, planningParameter*> getParameters();

    //adds a goal to the entity
    actorComponent* addGoal(planningParameter* goal);

    //gets the current goal of the entity
    planningParameter* getGoal();

    //sets the current plan of the entity
    void setPlan(std::deque<command*>& _plan);

    //gets the next step of the current plan
    command* getNextAction(std::unordered_map<int, planningParameter *>* status, game* _game);
};

//TODO
class effectComponent{
public:
    std::list<effect*> effects;
};

//TODO
class entityStateComponent{
public:
    planningState* state;
};

//General class for counters in an entity such as action points or health points
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