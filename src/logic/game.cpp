#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/interfaces/control.h"
#include "logic/interfaces/IO.h"
#include "logic/interfaces/control.h"

struct {
    SDL_Event pause;
    SDL_Event exit;
}controls;

void game::changeGameState(gameState state){
    if(state==_gameState)
        return;
    switch(state){
        case Run:
            _gameState=Run;
            break;
        case Combat:
            _gameState=Combat;
            break;
        case Stop:
            _gameState=Stop;
            break;
        case Pause:
            _gameState=Pause;
            break;
    }
}

game::game(){
    //library._game=this;
}

game::~game(){
}

bool game::initGame(){
    _gameState=Run;
    return 1;
}

void game::gameLoop(){
    while(_gameState!=gameState::Stop){
        if(_gameState==gameState::Run){
            if(_IOUnit!=nullptr) _IOUnit->presentScene(this);
            processInput();
            run();
        }
        else if(_gameState==gameState::Pause){
            if(_IOUnit!=nullptr) _IOUnit->presentScene(this);
            processInput();
        }
        else if(_gameState==gameState::Combat && getWorld()->Get<currentActionComponent>(library._player)->current!=nullptr){
            if(_IOUnit!=nullptr) _IOUnit->presentScene(this);
            processInput();
            run();
        }
        else if(_gameState==gameState::Combat){
            if(_IOUnit!=nullptr) _IOUnit->presentScene(this);
            processInput();
        }
        if(_IOUnit!=nullptr) _IOUnit->delay( 1000/FPS );
    }
}

void game::run(){
    if(_controlUnit!=nullptr) _controlUnit->applyTurn(this);
}

void game::processInput(){
    if(_IOUnit!=nullptr) _IOUnit->processInput(this, _controlUnit);
}

void game::addControlUnit(control* c){
    _controlUnit=c;
    c->setGame(this);
}