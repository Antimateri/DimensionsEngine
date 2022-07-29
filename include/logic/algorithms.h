#pragma once

#include <algorithm>
#include "common.h"
#include "logic/objects/world.h"

typedef std::pair<int, int> Pair;
 
// Creating a shortcut for pair<int, pair<int, int>> type
typedef std::pair<double, std::pair<int, int> > pPair;
 
// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};
 
// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int x, int y, Pair dest);
 
// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
bool getPath(World::mapRepresentation& map, int beginx, int beginy, int endx, int endy, std::list<Pair>& out);