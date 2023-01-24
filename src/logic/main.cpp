//code to try the logic module
#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/automata/fsm.h"

int main(){
    game _game;

    _game.setWorld(new World(100, 100));

    EntityID ent=_game.getWorld()->newEntity();
    _game.getWorld()->Assign<positionComponent>(ent)->moveTo(1,1,_game.getWorld(),ent);
    _game.getWorld()->Assign<currentActionComponent>(ent);

    library._player=ent;

    EntityID ent2=_game.getWorld()->newEntity();
    _game.getWorld()->Assign<positionComponent>(ent2)->moveTo(9,9,_game.getWorld(),ent2);
    _game.getWorld()->Assign<blockComponent>(ent2)->setBlock(directions::all);
    _game.getWorld()->Assign<currentActionComponent>(ent2);
    _game.getWorld()->Assign<APComponent>(ent2)->setmax(100)->setVal(100);

    _game.initGame();
    return 0;
}