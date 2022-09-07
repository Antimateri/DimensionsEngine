#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/textureManager.h"
#include "logic/automata/fsm.h"

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

class ExistsComponent{};

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
        return type&dir==dir;
    }

};

class currentActionComponent{
public:
    command* current=nullptr;
};

class posibleActionsComponent{
public:
    std::list<command*> posibilities;
};

class goalAutomataComponent{
public:

    FSM<goalState> goals;

    goalAutomataComponent(){}

};

class valueComponent{
private:
    int val;
    int maxVal;

public:

    virtual void setmax(int maxi){maxVal=maxi;val=maxi;}
    virtual const int getVal(){return val;};
    virtual void setVal(int val){this->val=std::max(std::min(val,maxVal),0);}
    virtual void addVal(int val){setVal(this->val+val);}
    virtual void subVal(int val){setVal(this->val-val);}
    virtual const int getMaxVal(){return maxVal;}
};

class healthComponent: public valueComponent{};

class APComponent: public valueComponent{};