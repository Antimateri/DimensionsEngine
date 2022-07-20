#pragma once

#include "world.h"

template<typename... ComponentTypes>
struct worldView{

    worldView(World& world): world(&world){
        if (sizeof...(ComponentTypes) == 0){
            all = true;
            it=world.componentPools[0].occupied.begin();
            end=world.componentPools[0].occupied.end();
        }
        else{
            int componentIds[] = { 0, GetId<ComponentTypes>() ... };
            int mini=MAX_COMPONENTS+1;
            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++){
                componentMask.set(componentIds[i]);
                if(world.componentPools[componentIds[i]].occupied.size()<mini){
                    mini=world.componentPools[componentIds[i]].occupied.size();
                    it=world.componentPools[componentIds[i]].occupied.begin();
                    end=world.componentPools[componentIds[i]].occupied.end();
                }
            }
        }
    }

    struct Iterator{

        Iterator(World* pScene, std::unordered_set<EntityIndex>::iterator it, std::unordered_set<EntityIndex>::iterator end, ComponentMask mask, bool all) : pScene(pScene), it(it), end(end), mask(mask), all(all) {}

        EntityID operator*() const {
            return pScene->entities[*it].id; 
        }

        bool operator==(const Iterator& other) const{
            return *it == *(other.it) || it == end;
        }

        bool operator!=(const Iterator& other) const{
            return !(*this==other);
        }

        bool ValidIndex(){
            return (all || mask == (mask & pScene->entities[*it].mask));
        }

        Iterator& operator++(){
            do{
                it++;
            } while (it!=end && !ValidIndex());
            return *this;
        }

        std::unordered_set<EntityIndex>::iterator it;
        std::unordered_set<EntityIndex>::iterator end;
        World* pScene;
        ComponentMask mask;
        bool all{ false };
    };

    World* world;
    ComponentMask<MAX_COMPONENTS> mask;
    std::unordered_set<EntityIndex>::iterator it;
    std::unordered_set<EntityIndex>::iterator end;
    bool all{0};

    const Iterator begin() const{
        while (it!=end && !(mask == (mask & world->entities[*it].mask))){
            it++;
        } 
        return Iterator(world, it, end, componentMask, all);
    }

    const Iterator end() const{
        return Iterator(world, end, end, componentMask, all);
    }
};
