//
// Created by David Oyeka on 7/25/18.
//

#include <unordered_set>
#include <unordered_map>
#include "AStar.h"

template<class V>
std::list AStar<V>::shortestPath(V src, V dest) {
    std::unordered_set<V> visited;
    std::unordered_map<V, double> distances;
    std::unordered_map<V, V> parents;

    return std::list();
}
