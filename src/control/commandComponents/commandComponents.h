//small commands that can be applied to the game and in conjunction create complex commands
#pragma once

#include "common.h"
#include "logic/objects/components/component.h"

//interface
class commandComponent{
public:
    //executes the commandComponent
    virtual int const action(command* _command, control* _game){return 0;}
    //reverses the commandComponent
    virtual int const reverseAction(command* _command, control* _game){return 0;}
    //checks if the commandComponent satisfies any of the goals given the status of the plan and the state of the game
    virtual bool hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world){return false;}
    //returns a list of preconditions that must be satisfied for the commandComponent to be executed
    virtual std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){return (new std::unordered_map<int, planningParameter *>());}
    //returns a list of effects that the commandComponent will have on the game
    virtual std::unordered_map<int, planningParameter *>* getEffects(command* _command, std::unordered_map<int, planningParameter *>* status){return (new std::unordered_map<int, planningParameter *>());}
    //returns a copy of the commandComponent
    virtual commandComponent* const replicate(){return new commandComponent();}
    //aborts the commandComponent 
    virtual void abort(command* _command, control* _game){}
    virtual int const getTime(){return 0;}
    virtual int const getCost(){return 0;}
};

//makes the active command the command the entity is executing (to avoid extreme multitasking)
class setCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status);
    commandComponent* const replicate(){return new setCurrentCommandComponent();}
    void abort(command* _command, control* _game);
};

//resets the command the entity is executing (to avoid extreme multitasking)
class resetCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate(){return new resetCurrentCommandComponent();}
    void abort(command* _command, control* _game);
};

//introduces a delay (to wait for animations for example)
class delayCommandComponent: public commandComponent{
private:
    float ms;

public:

    delayCommandComponent(float ms):ms(ms){}

    int const action(command* _command, control* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    int const reverseAction(command* _command, control* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    commandComponent* const replicate(){return new delayCommandComponent(ms);}
    int const getTime(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
};

//sets a position as the target of the command
class targetCommandComponent: public commandComponent{
private:

    int targetX;
    int targetY;

    int prevx;
    int prevy;

public:

    targetCommandComponent(int targetX, int targetY): targetX(targetX), targetY(targetY){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate(){return new targetCommandComponent(targetX, targetY);}
};

//starts an inner animation 
class innerAnimationCommandComponent: public commandComponent{
private:

    innerAnimation* an;

public:

    innerAnimationCommandComponent(innerAnimation* an):an(an){}

    ~innerAnimationCommandComponent();

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate();
    void abort(command* _command, control* _game);
};

//starts an outer animation
class outerAnimationCommandComponent: public commandComponent{
private:

    outerAnimation* an;

public:

    outerAnimationCommandComponent(outerAnimation* an):an(an){}

    ~outerAnimationCommandComponent();

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate();
    void abort(command* _command, control* _game);
};

//moves the source to the target
class teleportCommandComponent: public commandComponent{
private:

    int APpT=10;//action points per tile
    int APtaken; //action points taken

    int prevx, prevy;

public:

    teleportCommandComponent(int APpT):APpT(APpT){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate();
};

//moves the source in a random direction
class randomMoveCommandComponent: public commandComponent{
private:

    int dirTaken;
    int APCost;

public:

    randomMoveCommandComponent(int APCost):APCost(APCost){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    bool hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world);
    std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status);
    std::unordered_map<int, planningParameter *>* getEffects(command* _command, std::unordered_map<int, planningParameter *>* status);
    commandComponent* const replicate(){return new randomMoveCommandComponent(APCost);}
};

//makes the source recover AP
class recoverAPCommandComponent: public commandComponent{
private:

    int APRecovered;
public:
    
        recoverAPCommandComponent(int APRecovered):APRecovered(APRecovered){}
    
        int const action(command* _command, control* _game);
        int const reverseAction(command* _command, control* _game);
        bool hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world);
        std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status);
        std::unordered_map<int, planningParameter *>* getEffects(command* _command, std::unordered_map<int, planningParameter *>* status);
        commandComponent* const replicate(){return new recoverAPCommandComponent(APRecovered);}
};

//makes the source attack the target (and a entity in it)
class attackCommandComponent: public commandComponent{
private:

    int damage;
    int APcost;
    int range;
    int dir;
    
public:

    attackCommandComponent(int damage, int APcost, int range, int dir):damage(damage), APcost(APcost), range(range), dir(dir){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate(){return new attackCommandComponent(damage, APcost, range, dir);}
};

