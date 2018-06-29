//
// Created by David Oyeka on 6/29/18.
//

#ifndef STONEFALL_GRID_H
#define STONEFALL_GRID_H

#include <array>
#include <experimental/optional>
#include "../Constants.h"
#include "GridBlock.h"

using namespace std;
using namespace std::experimental;

class Grid {
    private:
        Grid();
        ~Grid();
        static shared_ptr<GridBlock> gridBlocks[BOARD_LENGTH][BOARD_WIDTH];
        static void createEdges();

    public:
        const optional<shared_ptr<GridBlock>> static getGridBlock(int x, int y) {
            if (x >= 0 && x < BOARD_WIDTH && y>= 0 && y < BOARD_LENGTH) {
            return optional(gridBlocks[x][y]);
            }
            return nullopt;
        }
        static void buildGrid();
        const static bool validateCoordinates(int x, int y);
        const static bool isWithinNBlocks(int n, shared_ptr<GridBlock> source, shared_ptr<GridBlock> target);
};


#endif //STONEFALL_GRID_H
