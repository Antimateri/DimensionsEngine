#pragma once

#include "common.h"
#include "logic/objects/components/component.h"
#include "graphic/animation/animation.h"
#include "logic/automata/fsm.h"

class commandComponent{
public:
    virtual int const action(command* _command, game* _game){return 0;}
    virtual int const reverseAction(command* _command, game* _game){return 0;}
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    virtual bool const accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    virtual void const reverseAccepted(command* _command, const game* _game){}
    virtual commandComponent* const replicate(){return new commandComponent();}
    virtual void abort(command* _command, const game* _game){}
    virtual int const getTime(){return 0;}
    virtual unsigned int const getEffect(){return 0;}
};

class setCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game);
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new setCurrentCommandComponent();}
    void abort(command* _command, const game* _game);
};

class resetCurrentCommandComponent: public commandComponent{
public:
    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game);
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new resetCurrentCommandComponent();}
    void abort(command* _command, const game* _game);
};

class delayCommandComponent: public commandComponent{
private:
    float ms;

public:

    delayCommandComponent(float ms):ms(ms){}

    int const action(command* _command, game* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    int const reverseAction(command* _command, game* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    commandComponent* const replicate(){return new delayCommandComponent(ms);}
    int const getTime(){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
};

class nextGoalStateCommandComponent: public commandComponent{
private:
    int nextState;
    bool source_target;

    goalState* prev;
    
public:

    nextGoalStateCommandComponent(int nexState, bool source_target): nextState(nextState), source_target(source_target){}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    commandComponent* const replicate(){return new nextGoalStateCommandComponent(nextState, source_target);}

};

class targetCommandComponent: public commandComponent{
private:

    int targetX;
    int targetY;

    int prevx;
    int prevy;

public:

    targetCommandComponent(int targetX, int targetY): targetX(targetX), targetY(targetY){}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new targetCommandComponent(targetX, targetY);}
};

class EntitySourceCommandComponent: public commandComponent{
private:

    EntityID ent;

    int prevx;
    int prevy;
    EntityID prevent;

public:

    EntitySourceCommandComponent(EntityID ent): ent(ent){}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new EntitySourceCommandComponent(ent);}
};

class innerAnimationCommandComponent: public commandComponent{
private:

    innerAnimation* an;

public:

    innerAnimationCommandComponent(innerAnimation* an):an(an){}

    ~innerAnimationCommandComponent(){delete an;}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game){return true;}
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new innerAnimationCommandComponent(an->replicate());}
    void abort(command* _command, const game* _game){an->abort();}
};

class outerAnimationCommandComponent: public commandComponent{
private:

    outerAnimation* an;

public:

    outerAnimationCommandComponent(outerAnimation* an):an(an){}

    ~outerAnimationCommandComponent(){delete an;}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game){return true;}
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new outerAnimationCommandComponent(an->replicate());}
    void abort(command* _command, const game* _game){an->abort();}
};

class teleportCommandComponent: public commandComponent{
private:

    int APpT=10;//action points per tile
    int APtaken; //action points taken

    int prevx, prevy;

public:

    teleportCommandComponent(int APpT):APpT(APpT){}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game);
    void const reverseAccepted(command* _command, const game* _game);
    commandComponent* const replicate();
    unsigned int const getEffect();
};

class randomMoveCommandComponent: public commandComponent{
private:

    int dirTaken;
    int APCost;

public:

    randomMoveCommandComponent(int APCost):APCost(APCost){}

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    //se comprueba si puede realizarlo y se paga el precio (en ese orden)
    bool const accepted(command* _command, const game* _game);
    void const reverseAccepted(command* _command, const game* _game);
    commandComponent* const replicate(){return new randomMoveCommandComponent(APCost);}
    unsigned int const getEffect();

};

