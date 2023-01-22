#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/automata/fsm.h"

int main(){
    game _game;

    library._world=new World(100, 100);

    EntityID ent=library._world->newEntity();
    library._world->Assign<positionComponent>(ent)->moveTo(1,1,library._world,ent);
    library._world->Assign<currentActionComponent>(ent);

    library._player=ent;

    EntityID ent2=library._world->newEntity();
    library._world->Assign<positionComponent>(ent2)->moveTo(9,9,library._world,ent2);
    library._world->Assign<blockComponent>(ent2)->setBlock(directions::all);
    library._world->Assign<currentActionComponent>(ent2);
    library._world->Assign<APComponent>(ent2)->setmax(100)->setVal(100);

    library._game->initGame();
    //library._game->gameLoop();
    return 0;
}