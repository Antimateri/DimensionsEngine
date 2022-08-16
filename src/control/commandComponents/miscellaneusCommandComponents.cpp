
#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"

int const setCurrentCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
    return 0;
}
int const setCurrentCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

bool const setCurrentCommandComponent::accepted(command* _command, const game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)==nullptr || \
            library._world->Get<currentActionComponent>(_command->source)->current==nullptr || \
            library._world->Get<currentActionComponent>(_command->source)->current->abort() ){
        return 1;
    }
    return 0;
}

int const resetCurrentCommandComponent::reverseAction(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
    return 0;
}
int const resetCurrentCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr)
        library._world->Get<currentActionComponent>(_command->source)->current=nullptr;
    return 0;
}

bool const resetCurrentCommandComponent::accepted(command* _command, const game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)==nullptr || \
        library._world->Get<currentActionComponent>(_command->source)->current==_command){
        return 1;
    }
    return 0;
}