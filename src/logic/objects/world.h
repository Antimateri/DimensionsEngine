#pragma once

#include "common.h"
#include "entity.h"

class World{
private:  

    int s_componentCounter;

    std::queue<EntityIndex> freeEntities;

public:

    struct ComponentPool{
        ComponentPool(size_t elementsize){
            elementSize = elementsize;
            pData = new char[elementSize * MAX_ENTITIES];
        }

        ~ComponentPool(){
            delete[] pData;
        }

        inline void* get(size_t index){
            return pData + index * elementSize;
        }

        char* pData{ nullptr };
        size_t elementSize{ 0 };
        std::unordered_set<EntityIndex> occupied;
    };
    
    std::vector<EntityDesc> entities;
    std::vector<ComponentPool*> componentPools;

    struct mapRepresentation{

        int nXTiles, nYTiles;

        World* super;

        std::vector<std::vector<std::list<EntityID>>> map;

       mapRepresentation(int nXTiles, int nYTiles, World* super): 
                nXTiles(nXTiles), nYTiles(nYTiles), map(nXTiles,std::vector<std::list<EntityID>>(nYTiles,std::list<EntityID>())), super(super){}

        bool isValid(int x, int y){
            return (x >= 0) && (x < map.size()) && (y >= 0) && (y < map[0].size());
        }

        long long hashCoord(int x, int y){
            return x*map[0].size()+y;
        }

        void deHashCoord(long long coord, int &x, int &y){
            y=coord%map[0].size();
            x=(coord-y)/map[0].size();
        }

        bool getBlock(int dir, int x, int y);

        bool isValidEntity(int x, int y){
            return isValid(x,y) && !map[x][y].empty() && map[x][y].front()!=INVALID_ENTITY;
        }

        template<typename T>
        T* Get(int x, int y){
            if(!isValidEntity(x,y))
                return nullptr;
            return super->Get<T>(map[x][y].back());
        }

    };

    mapRepresentation _map;

    SDL_Texture* background;

    World(int nXTiles, int nYTiles);

    ~World();

    template <class T>
    unsigned int GetId();

    EntityID newEntity();

    template<typename T>
    T* Assign(EntityID id);

    template<typename T>
    T* Get(EntityID id);

    template<typename T>
    void Remove(EntityID id);

    void DestroyEntity(EntityID id);

};

template <class T>
unsigned int World::GetId(){
    static unsigned int s_componentId = s_componentCounter ++;
    return s_componentId;
}

template<typename T>
T* World::Assign(EntityID id){
    unsigned int componentId = GetId<T>();

    if (componentPools.size() <= componentId){
        componentPools.resize(componentId + 1, nullptr);
    }
    if (componentPools[componentId] == nullptr){
        //Error de redondeo
        componentPools[componentId] = new ComponentPool(sizeof(T));
    }

    // Looks up the component in the pool, and initializes it with placement new
    T* pComponent = new (componentPools[componentId]->get(GetEntityIndex(id))) T();
    componentPools[componentId]->occupied.insert(GetEntityIndex(id));

    // Set the bit for this component to true and return the created component
    entities[GetEntityIndex(id)].mask.set(componentId);
    return pComponent;
} 

template<typename T>
T* World::Get(EntityID id){
    unsigned int componentId = GetId<T>();
    if (!entities[GetEntityIndex(id)].mask.test(componentId))
        return nullptr;

    T* pComponent = static_cast<T*>(componentPools[componentId]->get(GetEntityIndex(id)));
    return pComponent;
}

template<typename T>
void World::Remove(EntityID id){
    // ensures you're not accessing an entity that has been deleted
    if (entities[GetEntityIndex(id)].id != id) 
        return;

    unsigned int componentId = GetId<T>();

    entities[GetEntityIndex(id)].mask.reset(componentId);
    componentPools[componentId]->occupied.erase(GetEntityIndex(id));
}