#include "common.h"
#include "logic/objects/components/component.h"

//entity definition to replicate specifications of entities
class entityDefinition{
    std::string name;
    ComponentMask mask;
    std::vector<char*> components; 
};