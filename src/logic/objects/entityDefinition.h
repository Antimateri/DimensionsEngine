#include "common.h"
#include "logic/objects/components/component.h"

class entityDefinition{
    std::string name;
    ComponentMask mask;
    std::vector<char*> components; 
};