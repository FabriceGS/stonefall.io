//
// Created by David Oyeka on 7/25/18.
//

#ifndef STONEFALL_ASTAR_H
#define STONEFALL_ASTAR_H

#include <list>
#include <Map/GridBlock.h>

template <class V>
class AStar {
    public:
        std::list<V> shortestPath(V const& src, V const& dest);
};

//template <>
//class AStar<GridBlock> {
//    public:
//        std::list<GridBlock> shortestPath(GridBlock const& src, GridBlock const& dest);
//};


#endif //STONEFALL_ASTAR_H
