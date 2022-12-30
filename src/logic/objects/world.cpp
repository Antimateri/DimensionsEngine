#include "logic/objects/world.h"
#include "logic/objects/components/component.h"

bool World::mapRepresentation::getBlock(int dir, int x, int y){
        for(EntityID i: map[x][y]){
            if(super->Get<blockComponent>(i) != nullptr && super->Get<blockComponent>(i)->getBlock(dir))
                return 1;
        }
        return 0;
    }

World::World(int nXTiles, int nYTiles): _map(nXTiles, nYTiles, this), chunks((nXTiles/ChunkSize+1)*(nYTiles/ChunkSize+1),chunkManager()){
    s_componentCounter = 0;
    //No entity
    entities.push_back({0,ComponentMask()});
}

World::~World(){
    for(ComponentPool* i : componentPools)
        delete i;
    SDL_DestroyTexture(background);
}

int World::getChunk(int x, int y){
    return x/ChunkSize*(_map.nYTiles/ChunkSize+1)+y/ChunkSize;
}

std::list<int> World::getChunks(int x, int y, int r){
    std::list<int> chunks;
    int center=getChunk(x,y);
    for(int i=-r;i<=r;i++)
        for(int j=-r;j<=r;j++)
            if(i*i+j*j<=r*r)
                chunks.push_back(center+i*(_map.nYTiles/ChunkSize+1)+j);
    return chunks;
}

EntityID World::newEntity(){
    if (!freeEntities.empty()){
        EntityIndex newIndex = freeEntities.back();
        freeEntities.pop();
        EntityID newID = CreateEntityId(newIndex, GetEntityVersion(entities[newIndex].id));
        entities[newIndex].id = newID;
        //this->Assign<ExistsComponent>(newIndex);
        return entities[newIndex].id;
    }
    entities.push_back({ CreateEntityId(EntityIndex(entities.size()), 0), ComponentMask() });
    //this->Assign<ExistsComponent>(entities.back().id);
    return entities.back().id;
}

void World::DestroyEntity(EntityID id){
    if (entities.size()>GetEntityIndex(id) && entities[GetEntityIndex(id)].id != id)
        for(unsigned int i=0;i<componentPools.size();i++)
            if(entities[GetEntityIndex(id)].mask[i])
                componentPools[i]->occupied.erase(GetEntityIndex(id));

    EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
    entities[GetEntityIndex(id)].id = newID;
    entities[GetEntityIndex(id)].mask.reset(); 
    freeEntities.push(GetEntityIndex(id));
}

