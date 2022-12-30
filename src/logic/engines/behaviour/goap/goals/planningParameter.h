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

    virtual bool satisfies(planningParameter *parameter){return false;};
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

    virtual void activate(){}
    virtual void deactivate(){}

    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation){return false;}
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

    virtual planningParameter* setInfo(char* data){return this;}
    virtual char* getInfo(){return nullptr;}

};

planningParameter *max(planningParameter *a, planningParameter *b);

class planMove: public planningParameter{
public:
    planMove() : planningParameter(100,100) {}

    virtual bool satisfies(planningParameter *parameter){
        return true;
    }

    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation){
        return true;
    }

};

class planHasAP: public planningParameter{
private:
    int _ap;
public:
    planHasAP(int ap) : planningParameter(101,101), _ap(ap) {}

    virtual bool satisfies(planningParameter *parameter);

    virtual bool isSatisfied(std::unordered_map<int, planningParameter*>* situation);

    virtual planningParameter* setInfo(char* data);
    virtual char* getInfo();

};