//
// Created by David Oyeka on 6/29/18.
//

#include "Grid.h"

array<array<shared_ptr<GridBlock>, BOARD_LENGTH>, BOARD_WIDTH> Grid::gridBlocks;

void Grid::createEdges() {
    // TODO: Implement...
}

void Grid::buildGrid() {
    // Building the 2D array of GridBlock pointers.
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            gridBlocks[i][j] = make_shared<GridBlock>(i, j);
        }
    }

    // Connecting the GridBlocks.
    createEdges();
}

bool Grid::validateCoordinates(int x, int y) {
    return x >= 0
           && x < BOARD_WIDTH
           && y >= 0
           && y < BOARD_LENGTH
           && getGridBlock(x, y)->get()->isFull();
}

bool Grid::isWithinNBlocks(int n, GridBlock const& source, GridBlock const& target) {
    return source.getX() - target.getX() <= n && source.getY() - target.getY() <= n;
}

optional<shared_ptr<GridBlock>> Grid::getGridBlock(int x, int y) {
    if (x >= 0 && x < BOARD_WIDTH && y>= 0 && y < BOARD_LENGTH) {
        return optional(gridBlocks[x][y]);
    }
    return nullopt;
}
