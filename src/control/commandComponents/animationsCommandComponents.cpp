#include "control/commandComponents.h"
#include "control/command.h"
#include "logic/objects/component.h"
#include "graphic/animation.h"

int const innerAnimationCommandComponent::action(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->begin();
    library._mainWindow->addAnimation(an);
    return an->getSteps();
}

//TODO
int const innerAnimationCommandComponent::reverseAction(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->reverseBegin();
    library._mainWindow->addAnimation(an);
    return an->getSteps();
}