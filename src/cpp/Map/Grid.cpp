//
// Created by David Oyeka on 6/29/18.
//

#include "Grid.h"

array<array<shared_ptr<GridBlock>, Constants::BOARD_LENGTH>, Constants::BOARD_WIDTH> Grid::gridBlocks;

// 0 - NW, 1 - N, 2 - NE, 3 - W, 4 - E, 5 - SW, 6 - S, 7 - SE
void Grid::createNeighbors() {
    for (int i = 0; i < Constants::BOARD_WIDTH; i++) {
        for (int j = 0; j < Constants::BOARD_LENGTH; j++) {
            int direction = 0;
            array<weak_ptr<GridBlock>, 8> neighbors;

            for (int m = i - 1; m <= i + 1; m++) {
                for (int n = j - 1; n <= j + 1; n++) {
                    if (m >= 0 && m < Constants::BOARD_WIDTH && n >= 0 && n < Constants::BOARD_LENGTH) {
                        if (m == i && n == j)
                            continue;

                        neighbors[direction] = gridBlocks[m][n];
                    }
                    direction++;
                }
            }
            gridBlocks[i][j]->setNeighbors(neighbors);
        }
    }}

void Grid::buildGrid() {
    // Building the 2D array of GridBlock pointers.
    for (int i = 0; i < Constants::BOARD_WIDTH; i++) {
        for (int j = 0; j < Constants::BOARD_LENGTH; j++) {
            gridBlocks[i][j] = make_shared<GridBlock>(i, j);
        }
    }

    // Connecting the GridBlocks.
    createNeighbors();
}

bool Grid::validateCoordinates(int x, int y) {
    return x >= 0
           && x < Constants::BOARD_WIDTH
           && y >= 0
           && y < Constants::BOARD_LENGTH
           && !getGridBlock(x, y)->get()->isFull();
}

bool Grid::isWithinNBlocks(int n, GridBlock const& source, GridBlock const& target) {
    return (source.getX() - target.getX()) <= n && (source.getY() - target.getY()) <= n;
}

optional<shared_ptr<GridBlock>> Grid::getGridBlock(int x, int y) {
    if (x >= 0 && x < Constants::BOARD_WIDTH && y>= 0 && y < Constants::BOARD_LENGTH) {
       return optional(gridBlocks[x][y]);
    }
    return nullopt;
}

Grid::Grid() {
    cout << std::string("Grid created") << endl;
}

Grid::~Grid() {
    cout << std::string("Grid destroyed") << endl;
}
