#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"
#include "graphic/toRender/toRender.h"
#include "logic/objects/world.h"

innerAnimationCommandComponent::~innerAnimationCommandComponent(){delete an;}

commandComponent* const innerAnimationCommandComponent::replicate(){
    return new innerAnimationCommandComponent(an->replicate());
}

void innerAnimationCommandComponent::abort(command* _command, const game* _game){
    an->abort();
}

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
    an->setCenter(library._world->Get<positionComponent>(_command->source)->tileX, library._world->Get<positionComponent>(_command->source)->tileY);
    an->setSpeed(1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}

int const outerAnimationCommandComponent::reverseAction(command* _command, game* _game){
    if(_command->source==INVALID_ENTITY)return -1;
    an->setCenter(library._world->Get<positionComponent>(_command->source)->tileX, library._world->Get<positionComponent>(_command->source)->tileY);
    an->setSpeed(-1);
    an->begin();
    library._outerAnimationManager->addOuterAnimation(an);
    return 0;
}

commandComponent* const outerAnimationCommandComponent::replicate(){
    return new outerAnimationCommandComponent(an->replicate());
}

void outerAnimationCommandComponent::abort(command* _command, const game* _game){
    an->abort();
}

outerAnimationCommandComponent::~outerAnimationCommandComponent(){delete an;}