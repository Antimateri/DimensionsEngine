#include "graphic/toRender/toRender.h"
#include "graphic/animation/animation.h"

void toRenderInnerAnimation::draw(SDL_Renderer* r){
    if(running){
        auto it=todo.begin();
        while(it!=todo.end())
            if((*it)->step())
                it=todo.erase(it);
            else
                it++;
    }
}

void toRenderInnerAnimation::addInnerAnimation(innerAnimation* in){
    todo.push_back(in);
}

void toRenderInnerAnimation::pause(){
    running=0;
}

void toRenderInnerAnimation::start(){
    running=1;
}