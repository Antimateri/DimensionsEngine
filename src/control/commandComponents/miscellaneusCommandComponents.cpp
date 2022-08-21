
#include "control/commandComponents/commandComponents.h"
#include "control/command.h"
#include "logic/objects/components/component.h"

int const setCurrentCommandComponent::action(command* _command, game* _game){
    if(library._world->Get<currentActionComponent>(_command->source)!=nullptr){
        if(library._world->Get<currentActionComponent>(_command->source)->current!=nullptr)
            library._world->Get<currentActionComponent>(_command->source)->current->abort();
        library._world->Get<currentActionComponent>(_command->source)->current=_command;
    }
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
            library._world->Get<currentActionComponent>(_command->source)->current->stopable ){
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

int const nextGoalStateCommandComponent::action(command* _command, game* _game){
    if(source_target){
        if(library._world->_map.isValidEntity(_command->targetX, _command->targetY) \
            && library._world->_map.Get<goalAutomataComponent>(_command->targetX, _command->targetY)!=nullptr){
            prev=library._world->_map.Get<goalAutomataComponent>(_command->targetX, _command->targetY)->goals.getCurrentState();
            library._world->_map.Get<goalAutomataComponent>(_command->targetX, _command->targetY)->goals.nextState(this->nextState);
        }
    }
    else
        if(library._world->_map.isValidEntity(_command->sourceX, _command->sourceY) \
            && library._world->_map.Get<goalAutomataComponent>(_command->sourceX, _command->sourceY)!=nullptr){
            prev=library._world->_map.Get<goalAutomataComponent>(_command->sourceX, _command->sourceY)->goals.getCurrentState();
            library._world->_map.Get<goalAutomataComponent>(_command->sourceX, _command->sourceY)->goals.nextState(this->nextState);
        }
    return 0;
}

int const nextGoalStateCommandComponent::reverseAction(command* _command, game* _game){
    if(source_target){
        if(library._world->_map.isValidEntity(_command->targetX, _command->targetY) \
            && library._world->_map.Get<goalAutomataComponent>(_command->targetX, _command->targetY)!=nullptr){
            library._world->_map.Get<goalAutomataComponent>(_command->targetX, _command->targetY)->goals.setCurrentState(prev);
        }
    }
    else
        if(library._world->_map.isValidEntity(_command->sourceX, _command->sourceY) \
            && library._world->_map.Get<goalAutomataComponent>(_command->sourceX, _command->sourceY)!=nullptr){
            library._world->_map.Get<goalAutomataComponent>(_command->sourceX, _command->sourceY)->goals.setCurrentState(prev);
        }
    return 0;
}