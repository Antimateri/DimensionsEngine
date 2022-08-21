#include "logic/objects/components/component.h"

void directions::dir2coord(int dir, int &dx, int &dy){
    switch(dir){
        case left:
            dy=0;
            dx=-1;
            break;
        case right:
            dx=1;
            dy=0;
            break;
        case top:
            dy=-1;
            dx=0;
            break;
        case bottom:
            dy=1;
            dx=0;
            break;
        default:
            dx=0;
            dy=0;
    }
}

int directions::getOpposite(int dir){
    int out=0;
    int c=1;
    while(dir>0){
        if(dir%2)
            out+=32/c;
        c*=2;
        dir=dir>>1;
    }
    return out;
}

positionComponent::~positionComponent(){
    if(_world->_map.isValid(tileX, tileY))
        _world->_map.map[this->tileX][this->tileY].erase(pos);
}

positionComponent::moveError positionComponent::moveTo(int tileX, int tileY, World* world, EntityID id){
    _world=world;
    if(!world->_map.map[tileX][tileY].empty() && world->_map.Get<blockComponent>(tileX, tileY)!=nullptr \
                            && world->_map.getBlock(directions::all, tileX, tileY)){
        return moveError::PositionOccupied;
    }
    else if(!world->_map.isValid(tileX, tileY)){
        return moveError::indexOutOfBound;
    }
    if(_world->_map.isValid(this->tileX, this->tileY))
        _world->_map.map[this->tileX][this->tileY].erase(pos);
    this->tileX=tileX;
    this->tileY=tileY;
    pos=world->_map.map[tileX][tileY].insert(world->_map.map[tileX][tileY].end(),id);
    return moveError::succes;
}

positionComponent::moveError positionComponent::changePos(int dx, int dy, World* world, EntityID id){
    return moveTo(tileX + dx, tileY + dy, world, id);
}

positionComponent::moveError positionComponent::moveInDirection(int dir, World* world, EntityID id){
    int x,y;
    directions::dir2coord(dir,x,y);
    x+=tileX;
    y+=tileY;
    if(!world->_map.map[x][y].empty() && world->_map.Get<blockComponent>(x, y)!=nullptr \
                                        && world->_map.getBlock(dir, x, y)){
        return moveError::PositionOccupied;
    }
    return moveTo(x, y, world, id);
}
