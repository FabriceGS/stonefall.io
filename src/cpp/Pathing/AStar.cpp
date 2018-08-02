//
// Created by David Oyeka on 7/25/18.
//

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "AStar.h"

template<class V>
std::list<V> AStar<V>::shortestPath(V const& src, V const& dest) {
    using heuristic_pair_t = std::pair<V, double>;
    // The comparison lambda for the pair of a vertex and it's heuristic, calculated by adding
    // it's path distance from the source vertex and it's straight line distance to the destination vertex.
    auto shortest_heuristic_comp =
            [](heuristic_pair_t const& p1, heuristic_pair_t const& p2)
            { return p1.second > p2.second; };

    // The priority queue of a vertex and it's heuristic, where the smallest heuristic has the
    // greatest priority.
    std::priority_queue<heuristic_pair_t> toVisit(shortest_heuristic_comp);

    // The visited set represents vertexes that have already been 'visited' by the algorithm.
    std::unordered_set<V> visited;
    // The distances map represents distance away from the source vertex.
    std::unordered_map<V, double> distances;
    // The parents map represents the vertexes and their parents that were the cheapest way to reach them.
    std::unordered_map<V, V> parents;
    // The path is final path to take.
    std::list<V> path;
    // The closest vertex is the vertex we have passed closest to the destination.
    V closest;

    return std::list<V>();
}
