#include "graphic/animation/animation.h"
#include "logic/objects/world.h"
#include "logic/objects/components/component.h"
#include "logic/objects/components/graphicComponent.h"

void innerAnimation::begin(World* _world){
    this->_world=_world;
    loop=ntimes-1;
    if(speed<0){
        it=steps.end();
        it--;
        counter=0;
        _world->Get<imageComponent>(source)->img=it->second;
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

bool innerAnimation::step(){
    if(this->order){
        if(counter<=0){
            if(it==steps.end()){
                if(loop==0)return 1;
                else{
                    it=steps.begin();
                    if(loop>0)loop--;
                }
            }
            counter=it->first;
            _world->Get<imageComponent>(source)->img=it->second;
            it++;
        }
        else
            counter-=speed;
        return 0;
    }
    else{
        if(it==steps.begin()){
            if(loop==0) return 1;
            else{
                it=steps.end();
                it--;
                counter=0;
                _world->Get<imageComponent>(source)->img=it->second;
                if(loop>0)loop--;
            }
        }
        if(counter>=it->first){
            counter=0;
            it--;
            _world->Get<imageComponent>(source)->img=it->second;
        }
        else
            counter-=speed;
        return 0;
    }
}

void innerAnimation::setSpeed(float speed){
    this->speed=speed;
}

void innerAnimation::setRepeats(int ntimes){
    this->ntimes=ntimes;
}

void innerAnimation::setSource(EntityID source){
    this->source=source;
}

void innerAnimation::addStep(textureManager::imgDir frame, float ms){
    float dur=ms*FPS/1000;
    this->ms+=ms;
    steps.push_back({dur,frame});
}

void innerAnimation::abort(){
    if(order){
        it=steps.end();
        _world->Get<imageComponent>(source)->img=steps.begin()->second;
    }
    else{
        it=steps.end();
        it--;
        _world->Get<imageComponent>(source)->img=it->second;
        it=steps.begin();
    }
    loop=0;
    counter=0;
}

innerAnimation* innerAnimation::replicate(){
    innerAnimation* out = new innerAnimation();
    out->steps=std::list<std::pair<float,textureManager::imgDir>>(this->steps);
    out->source=this->source;
    out->ms=this->ms;
    return out;
}