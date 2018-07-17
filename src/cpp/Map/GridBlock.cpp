//
// Created by Theodore Tsivranidis on 6/13/18.
//

#include "GridBlock.h"

GridBlock::GridBlock(int x, int y) : x(x), y(y) { }

array<shared_ptr<GridBlock>, 8> &GridBlock::getNeighbors() {
    return neighbors;
}

void GridBlock::setNeighbors(const array<shared_ptr<GridBlock>, 8> &neighbors) {
    GridBlock::neighbors = neighbors;
}
