#pragma once

#include "common.h"
#include "logic/objects/components/component.h"

class commandComponent{
public:
    virtual int const action(command* _command, control* _game){return 0;}
    virtual int const reverseAction(command* _command, control* _game){return 0;}
    virtual bool hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world){return false;}
    virtual std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status){return (new std::unordered_map<int, planningParameter *>());}
    virtual std::unordered_map<int, planningParameter *>* getEffects(command* _command, std::unordered_map<int, planningParameter *>* status){return (new std::unordered_map<int, planningParameter *>());}
    virtual commandComponent* const replicate(){return new commandComponent();}
    virtual void abort(command* _command, control* _game){}
    virtual int const getTime(){return 0;}
    virtual int const getCost(){return 0;}
};

class setCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status);
    commandComponent* const replicate(){return new setCurrentCommandComponent();}
    void abort(command* _command, control* _game);
};

class resetCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState);
    commandComponent* const replicate(){return new resetCurrentCommandComponent();}
    void abort(command* _command, control* _game);
};

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

/*class nextGoalStateCommandComponent: public commandComponent{
private:
    int nextState;
    bool source_target;

    goalState* prev;
    
public:

    nextGoalStateCommandComponent(int nexState, bool source_target): nextState(nextState), source_target(source_target){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    commandComponent* const replicate(){return new nextGoalStateCommandComponent(nextState, source_target);}

};*/

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
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState){return true;}
    commandComponent* const replicate(){return new targetCommandComponent(targetX, targetY);}
};

class innerAnimationCommandComponent: public commandComponent{
private:

    innerAnimation* an;

public:

    innerAnimationCommandComponent(innerAnimation* an):an(an){}

    ~innerAnimationCommandComponent();

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState){return true;}
    commandComponent* const replicate();
    void abort(command* _command, control* _game);
};

class outerAnimationCommandComponent: public commandComponent{
private:

    outerAnimation* an;

public:

    outerAnimationCommandComponent(outerAnimation* an):an(an){}

    ~outerAnimationCommandComponent();

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState){return true;}
    commandComponent* const replicate();
    void abort(command* _command, control* _game);
};

class teleportCommandComponent: public commandComponent{
private:

    int APpT=10;//action points per tile
    int APtaken; //action points taken

    int prevx, prevy;

public:

    teleportCommandComponent(int APpT):APpT(APpT){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState);
    commandComponent* const replicate();
};

class randomMoveCommandComponent: public commandComponent{
private:

    int dirTaken;
    int APCost;

public:

    randomMoveCommandComponent(int APCost):APCost(APCost){}

    int const action(command* _command, control* _game);
    int const reverseAction(command* _command, control* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool hasEffect(command* _command, std::unordered_map<int, planningParameter *>* goals, std::unordered_map<int, planningParameter *>* status, World* _world);
    std::unordered_map<int, planningParameter *>* getPreconditions(command* _command, std::unordered_map<int, planningParameter *>* status);
    std::unordered_map<int, planningParameter *>* getEffects(command* _command, std::unordered_map<int, planningParameter *>* status);
    commandComponent* const replicate(){return new randomMoveCommandComponent(APCost);}
};

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
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game, planningState* userState);
    commandComponent* const replicate(){return new attackCommandComponent(damage, APcost, range, dir);}
};

