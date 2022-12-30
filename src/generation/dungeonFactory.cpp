#include "common.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "generation/dungeonFactory.h"

/*void dungeonFactory::makeNew(int difficulty, int seed, World* world) {
	Random rnd=new Random(seed);
	int height=rnd.nextInt(_dungeonMaxSize-_dungeonMinSize+1)+_dungeonMinSize;
	int width=rnd.nextInt(_dungeonMaxSize-_dungeonMinSize+1)+_dungeonMinSize;
    World* created=new World(MAP_WIDTH, MAP_HEIGHT);
	World::mapRepresentation grid=created->_map;
	
	Tree* divisions=new Tree(0);
    std::vector<std::vector<int>> regiones;
	this->makeRooms(divisions, rnd, width, height, regiones);
	
	//Reservo ID's negativos a los EmptyTiles
	for(int i=0;i<regiones.size();i++)
	    for(int x=regiones[i][2];x<regiones[i][0];x++)
		    for(int y=regiones[i][3];y<regiones[i][1];y++)
		        grid.map[x][y].push_back(-1);
	
	std::vector<std::vector<int>> conexions;
    makeConexions(divisions, grid, regiones, rnd, conexions);
	
	std::vector<std::vector<int>> zones;
    makeZones(regiones, grid, rnd, zones);
	
	makeBiomes(regiones, grid, zones, difficulty, conexions, rnd);
	
	for(auto zone: zones)for(int i:zone)
	    for(int x=regiones[i][2];x<regiones[i][0];x++)
		    for(int y=regiones[i][3];y<regiones[i][1];y++)
                if(x==regiones[i][2] || y==regiones[i][3] || x==regiones[i][0]-1 || y==regiones[i][1]-1)
                    if((x==conexions[i][0] && conexions[i][0]!=0 && y==regiones[i][3]) ||\
                    (x==conexions[i][2] && conexions[i][2]!=0 && y==regiones[i][1]-1) ||\
                    (y==conexions[i][1] && conexions[i][1]!=0 && x==regiones[i][0]-1) ||\
                    (y==conexions[i][3] && conexions[i][3]!=0 && x==regiones[i][2]))
                        maps.get(2)[x][y]=new Tile(Color.BLUE);
                    else    
                        maps.get(2)[x][y]=new Tile(Color.RED);
}*/