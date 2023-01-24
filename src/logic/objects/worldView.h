//iterator designed for scanning the entities in the world
#pragma once

#include "world.h"

template<typename... ComponentTypes>
struct worldView{

    //constructor
    worldView(World& world): world(&world){
        //if no components are specified, all entities are returned
        if (sizeof...(ComponentTypes) == 0){
            all = true;
            it=world.componentPools[0]->occupied.begin();
            ending=world.componentPools[0]->occupied.end();
        }
        //if components are specified, only entities with those components are returned
        else{
            unsigned int componentIds[] = { 0, world.GetId<ComponentTypes>() ... };
            int mini=MAX_COMPONENTS+1;
            for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++){
                mask.set(componentIds[i]);
                if(world.componentPools.size()>componentIds[i] && world.componentPools[componentIds[i]]->occupied.size()<mini){
                    mini=world.componentPools[componentIds[i]]->occupied.size();
                    it=world.componentPools[componentIds[i]]->occupied.begin();
                    ending=world.componentPools[componentIds[i]]->occupied.end();
                }
                else if(world.componentPools.size()<=componentIds[i]){
                    ending=world.componentPools[0]->occupied.end();
                    it=ending;
                }
            }
        }
    }

    struct Iterator{

        Iterator(World* pScene, std::unordered_set<EntityIndex>::iterator it, std::unordered_set<EntityIndex>::iterator ending, ComponentMask mask, bool all) : pScene(pScene), it(it), ending(ending), mask(mask), all(all) {}

        EntityID operator*() const {
            return pScene->entities[*it].id; 
        }

        bool operator==(const Iterator& other) const{
            return (it != ending && (other.it) != other.ending && *it == *(other.it)) || (it == ending && (other.it) == other.ending);
        }

        bool operator!=(const Iterator& other) const{
            return !(*this==other);
        }

        bool ValidIndex(){
            return (all || mask == (mask & pScene->entities[*it].mask));
        }

        Iterator& operator++(){
            do{
                ++it;
            } while (it!=ending && !ValidIndex());
            return *this;
        }

        Iterator operator++(int) { return ++(*this);}//Iterator tmp = *this; ++(*this); return tmp; }

        std::unordered_set<EntityIndex>::iterator it;
        std::unordered_set<EntityIndex>::iterator ending;
        World* pScene;
        ComponentMask mask;
        bool all{ false };
    };

    World* world;
    ComponentMask mask;
    std::unordered_set<EntityIndex>::iterator it;
    std::unordered_set<EntityIndex>::iterator ending;
    bool all{0};

    Iterator begin() {
        //advances while the entity doesn't have the required components
        while (it!=ending && !(mask == (mask & world->entities[*it].mask))){
            ++it;
        } 
        return Iterator(world, it, ending, mask, all);
    }

    Iterator end() const{
        return Iterator(world, ending, ending, mask, all);
    }
};
