#include "graphic/animation.h"
#include "logic/objects/world.h"
#include "logic/objects/component.h"

void innerAnimation::begin(){
    it=steps.begin();
    counter=0;
    library._world->Get<imageComponent>(source)->img=it->second;
    this->order=1;
}

bool innerAnimation::step(){
    if(this->order){
        if(counter>=it->first){
            counter=0;
            it++;
            if(it==steps.end())return 1;
            library._world->Get<imageComponent>(source)->img=it->second;
        }
        else
            counter++;
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

void innerAnimation::addStep(textureManager::imgDir frame, int ms){
    int dur=std::max(static_cast<int>(std::ceil(ms*FPS/1000)),1);
    this->nsteps+=dur;
    steps.push_back({dur,frame});
}