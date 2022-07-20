#pragma once

#include "common.h"
#include "logic/objects/component.h"

class commandComponent{
public:
    virtual const void action(command* _command, game* _game){}
    virtual const void reverseAction(command* _command, game* _game){}
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
    virtual const bool accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    virtual const void reverseAccepted(command* _command, const game* _game){}
    virtual const commandComponent* replicate(){return new commandComponent();}
};

class teleportCommandComponent: public commandComponent{
private:

    int APpT=10;//action points per tile
    int APtaken; //action points taken

    int prevx, prevy;

public:

    teleportCommandComponent(int APpT):APpT(APpT){}

    const void action(command* _command, game* _game);
    const void reverseAction(command* _command, game* _game);
    const bool accepted(command* _command, const game* _game);
    const void reverseAccepted(command* _command, const game* _game);
    const commandComponent* replicate();
};

class targetCommandComponent: public commandComponent{
private:

    int targetX;
    int targetY;

    int prevx;
    int prevy;

public:

    targetCommandComponent(int targetX, int targetY): targetX(targetX), targetY(targetY){}

    const void action(command* _command, game* _game);
    const void reverseAction(command* _command, game* _game);
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
    const bool accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    const void reverseAccepted(command* _command, const game* _game){}
    const commandComponent* replicate(){return new targetCommandComponent(targetX, targetY);}
};

class EntitySourceCommandComponent: public commandComponent{
private:

    EntityID ent;

    int prevx;
    int prevy;
    EntityID prevent;

public:

    EntitySourceCommandComponent(EntityID ent): ent(ent){}

    const void action(command* _command, game* _game);
    const void reverseAction(command* _command, game* _game);
    //se paga el precio y se comprueba si puede realizarlo (en ese orden)
    const bool accepted(command* _command, const game* _game){return true;}
    //llamado en caso de que no pueda realizarlo, se devuelve lo pagado
    const void reverseAccepted(command* _command, const game* _game){}
    const commandComponent* replicate(){return new EntitySourceCommandComponent(ent);}
};

