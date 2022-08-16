#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"

int const innerAnimationCommandComponent::action(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(1);
    an->begin();
    library._animationManager->addInnerAnimation(an);
    return an->getSteps();
}

//TODO
int const innerAnimationCommandComponent::reverseAction(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(-1);
    an->begin();
    library._animationManager->addInnerAnimation(an);
    return an->getSteps();
}