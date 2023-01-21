#include "commonGen.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "generation/dungeonFactory.h"

World* dungeonFactory::makeNew(int difficulty, int seed) {
    randomVar gen(seed); 
    std::uniform_int_distribution<> distrib(0, RAND_MAX);

	int height=distrib(gen)%(_dungeonMaxSize-_dungeonMinSize+1)+_dungeonMinSize;
	int width=distrib(gen)%(_dungeonMaxSize-_dungeonMinSize+1)+_dungeonMinSize;
    World* created=new World(width, height);
	std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
	
	Tree* divisions=new Tree(0);
    std::vector<region> regiones;
	std::cout<<"Generating rooms...\n";
	this->makeRooms(divisions, gen, width, height, regiones);
	
	//Reservo ID's negativos a los EmptyTiles
	for(int i=0;i<regiones.size();i++)
	    for(int x=regiones[i].x1;x<regiones[i].x2;x++)
		    for(int y=regiones[i].y1;y<regiones[i].y2;y++)
		        grid[x][y]=i;
	
	std::vector<region> conexions;
	std::cout<<"Generating connections...\n";
    makeConexions(divisions, regiones, gen, conexions);
	
	std::vector<std::vector<int>> zones;
	std::cout<<"Generating zones...\n";
    makeZones(regiones, grid, gen, zones);
	
	std::cout<<"Generating biomes...\n";
	makeBiomes(regiones, grid, zones, difficulty, conexions, gen, created);

	delete divisions;

	SDL_Renderer* renderer=library._textureManager->edit(nullptr);

	SDL_SetRenderTarget(renderer,NULL);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	created->background=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width*BLOCK_WIDTH, height*BLOCK_HEIGHT);
	std::cout<<SDL_GetError();
	SDL_SetRenderTarget(renderer,created->background);
	
	SDL_RenderClear(renderer);


	return created;
	
	/*for(auto zone: zones)for(int i:zone)
	    for(int x=regiones[i][2];x<regiones[i][0];x++)
		    for(int y=regiones[i][3];y<regiones[i][1];y++)
                if(x==regiones[i][2] || y==regiones[i][3] || x==regiones[i][0]-1 || y==regiones[i][1]-1)
                    if((x==conexions[i][0] && conexions[i][0]!=0 && y==regiones[i][3]) ||\
                    (x==conexions[i][2] && conexions[i][2]!=0 && y==regiones[i][1]-1) ||\
                    (y==conexions[i][1] && conexions[i][1]!=0 && x==regiones[i][0]-1) ||\
                    (y==conexions[i][3] && conexions[i][3]!=0 && x==regiones[i][2]))
                        maps[2][x][y]=new Tile(Color.BLUE);
                    else    
                        maps[2][x][y]=new Tile(Color.RED);*/
}

void dungeonFactory::makeRooms(Tree* division, randomVar& gen, int width, int height, std::vector<region>& regiones){
	std::uniform_int_distribution<> distrib(0, RAND_MAX);
	std::vector<Tree*> raices;
	raices.push_back(division);
	regiones.push_back({
		width,
		height,
		0,
		0
	});
	for(int iter=0;iter<_nIterationExpansion;iter++) {
		int size=regiones.size();
		for(int i=0;i<size;i++) {
			int prex1=regiones[i].x2,prey1=regiones[i].y2,prex0=regiones[i].x1,prey0=regiones[i].y1;
			//Si no puede hacer un tipo de particion hace el otro, asi evita que haya salas demasiado grandes
			switch(distrib(gen)%2) {
			case 1:
				//comprueba que le quepa una sala y que no se desproporcionen demasiado
				if(prex1-prex0-2*_roomMinSize>0 && (prex1-prex0)*_maxPerDifSides/100<prey1-prey0) {
					int n=distrib(gen)%(prex1-prex0+1-2*_roomMinSize)+prex0+_roomMinSize;
					regiones.push_back({
						n,
						prey1,
						prex0,
						prey0
					});
					regiones[i].x1=n;
					raices[i]->der=new Tree(i);
					raices[i]->iz=new Tree(regiones.size()-1);
					raices.push_back(raices[i]->iz);
					raices[i]=raices[i]->der;
					break;
				}
			case 0:
				if(prey1-prey0-2*_roomMinSize>0 && (prey1-prey0)*_maxPerDifSides/100<prex1-prex0) {
					int n=distrib(gen)%(prey1-prey0+1-2*_roomMinSize)+prey0+_roomMinSize;
					regiones.push_back({
						prex1,
						n,
						prex0,
						prey0
					});
					regiones[i].y1=n;
					raices[i]->der=new Tree(i);
					raices[i]->iz=new Tree(regiones.size()-1);
					raices.push_back(raices[i]->iz);
					raices[i]=raices[i]->der;
					break;
				}
			default:
				if(prex1-prex0-2*_roomMinSize>0 && (prex1-prex0)*_maxPerDifSides/100<prey1-prey0) {
					int n=distrib(gen)%(prex1-prex0+1-2*_roomMinSize)+prex0+_roomMinSize;
					regiones.push_back({
						n,
						prey1,
						prex0,
						prey0
					});
					regiones[i].x1=n;
					raices[i]->der=new Tree(i);
					raices[i]->iz=new Tree(regiones.size()-1);
					raices.push_back(raices[i]->iz);
					raices[i]=raices[i]->der;
					break;
				}
			}
		}
	}
}

int dungeonFactory::getClosestLeave(Tree* divisions, int index, std::vector<region>& regiones, std::vector<region>& conexions){
	std::queue<Tree*> cola;
		int out=-1;
		cola.push(divisions);
		while(!cola.empty()) {
			auto f=cola.front();
			cola.pop();
			if(f->der==nullptr && f->iz==nullptr) {
				region aux1=regiones[f->val];
				region aux2=regiones[index];
				bool xaxis=( ( aux1.x2==(aux2.x1) && conexions[f->val][1]==0 && conexions[index][3]==0 ) || ( aux1.x1==(aux2.x2) && conexions[f->val][3]==0 && conexions[index][1]==0 ) ) && aux1.y1<=aux2.y2 - _minConexion && aux2.y1<=aux1.y2 - _minConexion;
				bool yaxis=( ( aux1.y2==(aux2.y1) && conexions[f->val][2]==0 && conexions[index][0]==0 ) || ( aux1.y1==(aux2.y2) && conexions[f->val][0]==0 && conexions[index][2]==0 ) ) && aux1.x1<=aux2.x2 - _minConexion && aux2.x1<=aux1.x2 - _minConexion;
				if(xaxis || yaxis) {
					out=f->val;
					break;
				}
			}
			else if(f->der==nullptr) {
				cola.push(f->iz);
			}
			else if(f->iz==nullptr) {
				cola.push(f->der);
			}
			else {
				cola.push(f->iz);
				cola.push(f->der);
			}
		}
		return out;
}

void dungeonFactory::makeConexions(Tree* divisions, std::vector<region>& regiones, randomVar& gen, std::vector<region>& conexions){
	std::vector<Tree*>* siguiente = new std::vector<Tree*>();
	std::vector<Tree*>* actual = new std::vector<Tree*>(); 
	actual->push_back(divisions);
	for(int i=0;i<regiones.size();i++) {
		conexions.push_back({0,0,0,0});
	}
	while(!actual->empty()) {
		for(int i=0;i<actual->size();i++) {
			if((*actual)[i]->der==nullptr && (*actual)[i]->iz==nullptr) {
				if(i<actual->size()-1) {
					int posible=-1;
					for(int j=i+1;j<actual->size() && posible==-1;j++)
						posible=getClosestLeave((*actual)[j],(*actual)[i]->val,regiones,conexions);
					if(posible>=0) {
						//izquierda
						if(regiones[posible][2]==regiones[(*actual)[i]->val][0]) {
							int intervalmin=std::max(regiones[posible][3], regiones[(*actual)[i]->val][3]);
							int intervalmax=std::min(regiones[posible][1], regiones[(*actual)[i]->val][1]);
							conexions[posible][3]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][1]=((intervalmin+intervalmax)/2);
						}
						//abajo
						else if(regiones[posible][3]==regiones[(*actual)[i]->val][1]) {
							int intervalmin=std::max(regiones[posible][2], regiones[(*actual)[i]->val][2]);
							int intervalmax=std::min(regiones[posible][0], regiones[(*actual)[i]->val][0]);
							conexions[posible][0]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][2]=((intervalmin+intervalmax)/2);
						}
						//derecha
						else if(regiones[posible][0]==regiones[(*actual)[i]->val][2]) {
							int intervalmin=std::max(regiones[posible][3], regiones[(*actual)[i]->val][3]);
							int intervalmax=std::min(regiones[posible][1], regiones[(*actual)[i]->val][1]);
							conexions[posible][1]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][3]=((intervalmin+intervalmax)/2);
						}
						//arriba
						else if(regiones[posible][1]==regiones[(*actual)[i]->val][3]) {
							int intervalmin=std::max(regiones[posible][2], regiones[(*actual)[i]->val][2]);
							int intervalmax=std::min(regiones[posible][0], regiones[(*actual)[i]->val][0]);
							conexions[posible][2]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][0]=((intervalmin+intervalmax)/2);
						}
					}
				}
				if(i>0) {
					int posible=-1;
					for(int j=i-1;j>=0 && posible==-1;j--)
						posible=getClosestLeave((*actual)[j],(*actual)[i]->val,regiones,conexions);
					if(posible>=0) {
						//izquierda
						if(regiones[posible][2]==regiones[(*actual)[i]->val][0]) {
							int intervalmin=std::max(regiones[posible][3], regiones[(*actual)[i]->val][3]);
							int intervalmax=std::min(regiones[posible][1], regiones[(*actual)[i]->val][1]);
							conexions[posible][3]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][1]=((intervalmin+intervalmax)/2);
						}
						//abajo
						else if(regiones[posible][3]==regiones[(*actual)[i]->val][1]) {
							int intervalmin=std::max(regiones[posible][2], regiones[(*actual)[i]->val][2]);
							int intervalmax=std::min(regiones[posible][0], regiones[(*actual)[i]->val][0]);
							conexions[posible][0]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][2]=((intervalmin+intervalmax)/2);
						}
						//derecha
						else if(regiones[posible][0]==regiones[(*actual)[i]->val][2]) {
							int intervalmin=std::max(regiones[posible][3], regiones[(*actual)[i]->val][3]);
							int intervalmax=std::min(regiones[posible][1], regiones[(*actual)[i]->val][1]);
							conexions[posible][1]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][3]=((intervalmin+intervalmax)/2);
						}
						//arriba
						else if(regiones[posible][1]==regiones[(*actual)[i]->val][3]) {
							int intervalmin=std::max(regiones[posible][2], regiones[(*actual)[i]->val][2]);
							int intervalmax=std::min(regiones[posible][0], regiones[(*actual)[i]->val][0]);
							conexions[posible][2]=((intervalmin+intervalmax)/2);
							conexions[(*actual)[i]->val][0]=((intervalmin+intervalmax)/2);
						}
					}
				}
			}
			else if((*actual)[i]->der==nullptr) {
				siguiente->push_back((*actual)[i]->iz);
			}
			else if((*actual)[i]->iz==nullptr) {
				siguiente->push_back((*actual)[i]->der);
			}
			else {
				siguiente->push_back((*actual)[i]->iz);
				siguiente->push_back((*actual)[i]->der);
			}
		}
		delete actual;
		actual = siguiente;
		siguiente = new std::vector<Tree*>();
	}
	delete actual;
	delete siguiente;
}

void dungeonFactory::makeZones(std::vector<region>& regiones, std::vector<std::vector<int>>& grid, randomVar& gen, std::vector<std::vector<int>>& zones){
	std::uniform_int_distribution<> distrib(0, RAND_MAX);
	std::unordered_set<int> registrados;
	for(int i=0;i<regiones.size();i++) if(!registrados.count(i)){
		std::vector<int> in;	    
		int maxsalas=distrib(gen)%(_maxHPB-_minHPB+1)+_minHPB;
		//pa donde se mueve
		int direction=distrib(gen)%(2);
		//posicion actual
		int x=regiones[i].x1, y=regiones[i].y1;
		//numero de bloques de frontera con fronteraActual
		int frontera=0;
		//sala actual
		int actual=grid[x][y];
		//sala cuya frontera esta registrando
		int fronteraActual=0;
		//celdas en las que ha entrado a la sala
		int xprin=x, yprin=y;
		in.push_back(grid[x][y]);
		registrados.insert(grid[x][y]);
		std::pair<int,int> posfrontera=nextMove((direction+3)%4);
		if(!(x+posfrontera.first<0 || y+posfrontera.second<0 || x+posfrontera.first>=grid.size() || y+posfrontera.second>=grid[0].size()) && !registrados.count(grid[x+posfrontera.first][y+posfrontera.second])) {
			frontera=1;
			fronteraActual=grid[x+posfrontera.first][y+posfrontera.second];
		}
		while(true) {
			std::pair<int,int> next=nextMove(direction);
			x+=next.first;
			y+=next.second;
			posfrontera=nextMove((direction+3)%4);
			//esta rodeada de celdas ya cogidas
			if(x==xprin && y==yprin) {
				break;
			}
			//Se sale del lado, cambio de direccion
			else if(x<0 || y<0 || x>=grid.size() || y>=grid[0].size() || grid[x][y]!=actual) {
				x-=next.first;
				y-=next.second;
				direction=(direction+1)%4;
			}
			//comportamiento normal
			else if(!(x+posfrontera.first<0 || y+posfrontera.second<0 || x+posfrontera.first>=grid.size() || y+posfrontera.second>=grid[0].size())){
				//caso en el que no tuviera frontera con nada bueno
				if(frontera==0) {
					if(!registrados.count(grid[x+posfrontera.first][y+posfrontera.second])) {
						frontera=1;
						fronteraActual=grid[x+posfrontera.first][y+posfrontera.second];
					}
				}
				//caso en el que tuviera frontera con algo distinto
				else if(fronteraActual!=grid[x+posfrontera.first][y+posfrontera.second]) {
					if(!registrados.count(grid[x+posfrontera.first][y+posfrontera.second])) {
						frontera=1;
						fronteraActual=grid[x+posfrontera.first][y+posfrontera.second];
					}
					else {
						frontera=0;
					}
				}
				//continuacion de la frontera
				else {
					frontera++;
					if(frontera==_minConexion) {
						in.push_back(fronteraActual);
						registrados.insert(fronteraActual);
						actual=fronteraActual;
						x-=4*next.first-posfrontera.first;
						y-=4*next.second-posfrontera.second;
						xprin=x; yprin=y;
						frontera=0;
						direction=(direction+2)%4;
						if(in.size()>=maxsalas)
						break;
					}
				}
			}
		}
		zones.push_back(in);
	}
}

void dungeonFactory::makeBiomes(std::vector<region>& regiones, 
								std::vector<std::vector<int>>& grid, 
								std::vector<std::vector<int>>& zones, 
								int difficulty, 
								std::vector<region>& conexions, 
								randomVar& gen,
								World* world
								){
	std::uniform_int_distribution<> distrib(0, RAND_MAX);
	for(auto j : zones) {
		int biome=distrib(gen)%factories.size();
		factories[biome]->makeNew(world, regiones, j, conexions, difficulty, gen);
	}
}