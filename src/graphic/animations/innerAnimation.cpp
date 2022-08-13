#include "graphic/animation.h"
#include "logic/objects/world.h"
#include "logic/objects/component.h"

void innerAnimation::begin(){
    it=steps.begin();
    counter=0;
    this->order=1;
}

bool innerAnimation::step(){
    if(this->order){
        if(counter<=0){
            if(it==steps.end())return 1;
            counter=it->first;
            library._world->Get<imageComponent>(source)->img=it->second;
            it++;
        }
        else
            counter--;
        return 0;
    }
    else{
        if(it==steps.begin())return 1;
        if(counter>=it->first){
            counter=0;
            it--;
            library._world->Get<imageComponent>(source)->img=it->second;
        }
        else
            counter++;
        return 0;
    }
}

void innerAnimation::reverseBegin(){
    it=steps.end();
    it--;
    counter=0;
    library._world->Get<imageComponent>(source)->img=it->second;
    this->order=0;
}

void innerAnimation::setSource(EntityID source){
    this->source=source;
}

void innerAnimation::addStep(textureManager::imgDir frame, float ms){
    int dur=std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);
    this->ms+=ms;
    steps.push_back({dur,frame});
}

void innerAnimation::abort(){
    it=steps.end();
    it--;
}

innerAnimation* innerAnimation::replicate(){
    innerAnimation* out = new innerAnimation();
    out->steps=std::list<std::pair<int,textureManager::imgDir>>(this->steps);
    out->source=this->source;
    out->ms=this->ms;
    return out;
}