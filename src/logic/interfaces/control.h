#pragma once
#include "common.h"

class control{
private:

    game* _game;

public:
    control(){};
    ~control(){};

    void setGame(game* _game){
        this->_game=_game;
    }

    game* getGame(){
        return _game;
    }

    virtual void applyTurn(game* game)=0;
};