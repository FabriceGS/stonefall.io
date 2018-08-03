//
// Created by David Oyeka on 7/25/18.
//

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "Pathing/AStar.h"
#include "Config/Utility.h"

std::list<GridBlock> AStar::shortestPath(GridBlock const& src, GridBlock const& dest) {
    // TODO: Possible source of dramatic error, this pq stores GridBlock raw pointers for now.
    using heuristic_pair_t = std::pair<GridBlock*, double>;
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
    // The distancesFromSource map represents distance away from the source GridBlock.
    std::unordered_map<GridBlock, double> distancesFromSource;
    // The parents map represents the GridBlocks and their parents that were the cheapest way to reach them.
    std::unordered_map<GridBlock, GridBlock> parents;
    // The path is final path to take.
    std::list<GridBlock> path;

    // The GridBlock closest to the destination one can reach.
    weak_ptr<GridBlock> closest;
    for (const auto &weakNeighbor : dest.getNeighbors()) {
        if (auto neighbor = weakNeighbor.lock()) {
            if (neighbor != nullptr) {
                if (isUninitialized(closest)) {
                    closest = neighbor;
                } else {
                    if (auto close = closest.lock()) {
                        if (neighbor->getDistance(src) < close->getDistance(src)) {
                            closest = weakNeighbor;
                        }
                    }
                }
            }
        }
    }

    double closestDist = std::numeric_limits<double>::max();
    double distFromStart = std::numeric_limits<double>::max();

    // Initializing the distances from source map.
    distancesFromSource.insert(make_pair(src, 0.0));

    // Initializing the toVisit/parents map.
    for (const auto &weakNeighbor : src.getNeighbors()) {
        if (auto neighbor = weakNeighbor.lock()) {
            toVisit.push(make_pair(neighbor.get(), 1.0));
            distancesFromSource.insert(make_pair(*neighbor, 1.0));
            parents.insert(make_pair(*neighbor, src));
        }
    }
    visited.insert(src);

    while (!toVisit.empty()) {
        auto curr = toVisit.top().first;
        toVisit.pop();

        auto location = visited.find(*curr);
        if (location != visited.end()) {
            // TODO: Complete main loop...
        }
    }

    return std::list<GridBlock>();
}
