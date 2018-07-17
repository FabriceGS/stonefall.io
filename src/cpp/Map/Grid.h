//
// Created by David Oyeka on 6/29/18.
//

#ifndef STONEFALL_GRID_H
#define STONEFALL_GRID_H

#include <array>
#include <experimental/optional>
#include "../Constants.h"
#include "GridBlock.h"

using namespace std::experimental;

class Grid {
    private:
        static array<array<shared_ptr<GridBlock>, BOARD_LENGTH>, BOARD_WIDTH> gridBlocks;
        static void createNeighbors();

    public:
        static optional<shared_ptr<GridBlock>> getGridBlock(int x, int y);
        static void buildGrid();
        static bool validateCoordinates(int x, int y);
        static bool isWithinNBlocks(int n, GridBlock const& source, GridBlock const& target);
};


#endif //STONEFALL_GRID_H
