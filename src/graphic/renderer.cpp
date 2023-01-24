#include "graphic/renderer.h"

Renderer::~Renderer(){
    auto it=render.begin();
    for(;it!=render.end();it++)
        delete (*it);
}

void Renderer::draw(SDL_Renderer* r){
    auto it=render.begin();
    for(;it!=render.end();it++){
        (*it)->draw(r);
    }
}

void Renderer::processInput(SDL_Event& _event, control* controller){
    auto it=render.rbegin();
    for(;it!=render.rend();it++)
        if((*it)->processInput(_event, controller))
            break;
}

void Renderer::addLayer(toRender* newRender){
    render.push_back(newRender);
}

void Renderer::removeLastLayer(){
    render.pop_back();
}