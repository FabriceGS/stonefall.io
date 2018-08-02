//
// Created by David Oyeka on 7/25/18.
//

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "AStar.h"

std::list<GridBlock> AStar::shortestPath(GridBlock const& src, GridBlock const& dest) {
    using heuristic_pair_t = std::pair<GridBlock, double>;
    using heuristic_container_t = std::vector<heuristic_pair_t>;
    // The comparison lambda for the pair of a GridBlock and it's heuristic, calculated by adding
    // it's path distance from the source GridBlock and it's straight line distance to the destination GridBlock.
    auto shortest_heuristic_comp =
            [](heuristic_pair_t const& p1, heuristic_pair_t const& p2)
            { return p1.second > p2.second; };

    // The priority queue of a GridBlock and it's heuristic, where the smallest heuristic has the
    // greatest priority.
    std::priority_queue<heuristic_pair_t, heuristic_container_t, decltype(shortest_heuristic_comp)> toVisit(shortest_heuristic_comp);

    // The visited set represents GridBlocks that have already been 'visited' by the algorithm.
    std::unordered_set<GridBlock> visited;
    // The distances map represents distance away from the source GridBlock.
    std::unordered_map<GridBlock, double> distances;
    // The parents map represents the GridBlocks and their parents that were the cheapest way to reach them.
    std::unordered_map<GridBlock, GridBlock> parents;
    // The path is final path to take.
    std::list<GridBlock> path;

    // The GridBlock closest to the destination one can reach.
    // GridBlock closest = dest.getNeighbors()[0];

    return std::list<GridBlock>();
}
