#include "logic/game.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "control/commandComponents/commandComponents.h"
#include "logic/engines/behaviour/behaviourEngine.h"
#include "graphic/mainWindow.h"
#include "control/command.h"
#include "generation/dungeonFactory.h"
#include "generation/caveFactory.h"
#include "generation/biomeFactory.h"

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
    library._game=this;
    std::vector<biomeFactory*> factories;
    //factories.push_back(new biomeFactory());
    factories.push_back(new caveFactory(45,5));
    
    library._mainWindow=new mainWindow();
    library._world=dungeonFactory(factories).makeNew(1,10); //new World(100, 100);
    library._innerAnimationManager=new toRenderInnerAnimation();
    library._mainWindow->addLayer(library._innerAnimationManager);
    library._mainWindow->addLayer(new toRenderBackground());
    library._mainWindow->addLayer(new toRenderEntities());
    library._outerAnimationManager=new toRenderOuterAnimation();
    library._mainWindow->addLayer(library._outerAnimationManager);
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
    while(_gameState!=gameState::Stop){
        if(_gameState==gameState::Run){
            library._mainWindow->presentScene();
            processInput();
            run();
        }
        else if(_gameState==gameState::Pause){
            library._mainWindow->presentScene();
            processInput();
        }
        else if(_gameState==gameState::Combat && library._world->Get<currentActionComponent>(library._player)->current!=nullptr){
            library._mainWindow->presentScene();
            processInput();
            run();
        }
        else if(_gameState==gameState::Combat){
            library._mainWindow->presentScene();
            processInput();
        }
        SDL_Delay( 1000/FPS );
    }
}

void game::run(){
    behaviourEngine(library._world);

    if(waiting.empty())return;

    for(auto c : waiting.front()){
        int code=c->action(this);
        if(code==0){
            _register.push_back(c);
            if(_register.size()>NUMBER_COMMANDS_REMEMBERED){
                delete _register.front();
                _register.pop_front();
            }
        }
        else if(code>0){
            while(waiting.size()<=code)
                waiting.push_back(std::list<command*>());
            auto it=waiting.begin();
            std::advance(it,code);
            (*it).push_back(c);
        }
    }
    waiting.pop_front();
}

void game::processInput(){
    SDL_Event _event;
    while(SDL_PollEvent(&_event)){
        if(_event.type == SDL_QUIT){
			_gameState=gameState::Stop;
            break;
        }
        else if(_event.type == SDL_KEYDOWN && _event.key.keysym.sym == SDLK_ESCAPE){
            if(_gameState==gameState::Pause)
                this->changeGameState(gameState::Run);
            else if(_gameState==gameState::Run)
                this->changeGameState(gameState::Pause);
        }
        else if(this->lockInput==false)
            library._mainWindow->processInput(_event);
    }
}

void game::addCommand(command* c){
    c->ready();
    if(waiting.empty())
        waiting.push_front(std::list<command*>());
    waiting.front().push_back(c);
}