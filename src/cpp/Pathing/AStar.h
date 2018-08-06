//
// Created by David Oyeka on 7/25/18.
//

#ifndef STONEFALL_ASTAR_H
#define STONEFALL_ASTAR_H
#define NEIGHBOR_DISTANCE 1.0

#include <list>
#include <Map/GridBlock.h>

class AStar {
    public:
        static std::list<GridBlock*> shortestPath(GridBlock* const& src, GridBlock* const& dest);
        static void printPath(std::list<GridBlock*> path);
};

#endif //STONEFALL_ASTAR_H
