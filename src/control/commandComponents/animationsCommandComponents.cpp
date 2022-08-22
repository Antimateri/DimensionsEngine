#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"

int const innerAnimationCommandComponent::action(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(1);
    an->begin();
    library._innerAnimationManager->addInnerAnimation(an);
    return 0;
}

int const innerAnimationCommandComponent::reverseAction(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(-1);
    an->begin();
    library._innerAnimationManager->addInnerAnimation(an);
    return 0;
}

int const outerAnimationCommandComponent::action(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setCenter(_command->sourceX, _command->sourceY);
    an->setSpeed(1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}

int const outerAnimationCommandComponent::reverseAction(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setCenter(_command->sourceX, _command->sourceY);
    an->setSpeed(-1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}