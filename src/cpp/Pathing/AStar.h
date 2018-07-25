//
// Created by David Oyeka on 7/25/18.
//

#ifndef STONEFALL_ASTAR_H
#define STONEFALL_ASTAR_H

#include <list>

template <class V>
class AStar {
    public:
        std::list shortestPath(V src, V dest);
};


#endif //STONEFALL_ASTAR_H
