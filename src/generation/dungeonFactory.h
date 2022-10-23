#include "common.h"
#include "generation/biomeFactory.h"
#include "logic/objects/world.h"
#include "logic/objects/world.h"

class dungeonFactory {
    
    //room creation parameters
    const int _roomMinSize=10;
    const int _dungeonMaxSize=300;
    const int _dungeonMinSize=70;
    const int _maxPerDifSides=0;
    
    //rooms per biome
    const int _maxHPB=7;
    const int _minHPB=3;
    const int _minConexion=10;
    
    //std::list<BiomeFactory> _factories;
    
    struct Tree{
      Tree* der;
      Tree* iz;
      int val;
      
      Tree(int val){
          this->val=val; 
          iz=nullptr;
          der=nullptr;
      }

    };
    
    dungeonFactory(std::list<biomeFactory>* factories);
    
    void makeNew(int difficulty, int seed, World* world); //creates a new dungeon
    
    void makeRooms(Tree* division, int seed, int width, int height, std::vector<std::vector<int>>& regiones);
    
    int getClosestLeave(Tree* divisions, int index, std::vector<std::vector<int>>& regiones, std::vector<std::vector<int>>& conexions);
    
    void makeConexions(Tree* divisions, World::mapRepresentation& grid, std::vector<std::vector<int>>& regiones, int seed, std::vector<std::vector<int>>& conexions);

    //Junta salas en zonas
    //devuelve un array de zonas(cada zona es un array de numeros identificadores de zonas)
    void makeZones(std::vector<std::vector<int>>& regiones, World::mapRepresentation grid, int seed, std::vector<std::vector<int>>& zones);
    
    void makeBiomes(std::vector<std::vector<int>>& regiones, World::mapRepresentation grid, std::vector<std::vector<int>>& zones, int difficulty, std::vector<std::vector<int>>& conexions, int seed);
    
};