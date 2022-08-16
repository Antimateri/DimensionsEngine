#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

#include "definitions.h"
#include "logic/dataStructures.h"
#include "library.h"

typedef std::bitset<MAX_COMPONENTS> ComponentMask;

typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;
