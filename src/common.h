#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

#include "library.h"
#include "logic/dataStructures.h"

typedef std::bitset<MAX_COMPONENTS> ComponentMask;

typedef unsigned int EntityIndex;
typedef unsigned int EntityVersion;