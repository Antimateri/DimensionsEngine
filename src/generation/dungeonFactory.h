#pragma once
#include "generation/biomeFactory.h"

class dungeonFactory {
    
  private:

    //room creation parameters
    const int _nIterationExpansion=30;
    const int _roomMinSize=10;
    const int _dungeonMaxSize=300;
    const int _dungeonMinSize=70;
    const int _maxPerDifSides=0;
    
    //rooms per biome
    const int _maxHPB=10;
    const int _minHPB=4;
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

    //0 abajo, 1 derecha, 2 arriba, 3 izquierda
    std::pair<int,int> nextMove(int direction) {
      std::pair<int,int> out= {0,0};
      switch(direction) {
        case 0:
          out.second=1;
          break;
        case 1:
          out.first=1;
          break;
        case 2:
          out.second=-1;
          break;
        case 3:
          out.first=-1;
      }
      return out;
    }

    std::vector<biomeFactory*> factories;
    

  public:
    
    dungeonFactory(std::vector<biomeFactory*>& factories): factories(factories) {}
    
    World* makeNew(int difficulty, int seed); //creates a new dungeon
    
  private:

    void makeRooms(Tree* division, randomVar& gen, int width, int height, std::vector<region>& regiones);
    
    int getClosestLeave(Tree* divisions, int index, std::vector<region>& regiones, std::vector<region>& conexions);
    
    void makeConexions(Tree* divisions, std::vector<region>& regiones, randomVar& gen, std::vector<region>& conexions);

    //Junta salas en zonas
    //devuelve un array de zonas(cada zona es un array de numeros identificadores de zonas)
    void makeZones(std::vector<region>& regiones, std::vector<std::vector<int>>& grid, randomVar& gen, std::vector<std::vector<int>>& zones);
    
    void makeBiomes(std::vector<region>& regiones, std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& zones, int difficulty, std::vector<region>& conexions, randomVar& gen, World* world);
    
};