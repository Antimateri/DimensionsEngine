#include "generation/caveFactory.h"
#include "logic/objects/world.h"
#include "logic/objects/components/graphicComponent.h"

int caveFactory::getSurrounding(int x, int y, std::vector<std::vector<int>> map) {
    int out=0;
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++)
        if((i!=0 || j!=0) && x+i>=0 && y+j>=0 && x+i<map.size() && y+j<map[0].size() && map[x+i][y+j]!=0 && map[x+i][y+j]==2)
            out++;
    return out;
}

void caveFactory::makeNew(World* world, std::vector<region>& regiones, std::vector<int>& zone, std::vector<region>& conexions, int level, randomVar& gen) {
    std::vector<std::vector<int>> map(world->_map.nXTiles, std::vector<int>(world->_map.nYTiles, 0));
    std::uniform_int_distribution<> distrib(0, RAND_MAX);
    //distribucion aleatoria
    for(int i:zone)
        for(int x=regiones[i][2];x<regiones[i][0];x++)
        for(int y=regiones[i][3];y<regiones[i][1];y++)
            if(distrib(gen)%(101)<=_wallPercentage || x==regiones[i][2] || y==regiones[i][3] || x==regiones[i][0]-1 || y==regiones[i][1]-1)
                map[x][y]=(2);
            else
                map[x][y]=(1);
    
    //generacion de caminos
    for(int i : zone) {
        int centerx=(regiones[i][0]+regiones[i][2])/2;
        int centery=(regiones[i][1]+regiones[i][3])/2;
        if(conexions[i][0]!=0) {
            int change=distrib(gen)%(centery - regiones[i][3]) + regiones[i][3];
            for(int j=regiones[i][3];j<=change;j++) {
                map[conexions[i][0]][j] = (1);
                map[conexions[i][0]+1][j] = (1);
            }
            int start, end;
            if(centerx>conexions[i][0]) {
                start=conexions[i][0];
                end=centerx;
            }
            else {
                start=centerx;
                end=conexions[i][0];
            }
            for(int j=start;j<=end;j++) {
                map[j][change] = (1);
                map[j][change+1] = (1);
            }
            for(int j=change;j<=centery;j++) {
                map[centerx][j] = (1);
                map[centerx+1][j] = (1);
            }
        }
        if(conexions[i][1]!=0) {
            int change=distrib(gen)%(regiones[i][0] - centerx) + centerx;
            for(int j=centerx;j<=change;j++) {
                map[j][centery] = (1);
                map[j][centery+1] = (1);
            }
            int start, end;
            if(centery>conexions[i][1]) {
                start=conexions[i][1];
                end=centery;
            }
            else {
                start=centery;
                end=conexions[i][1];
            }
            for(int j=start;j<=end;j++) {
                map[change][j] = (1);
                map[change-1][j] = (1);
            }
            for(int j=change;j<regiones[i][0];j++) {
                map[j][conexions[i][1]] = (1);
                map[j][conexions[i][1]+1] = (1);
            }
        }
        if(conexions[i][2]!=0) {
            int change=distrib(gen)%(regiones[i][1] - centery) + centery;
            for(int j=centery;j<=change;j++) {
                map[centerx][j] = (1);
                map[centerx+1][j] = (1);
            }
            int start, end;
            if(centerx>conexions[i][2]) {
                start=conexions[i][2];
                end=centerx;
            }
            else {
                start=centerx;
                end=conexions[i][2];
            }
            for(int j=start;j<=end;j++) {
                map[j][change] = (1);
                map[j][change-1] = (1);
            }
            for(int j=change;j<regiones[i][1];j++) {
                map[conexions[i][2]][j] = (1);
                map[conexions[i][2]+1][j] = (1);
            }
        }
        if(conexions[i][3]!=0) {
            int change=distrib(gen)%(centerx - regiones[i][2]) + regiones[i][2];
            for(int j=regiones[i][2];j<=change;j++) {
                map[j][conexions[i][3]] = (1);
                map[j][conexions[i][3]+1] = (1);
            }
            int start, end;
            if(centery>conexions[i][3]) {
                start=conexions[i][3];
                end=centery;
            }
            else {
                start=centery;
                end=conexions[i][3];
            }
            for(int j=start;j<=end;j++) {
                map[change][j] = (1);
                map[change+1][j] = (1);
            }
            for(int j=change;j<=centerx;j++) {
                map[j][centery] = (1);
                map[j][centery+1] = (1);
            }
        }
    }
    
    //pasadas del automata
    for(int j=0;j<_evaluations;j++)
        for(int i:zone) 
            for(int x=regiones[i][2];x<regiones[i][0];x++)
                for(int y=regiones[i][3];y<regiones[i][1];y++) {
                    int surr=getSurrounding(x,y,map);
                    if(map[x][y]==2 && surr<=2)
                        map[x][y]=(1);
                    else if(map[x][y]==1 && surr>=5)
                        map[x][y]=(2);
                }
    
    //interpretacion
    for(int i:zone) {
        for(int x=regiones[i][2];x<regiones[i][0];x++)
        for(int y=regiones[i][3];y<regiones[i][1];y++)
            if(map[x][y]==2){
                //map[x][y]=new Tile(wall);
                EntityID ent=world->newEntity();
                world->Assign<positionComponent>(ent)->moveTo(x,y,world,ent);
                world->Assign<imageComponent>(ent)->img=library._textureManager->add();
                world->Assign<blockComponent>(ent)->setBlock(directions::all);

                SDL_Renderer* rend=library._textureManager->edit(&world->Get<imageComponent>(ent)->img);
                SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
                SDL_RenderFillRect(rend,&world->Get<imageComponent>(ent)->img.getRect());
            }
            else{
                //map[x][y]=new Tile(ground);
                EntityID ent=world->newEntity();
                world->Assign<positionComponent>(ent)->moveTo(x,y,world,ent);
                world->Assign<imageComponent>(ent)->img=library._textureManager->add();

                SDL_Renderer* rend=library._textureManager->edit(&world->Get<imageComponent>(ent)->img);
                SDL_SetRenderDrawColor(rend, 100, 100, 100, 255);
                SDL_RenderFillRect(rend,&world->Get<imageComponent>(ent)->img.getRect());
            }
    }
}