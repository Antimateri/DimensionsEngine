#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"
#include "graphic/toRender/toRender.h"
#include "logic/objects/world.h"
#include "logic/game.h"
#include "control/control.h"

innerAnimationCommandComponent::~innerAnimationCommandComponent(){delete an;}

commandComponent* const innerAnimationCommandComponent::replicate(){
    return new innerAnimationCommandComponent(an->replicate());
}

void innerAnimationCommandComponent::abort(command* _command, control* _controller){
    an->abort();
}

int const innerAnimationCommandComponent::action(command* _command, control* _controller){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(1);
    an->begin(_controller->getGame()->getWorld());
    library._innerAnimationManager->addInnerAnimation(an);
    return 0;
}

int const innerAnimationCommandComponent::reverseAction(command* _command, control* _controller){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setSource(_command->source);
    an->setSpeed(-1);
    an->begin(_controller->getGame()->getWorld());
    library._innerAnimationManager->addInnerAnimation(an);
    return 0;
}

int const outerAnimationCommandComponent::action(command* _command, control* _controller){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setCenter(_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileX, _controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileY);
    an->setSpeed(1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}

int const outerAnimationCommandComponent::reverseAction(command* _command, control* _controller){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setCenter(_controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileX, _controller->getGame()->getWorld()->Get<positionComponent>(_command->source)->tileY);
    an->setSpeed(-1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}

commandComponent* const outerAnimationCommandComponent::replicate(){
    return new outerAnimationCommandComponent(an->replicate());
}

void outerAnimationCommandComponent::abort(command* _command, control* _controller){
    an->abort();
}

outerAnimationCommandComponent::~outerAnimationCommandComponent(){delete an;}