//
// Created by David Oyeka on 6/29/18.
//

#ifndef STONEFALL_GRID_H
#define STONEFALL_GRID_H

#include <array>
#include <experimental/optional>
#include "Config/ReleaseConstants.h"
#include "GridBlock.h"

using namespace std::experimental;

class Grid {
private:
    array<array<shared_ptr<GridBlock>, Constants::BOARD_LENGTH>, Constants::BOARD_WIDTH> gridBlocks;
    void createNeighbors();

public:
    Grid();
    ~Grid();
    optional<shared_ptr<GridBlock>> getGridBlock(int x, int y);
    void buildGrid();
    bool validateCoordinates(int x, int y);
    bool isWithinNBlocks(int n, GridBlock const& source, GridBlock const& target);
};


#endif //STONEFALL_GRID_H
