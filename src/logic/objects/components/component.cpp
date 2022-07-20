#include "logic/objects/component.h"

positionComponent::~positionComponent(){
    _world->map[this->tileX][this->tileY]=INVALID_ENTITY;
}

positionComponent::moveError positionComponent::moveTo(int tileX, int tileY, World* world, EntityID id){
    _world=world;
    if(world->map[tileX][tileY]!=INVALID_ENTITY){
        return moveError::PositionOccupied;
    }
    else if(world->nYTiles<=tileY || world->nXTiles<=tileX || tileY<0 || tileX<0){
        return moveError::indexOutOfBound;
    }
    world->map[this->tileX][this->tileY]=INVALID_ENTITY;
    this->tileX=tileX;
    this->tileY=tileY;
    world->map[tileX][tileY] = id;
    return moveError::succes;
}

positionComponent::moveError positionComponent::changePos(int dx, int dy, World* world, EntityID id){
    return moveTo(tileX + dx, tileY + dy, world, id);
}
