#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/component.h"

struct {
    SDL_Event pause;
    SDL_Event exit;
}controls;

game::game(){
    library._game=this;
    library._world=new World(1000, 1000);
    
    library._mainWindow=new mainWindow();
    library._mainWindow->addLayer(new toRenderEntities());
}

game::~game(){
    delete library._mainWindow;
    delete library._world;
}

bool game::initGame(){
    _gameState=Run;
    return 1;
}

void game::gameLoop(){
    while(_gameState==gameState::Run){
        library._mainWindow->presentScene();
        /*for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                std::cout<<library._world->map[j][i]<<' ';
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;*/
        processInput();
        SDL_Delay( 20 );
    }
}

void game::run(){

}

void game::processInput(){
    SDL_Event _event;
    while(SDL_PollEvent(&_event)){
        if(_event.type == SDL_QUIT){
			_gameState=gameState::Stop;
            break;
        }
        else
            library._mainWindow->processInput(_event);
    }
}

void game::executeCommand(command* c){
    if(c->Accepted(this)){
        c->action(this);
        _register.push_back(c);
        if(_register.size()>NUMBER_COMMANDS_REMEMBERED){
            delete _register.front();
            _register.pop_front();
        }
    }
}