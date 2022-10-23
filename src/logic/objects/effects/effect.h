#include "common.h"

class effect{

    virtual std::string getName(){
        return "unnamed";
    }

    virtual float speed(float current_speed){
        return current_speed;
    }

    virtual int incoming_damage(int current_damage){
        return current_damage;
    }

    virtual int outgoing_damage(int current_damage){
        return current_damage;
    }

    virtual int incoming_heal(int current_heal){
        return current_heal;
    }

    virtual int outgoing_heal(int current_heal){
        return current_heal;
    }
};