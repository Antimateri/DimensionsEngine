#pragma once

#include "common.h"

struct EntityDesc{
    EntityID id;
    ComponentMask mask;

    EntityDesc(EntityID id, ComponentMask mask):id(id), mask(mask){};
};

inline EntityID CreateEntityId(EntityIndex index, EntityVersion version){
    // Shift the index up 32, and put the version in the bottom
    return (static_cast<EntityID>(version) << 32) | static_cast<EntityID>(index);
}

inline EntityIndex GetEntityIndex(EntityID id){
    // Shift down 32 so we lose the version and get our index
    return id;
}

inline EntityVersion GetEntityVersion(EntityID id){
    // Cast to a 32 bit int to get our version number (loosing the top 32 bits)
    return static_cast<EntityVersion>(id >> 32);
}

inline bool IsEntityValid(EntityID id){
    // Check if the index is our invalid index
    return id != EntityIndex(-1);
}

#define INVALID_ENTITY 0