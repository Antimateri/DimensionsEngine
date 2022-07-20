#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/textureManager.h"

enum EspecialComponent{
    value
};

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
    
public:

    int tileX;
    int tileY;

    enum moveError{
        succes,
        indexOutOfBound,
        PositionOccupied
    };

    ~positionComponent();

    moveError moveTo(int tileX, int tileY, World* world, EntityID id);

    moveError changePos(int dx, int dy, World* world, EntityID id);
};

class valueComponent{
private:
    int val;
    int maxVal;

public:

    void setmax(int maxi){maxVal=maxi;val=maxi;}
    const int getVal(){return val;};
    void setVal(int val){this->val=std::max(std::min(val,maxVal),0);}
    void addVal(int val){this->val=std::min(this->val+val,maxVal);}
    void subVal(int val){this->val=this->val-val;}
    const int getMaxVal(){return maxVal;}
};

class healthComponent: public valueComponent{};

class APComponent: public valueComponent{};