#include "generation/biomeFactory.h"
#include "logic/objects/world.h"
#include "graphic/textureManager.h"
#include "logic/objects/components/graphicComponent.h"

void biomeFactory::makeNew(World* world, std::vector<region>& regiones, std::vector<int>& zone, std::vector<region>& conexions, int level, randomVar& gen) {
		
    int r,g,b;
    std::uniform_int_distribution<> distrib(0, RAND_MAX);
    r=distrib(gen)%256;
    g=distrib(gen)%256;
    b=distrib(gen)%256;
    for(int i:zone) {
        for(int x=regiones[i].x1;x<regiones[i].x2;x++){
            for(int y=regiones[i].y1;y<regiones[i].y2;y++){
                EntityID ent=world->newEntity();
                world->Assign<positionComponent>(ent)->moveTo(x,y,world,ent);
                world->Assign<imageComponent>(ent)->img=library._textureManager->add();

                SDL_Renderer* rend=library._textureManager->edit(&world->Get<imageComponent>(ent)->img);
                SDL_SetRenderDrawColor(rend, r, g, b, 255);
                SDL_RenderFillRect(rend,&world->Get<imageComponent>(ent)->img.getRect());
            }
        }
    }
}