#pragma once

#include "common.h"
#include "logic/objects/world.h"
#include "graphic/textureManager.h"

namespace directions{
        const int center=1;
        const int left=2;
        const int right=4;
        const int top=8;
        const int bottom=16;
        const int all=31;


    void dir2coord(int dir, int &dx, int &dy);

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

    moveError moveTo(int tileX, int tileY, World* world, EntityID id);

    moveError changePos(int dx, int dy, World* world, EntityID id);

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