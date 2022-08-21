#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "logic/engines/behaviour/behaviourEngine.h"

int const teleportCommandComponent::action(command* _command, game* _game){
    prevx=library._world->Get<positionComponent>(_command->source)->tileX;
    prevy=library._world->Get<positionComponent>(_command->source)->tileY;
    if(library._world->Get<positionComponent>(_command->source)->moveTo(_command->targetX,_command->targetY,library._world,_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}
int const teleportCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<positionComponent>(_command->source)->moveTo(prevx, prevy ,library._world,_command->source)!=positionComponent::moveError::succes)
        return -1;
    return 0;
}
bool const teleportCommandComponent::accepted(command* _command, const game* _game){
    APComponent* ap=library._world->Get<APComponent>(_command->source);
    if(ap==nullptr)
        return 1;
    this->APtaken=APpT*(abs(_command->sourceX-_command->targetX)+abs(_command->sourceY-_command->targetY));
    //if(!library._world->_map.map[_command->targetX][_command->targetY].empty() && library._world->_map.map[_command->sourceX][_command->sourceY]!=_command->source)
    //    return 0;
    if(ap->getVal()>=this->APtaken){
        ap->subVal(this->APtaken);
        return 1;
    }
    return 0;
}
void const teleportCommandComponent::reverseAccepted(command* _command, const game* _game){
    APComponent* ap=library._world->Get<APComponent>(_command->source);
    if(ap==nullptr)
        return;
    this->APtaken=APpT*(abs(_command->sourceX-_command->targetX)+abs(_command->sourceY-_command->targetY));
    ap->addVal(this->APtaken);
}
commandComponent* const teleportCommandComponent::replicate(){
    return new teleportCommandComponent(this->APpT);
}

unsigned int const teleportCommandComponent::getEffect(){
    return goals::move;
}

int const randomMoveCommandComponent::action(command* _command, game* _game){
    do{
        dirTaken=1<<rand()%10;
    }while(library._world->Get<positionComponent>(_command->source)->moveInDirection(dirTaken, library._world, _command->source)!=positionComponent::moveError::succes);
    return 0;
}

int const randomMoveCommandComponent::reverseAction(command* _command, game* _game){
    library._world->Get<positionComponent>(_command->source)->moveInDirection(directions::getOpposite(dirTaken), library._world, _command->source);
    return 0;
}

bool const randomMoveCommandComponent::accepted(command* _command, const game* _game){
    int dir=2;
    bool out=0;
    for(int i=1;i<=4;i++){
        int x,y;
        directions::dir2coord(dir,x,y);
        if(library._world->_map.isValid(_command->sourceX+x, _command->sourceY+y) && !library._world->_map.isValidEntity(_command->sourceX+x, _command->sourceY+y)){
            out=1;
            break;
        }
        dir+=2;
    }
    if(out){
        APComponent* ap=library._world->Get<APComponent>(_command->source);
        if(ap==nullptr)
            return 1;
        if(ap->getVal()>=this->APCost){
            ap->subVal(this->APCost);
            return 1;
        }
    }
    return 0;
}
void const randomMoveCommandComponent::reverseAccepted(command* _command, const game* _game){}
unsigned int const randomMoveCommandComponent::getEffect(){return goals::move;}

