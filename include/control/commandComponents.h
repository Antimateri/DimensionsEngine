#pragma once

#include "common.h"
#include "logic/objects/component.h"
#include "graphic/animation.h"

class commandComponent{
public:
    virtual int const action(command* _command, game* _game){return 0;}
    virtual int const reverseAction(command* _command, game* _game){return 0;}
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
    virtual bool const accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    virtual void const reverseAccepted(command* _command, const game* _game){}
    virtual commandComponent* const replicate(){return new commandComponent();}
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
    bool const accepted(command* _command, const game* _game);
    void const reverseAccepted(command* _command, const game* _game);
    commandComponent* const replicate();
};

class delayCommandComponent: public commandComponent{
private:
    int ms;

public:

    delayCommandComponent(int ms):ms(ms){}

    int const action(command* _command, game* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    int const reverseAction(command* _command, game* _game){return std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);}
    commandComponent* const replicate(){return new delayCommandComponent(ms);}
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
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
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
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
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

    int const action(command* _command, game* _game);
    int const reverseAction(command* _command, game* _game);
    bool const accepted(command* _command, const game* _game){return true;}
    void const reverseAccepted(command* _command, const game* _game){}
    commandComponent* const replicate(){return new innerAnimationCommandComponent(an);}
};

