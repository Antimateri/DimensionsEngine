#pragma once
#include "common.h"

class control{
public:
    control(){};
    ~control(){};
    virtual void applyTurn(game* game)=0;
};