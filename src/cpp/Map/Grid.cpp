//
// Created by David Oyeka on 6/29/18.
//

#include "Grid.h"

//const optional<shared_ptr<GridBlock>> Grid::getGridBlock(int x, int y) {
//    if (x >= 0 && x < BOARD_WIDTH && y>= 0 && y < BOARD_LENGTH) {
//        return optional(gridBlocks[x][y]);
//    }
//    return nullopt;
//}

void Grid::createEdges() {

}

void Grid::buildGrid() {

}

const bool Grid::validateCoordinates(int x, int y) {
    return false;
}

const bool Grid::isWithinNBlocks(int n, shared_ptr<GridBlock> source, shared_ptr<GridBlock> target) {
    return false;
}
