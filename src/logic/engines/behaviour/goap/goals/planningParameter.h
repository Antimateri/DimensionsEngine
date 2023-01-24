//different goals and states for planning, both are codified in planningParameter
#pragma once

#include "common.h"

class planningParameter{
protected:
    int _priority;
    EntityID _owner;
    std::string _name;
    int _id;
    int _status;

public:
    planningParameter() : _priority(0) {}
    planningParameter(int priority, int id) : _priority(priority), _id(id) {}
    ~planningParameter() {}

    virtual bool satisfies(planningParameter *parameter){return false;};    //if this is satiesfied the parameter is satisfied?
    
    //comparasion operators, sintax sugar if you may
    virtual bool operator==(planningParameter *parameter){return false;};
    bool operator!=(planningParameter *parameter){
        return !((*this)==parameter);
    };
    bool operator<(planningParameter *parameter){
        return !satisfies(parameter);
    }
    bool operator>=(planningParameter *parameter){
        return satisfies(parameter);
    }
    bool operator<=(planningParameter *parameter){
        return ((*this)==parameter) || !satisfies(parameter);
    }
    bool operator>(planningParameter *parameter){
        return !((*this)<=parameter);
    }

    //copies the important information into a new object
    virtual planningParameter* replicate(){return (new planningParameter())->setOwner(getOwner());}

    //in case it becoming active triggers something
    virtual void activate(){}
    virtual void deactivate(){}

    //sum and substraction of parameters and goals, for example if you add a goal of 25 action 
    //points to a goal of 10 action points you get a goal of 35 action points
    virtual planningParameter* add(planningParameter *parameter){
        if(parameter->getID()==getID()){
            return this;
        }
        return nullptr;
    }

    virtual planningParameter* substract(planningParameter *parameter){
        if(parameter->getID()==getID()){
            return nullptr;
        }
        return this;
    }

    //if the parameter is applicable to the situation (can be activated as a goal)
    virtual bool aplicable(std::unordered_map<int, planningParameter*>* situation){return true;}

    //if the goal is satisfied
    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world){return false;}
    //if the preconditions to considerer the goal are satisfied
    virtual bool satisfyPreconditions(){return false;}

    virtual planningParameter* setPriority(int priority){
        _priority=priority;
        return this;
    }
    
    virtual int getPriority(){
        return _priority;
    }

    virtual planningParameter* setOwner(EntityID owner){
        _owner=owner;
        return this;
    }
    virtual EntityID getOwner(){
        return _owner;
    }

    virtual planningParameter* setName(const std::string &name){
        _name=name;
        return this;
    }

    virtual const std::string &getName(){
        return _name;
    }

    virtual const int getID() const{
        return _id;
    }

    //encapsulation on whatever the parameter stores, for example action points goal would store a number
    virtual planningParameter* setInfo(char* data){return this;}
    virtual char* getInfo(){return nullptr;}

};

//the entity wants to move
class planMove: public planningParameter{
public:
    planMove() : planningParameter(100,100) {}

    virtual bool satisfies(planningParameter *parameter){
        return true;
    }

    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world){
        return situation != nullptr && (*situation).count(getID());
    }

    virtual planningParameter* replicate(){return (new planMove())->setOwner(getOwner());}

};

//the entity needs/have a certain amount of action points
class planHasAP: public planningParameter{
private:
    int _ap;
public:
    planHasAP(int ap) : planningParameter(101,101), _ap(ap) {}

    virtual bool satisfies(planningParameter *parameter);

    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world);

    virtual planningParameter* add(planningParameter *parameter){
        if(parameter->getID()==getID()){
            this->_ap+=*(parameter->getInfo());
            return this;
        }
        return nullptr;
    }

    virtual planningParameter* substract(planningParameter *parameter){
        if(parameter->getID()==getID()){
            if(_ap-*(parameter->getInfo())<=0){
                return nullptr;
            }
            this->_ap-=*(parameter->getInfo());
            return this;
        }
        return this;
    }

    virtual planningParameter* replicate(){return (new planHasAP(_ap))->setOwner(getOwner());}

    virtual planningParameter* setInfo(char* data);
    virtual char* getInfo();

};

class isNotOccupiedPlan: public planningParameter{
    public:
        isNotOccupiedPlan() : planningParameter(102,102) {}

        virtual bool satisfies(planningParameter *parameter){
            return true;
        }

        virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation, World* _world);

        virtual planningParameter* replicate(){return (new isNotOccupiedPlan())->setOwner(getOwner());}
};