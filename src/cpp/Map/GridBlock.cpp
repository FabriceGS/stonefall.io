//
// Created by Theodore Tsivranidis on 6/13/18.
//

#include "GridBlock.h"

GridBlock::GridBlock(int x, int y) : x(x), y(y) {
    cout << std::string("GridBlock ") + std::to_string(stat) + std::string(" created") << endl;
    stat++;
}

array<weak_ptr<GridBlock>, 8> &GridBlock::getNeighbors() {
    return neighbors;
}

void GridBlock::setNeighbors(const array<weak_ptr<GridBlock>, 8> &neighbors) {
    GridBlock::neighbors = neighbors;
}

GridBlock::~GridBlock() {
    cout << std::string("GridBlock ") + std::to_string(stat) + std::string(" destroyed") << endl;
    stat--;
}
