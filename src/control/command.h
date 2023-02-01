//class that represents a command
#pragma once

#include "common.h"

//it works as a list of commandComponents which work as minicommands that generate a complex action in conjuction
class command{
private:

    std::list<commandComponent*>::iterator it;
    std::list<commandComponent*>::iterator currentState; 
    std::list<commandComponent*> _components; //list of subcommands to execute
    int totalTime=0;    //time in steps to execute the command
    int totalCost=0;    //TODO
    unsigned int effect=0;  //TODO
    std::string name;   //name of the command

    void endAction(game* _game);    //in case of abortion cleans the actions of the command

public:
    EntityID source;    //entity who initialized the command

    int targetX, targetY;  //target of the command in coordinates

    bool stopable;  //if the command can be aborted

    command();

    void ready(){it=_components.begin();}   //resets the iterator to the first subcommand

    EntityIndex getSource(){return source;} 

    command* setSource(EntityIndex _source);

    int action(control* _game); //executes the command
    
    int reverseAction(control* _game);  //executes the command in reverse
    
    command* replicate();   //returns a copy of the command
    
    //checks if the command satisfie any goals given the status of the plan and the world
    bool hasEffect(std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world); 

    //checks if the command can be executed given the status of the plan and the world
    bool canExecute(std::unordered_map<int, planningParameter *>* status, game* _game);

    //returns the preconditions and postconditions of the command given the status of the plan
    std::pair<planningState*,planningState*> getPrePost(std::unordered_map<int, planningParameter *>* status);

    command* push_back(commandComponent* _component);   //adds a subcommand to the command

    command* push_front(commandComponent* _component);  //adds a subcommand to the command

    void pop_front();   //removes the first subcommand

    ~command();

    bool abort(control* _control); //aborts the command
    
    unsigned int const getTime();  //returns the time in milliseconds to execute the command

    unsigned int const getCost();   //returns the cost of the command

    std::string const getName();    

    command* setName(std::string _name);
};