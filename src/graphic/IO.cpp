#include "graphic/IO.h"
#include "logic/game.h"
#include "control/control.h"

void SDLIO::processInput(game* _game, control* controller){
    SDL_Event _event;
    while(SDL_PollEvent(&_event)){
        if(_event.type == SDL_QUIT){
            _game->changeGameState(game::gameState::Stop);
            break;
        }
        else if(_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_ESCAPE){
            if(_game->_gameState==game::gameState::Pause)
                _game->changeGameState(game::gameState::Run);
            else if(_game->_gameState==game::gameState::Run)
                _game->changeGameState(game::gameState::Pause);
        }
        else if(!_game->isLocked() && _game->_gameState==game::gameState::Run)
            library._mainWindow->processInput(_event, controller);
    }
}

void SDLIO::presentScene(game* game){
    library._mainWindow->presentScene();
}

void SDLIO::delay(int ms){
    SDL_Delay(ms);
}