#include "logic/algorithms.h"
#include "logic/objects/component.h"

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(int x, int y, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (x - dest.first) * (x - dest.first)
        + (y - dest.second) * (y - dest.second)));
}
 
// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
bool getPath(World::mapRepresentation& map, int beginx, int beginy, int endx, int endy, std::list<std::pair<int,int>>& out){
    // If the source is out of range
    if (!map.isValid(beginx, beginy))
        return 0;
 
    // If the destination is out of range
    if (!map.isValid(endx, endy))
        return 0;
 
    // If the destination cell is the same as source cell
    if (beginx==endx && beginy==endy)
        return 0;
 
    // means that no cell has been included yet This closed
    std::unordered_set<long long> closedList;
 
    // Declare a 2D array of structure to hold the details
    // of that cell
    std::unordered_map<long long,cell> cellDetails;
 
    /*int i, j;
 
    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }*/
 
    // Initialising the parameters of the starting node
    long long has=map.hashCoord(beginx, beginy);
    cellDetails.insert({has,{beginx, beginy, 0, 0, 0}});
 
    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair of
     pair.*/
    std::set<pPair> openList;
 
    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(std::make_pair(0.0, std::make_pair(beginx, beginy)));
 
    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;
 
    while (!openList.empty()) {
        pPair p = *openList.begin();
 
        // Remove this vertex from the open list
        openList.erase(openList.begin());
 
        // Add this vertex to the closed list
        int i = p.second.first;
        int j = p.second.second;
        closedList.insert(map.hashCoord(i,j));
 
        /*
         Generating all the 8 successor of this cell
 
             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E
 
         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/
 
        // To store the 'g', 'h' and 'f' of the 8 successors
        double gNew, hNew, fNew;
 
        //----------- 1st Successor (North) ------------
 
        // Only process this cell if this is a valid one
        if (map.isValid(i - 1, j) && !map.getBlock(directions::top,i-1,j)) {
            has=map.hashCoord(i-1,j);
            // If the destination cell is the same as the
            // current successor
            if (i-1 == endx && j == endy) {
                // Set the Parent of the destination cell
                if(!cellDetails.count(has))
                    cellDetails.insert({has,{i, j, 0, 0, 0}});
                else{
                    cellDetails[has].parent_i=i;
                    cellDetails[has].parent_j=j;
                }
                foundDest = true;
                break;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList.count(has)) {
                gNew = cellDetails[map.hashCoord(i,j)].g + 1.0;
                hNew = calculateHValue(i - 1, j, {endx, endy});
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (!cellDetails.count(has)){
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j)));
                    cellDetails.insert({has,{i, j, fNew, gNew, hNew}});
                }
                else if(cellDetails[has].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i - 1, j)));
 
                    // Update the details of this cell
                    cellDetails[has].f = fNew;
                    cellDetails[has].g = gNew;
                    cellDetails[has].h = hNew;
                    cellDetails[has].parent_i = i;
                    cellDetails[has].parent_j = j;
                }
            }
        }
 
        //----------- 2nd Successor (South) ------------
 
        // Only process this cell if this is a valid one
        if (map.isValid(i + 1, j) && !map.getBlock(directions::bottom,i+1,j)) {
            has=map.hashCoord(i+1,j);
            // If the destination cell is the same as the
            // current successor
            if (i+1 == endx && j == endy) {
                // Set the Parent of the destination cell
                if(!cellDetails.count(has))
                    cellDetails.insert({has,{i, j, 0, 0, 0}});
                else{
                    cellDetails[has].parent_i=i;
                    cellDetails[has].parent_j=j;
                }
                foundDest = true;
                break;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList.count(has)) {
                gNew = cellDetails[map.hashCoord(i,j)].g + 1.0;
                hNew = calculateHValue(i + 1, j, {endx, endy});
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (!cellDetails.count(has)){
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j)));
                    cellDetails.insert({has,{i, j, fNew, gNew, hNew}});
                }
                else if(cellDetails[has].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i + 1, j)));
 
                    // Update the details of this cell
                    cellDetails[has].f = fNew;
                    cellDetails[has].g = gNew;
                    cellDetails[has].h = hNew;
                    cellDetails[has].parent_i = i;
                    cellDetails[has].parent_j = j;
                }
            }
        }
 
        //----------- 3rd Successor (East) ------------
 
        // Only process this cell if this is a valid one
        if (map.isValid(i, j + 1) && !map.getBlock(directions::top,i,j + 1)) {
            has=map.hashCoord(i,j + 1);
            // If the destination cell is the same as the
            // current successor
            if (i == endx && j+1 == endy) {
                // Set the Parent of the destination cell
                if(!cellDetails.count(has))
                    cellDetails.insert({has,{i, j, 0, 0, 0}});
                else{
                    cellDetails[has].parent_i=i;
                    cellDetails[has].parent_j=j;
                }
                foundDest = true;
                break;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList.count(has)) {
                gNew = cellDetails[map.hashCoord(i,j)].g + 1.0;
                hNew = calculateHValue(i, j + 1, {endx, endy});
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (!cellDetails.count(has)){
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j + 1)));
                    cellDetails.insert({has,{i, j, fNew, gNew, hNew}});
                }
                else if(cellDetails[has].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[has].f = fNew;
                    cellDetails[has].g = gNew;
                    cellDetails[has].h = hNew;
                    cellDetails[has].parent_i = i;
                    cellDetails[has].parent_j = j;
                }
            }
        }
 
        //----------- 4th Successor (West) ------------
 
        // Only process this cell if this is a valid one
        if (map.isValid(i, j - 1) && !map.getBlock(directions::top,i,j - 1)) {
            has=map.hashCoord(i,j - 1);
            // If the destination cell is the same as the
            // current successor
            if (i == endx && j-1 == endy) {
                // Set the Parent of the destination cell
                if(!cellDetails.count(has))
                    cellDetails.insert({has,{i, j, 0, 0, 0}});
                else{
                    cellDetails[has].parent_i=i;
                    cellDetails[has].parent_j=j;
                }
                foundDest = true;
                break;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (!closedList.count(has)) {
                gNew = cellDetails[map.hashCoord(i,j)].g + 1.0;
                hNew = calculateHValue(i, j - 1, {endx, endy});
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (!cellDetails.count(has)){
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));
                    cellDetails.insert({has,{i, j, fNew, gNew, hNew}});
                }
                else if(cellDetails[has].f > fNew) {
                    openList.insert(std::make_pair(
                        fNew, std::make_pair(i, j - 1)));
 
                    // Update the details of this cell
                    cellDetails[has].f = fNew;
                    cellDetails[has].g = gNew;
                    cellDetails[has].h = hNew;
                    cellDetails[has].parent_i = i;
                    cellDetails[has].parent_j = j;
                }
            }
        }
 
 /*
        //----------- 5th Successor (North-East)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j + 1] == false
                     && isUnBlocked(grid, i - 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j + 1].f == FLT_MAX
                    || cellDetails[i - 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }
 
        //----------- 6th Successor (North-West)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i - 1, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i - 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i - 1][j - 1] == false
                     && isUnBlocked(grid, i - 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i - 1][j - 1].f == FLT_MAX
                    || cellDetails[i - 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i - 1, j - 1)));
                    // Update the details of this cell
                    cellDetails[i - 1][j - 1].f = fNew;
                    cellDetails[i - 1][j - 1].g = gNew;
                    cellDetails[i - 1][j - 1].h = hNew;
                    cellDetails[i - 1][j - 1].parent_i = i;
                    cellDetails[i - 1][j - 1].parent_j = j;
                }
            }
        }
 
        //----------- 7th Successor (South-East)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j + 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j + 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j + 1].parent_i = i;
                cellDetails[i + 1][j + 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j + 1] == false
                     && isUnBlocked(grid, i + 1, j + 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j + 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j + 1].f == FLT_MAX
                    || cellDetails[i + 1][j + 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j + 1)));
 
                    // Update the details of this cell
                    cellDetails[i + 1][j + 1].f = fNew;
                    cellDetails[i + 1][j + 1].g = gNew;
                    cellDetails[i + 1][j + 1].h = hNew;
                    cellDetails[i + 1][j + 1].parent_i = i;
                    cellDetails[i + 1][j + 1].parent_j = j;
                }
            }
        }
 
        //----------- 8th Successor (South-West)
        //------------
 
        // Only process this cell if this is a valid one
        if (isValid(i + 1, j - 1) == true) {
            // If the destination cell is the same as the
            // current successor
            if (isDestination(i + 1, j - 1, dest) == true) {
                // Set the Parent of the destination cell
                cellDetails[i + 1][j - 1].parent_i = i;
                cellDetails[i + 1][j - 1].parent_j = j;
                printf("The destination cell is found\n");
                tracePath(cellDetails, dest);
                foundDest = true;
                return;
            }
 
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i + 1][j - 1] == false
                     && isUnBlocked(grid, i + 1, j - 1)
                            == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHValue(i + 1, j - 1, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i + 1][j - 1].f == FLT_MAX
                    || cellDetails[i + 1][j - 1].f > fNew) {
                    openList.insert(make_pair(
                        fNew, make_pair(i + 1, j - 1)));
 
                    // Update the details of this cell
                    cellDetails[i + 1][j - 1].f = fNew;
                    cellDetails[i + 1][j - 1].g = gNew;
                    cellDetails[i + 1][j - 1].h = hNew;
                    cellDetails[i + 1][j - 1].parent_i = i;
                    cellDetails[i + 1][j - 1].parent_j = j;
                }
            }
        }
        */
    }
 
    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destination cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    if (foundDest == false)
        return 0;
 
    int i,j;
    i=endx;
    j=endy;

    while(1){
        if(i==beginx && j==beginy)
            break;

        has=map.hashCoord(i,j);
        out.push_front({i,j});
        i=cellDetails[has].parent_i;
        j=cellDetails[has].parent_j;

    }

    return 1;
}