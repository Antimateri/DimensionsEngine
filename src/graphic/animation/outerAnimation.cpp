#include "graphic/animation/animation.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/objects/components/graphicComponent.h"

void outerAnimation::begin(){
    loop=ntimes-1;
    if(speed<0){
        it=steps.end();
        it--;
        counter=0;
        this->order=0;
    }
    else if(speed>0){
        it=steps.begin();
        counter=0;
        this->order=1;
    }
    else{
        counter=0;
        it=steps.end();
    }
}

bool outerAnimation::step(){
    if(this->order){
        if(counter<=0){
            counter=it->ms;
            it++;
            if(it==steps.end()){
                if(loop==0)return 1;
                else{
                    it=steps.begin();
                    if(loop>0)loop--;
                }
            }
        }
        else
            counter-=speed*1000/FPS;
        return 0;
    }
    else{
        if(it==steps.begin()){
            if(loop==0) return 1;
            else{
                it=steps.end();
                it--;
                counter=0;
                if(loop>0)loop--;
            }
        }
        if(counter>=it->ms){
            counter=0;
            it--;
        }
        else
            counter-=speed*1000/FPS;
        return 0;
    }
}

void outerAnimation::draw(){
    SDL_Rect dest={(centerX + it->relativeBlockX - Representation_coordinates.topX) * BLOCK_WIDTH  + it->relativeX, 
                   (centerY + it->relativeBlockY - Representation_coordinates.topY) * BLOCK_HEIGHT + it->relativeY,
                   BLOCK_WIDTH, BLOCK_HEIGHT};
    library._textureManager->draw(&it->img, &dest);
}

void outerAnimation::setSpeed(float speed){
    this->speed=speed;
}

void outerAnimation::setRepeats(int ntimes){
    this->ntimes=ntimes;
}

void outerAnimation::setCenter(int x, int y) {
    this->centerX=x;
    this->centerY=y;
}

void outerAnimation::addStep(textureManager::imgDir img, float ms, int relativeX, int relativeY, int relativeBlockX, int relativeBlockY){
    this->ms+=ms;
    steps.push_back({ms, img, relativeBlockX, relativeBlockY, relativeX, relativeY});
}

void outerAnimation::abort(){
    if(order){
        it=steps.end();
        it--;
    }
    else{
        it=steps.begin();
    }
    loop=0;
    counter=0;
}

outerAnimation* outerAnimation::replicate(){
    outerAnimation* out = new outerAnimation();
    out->steps=std::list<frame>(this->steps);
    out->centerX=this->centerX;
    out->centerY=this->centerY;
    out->ms=this->ms;
    return out;
}