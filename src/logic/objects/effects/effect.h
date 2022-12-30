#include "common.h"

class effect{
private:
    int stregth;
public:

    effect(float strength):stregth(strength){}

    virtual std::string getName(){
        return "unnamed";
    }

    virtual float speed(float current_speed){
        return current_speed;
    }

    virtual float in_attack(float current_attack){
        if(current_attack<0) return in_heal(current_attack);
        else return in_damage(current_attack); 
    }

    virtual float out_attack(float current_attack){
        if(current_attack<0) return out_heal(current_attack);
        else return out_damage(current_attack); 
    }

    virtual float in_damage(int current_damage){
        return current_damage;
    }

    virtual float out_damage(int current_damage){
        return current_damage;
    }

    virtual float in_heal(int current_heal){
        return current_heal;
    }

    virtual float out_heal(int current_heal){
        return current_heal;
    }
};

class temporalEffect:public effect{
private:
    int duration;
public:
    
    temporalEffect(float strength,int duration):effect(strength),duration(duration){}
    
    virtual void update(){
        duration--;
    }

    virtual bool isOver(){
        return duration<=0;
    }
};