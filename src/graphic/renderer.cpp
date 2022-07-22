#include "graphic/renderer.h"

void Renderer::processAnimations(){
    auto it=todo.begin();
    while(it!=todo.end())
        if((*it)->step())
            it=todo.erase(it);
        else
            it++;
}

Renderer::~Renderer(){
    auto it=render.begin();
    for(;it!=render.end();it++)
        delete (*it);
}

void Renderer::draw(SDL_Renderer* r){
    processAnimations();
    auto it=render.begin();
    for(;it!=render.end();it++){
        (*it)->draw(r);
    }
}

void Renderer::processInput(SDL_Event& _event){
    auto it=render.rbegin();
    for(;it!=render.rend();it++)
        if((*it)->processInput(_event))
            break;
}

void Renderer::addLayer(toRender* newRender){
    render.push_back(newRender);
}

void Renderer::removeLastLayer(){
    render.pop_back();
}

void Renderer::addInnerAnimation(innerAnimation* in){
    todo.push_back(in);
}