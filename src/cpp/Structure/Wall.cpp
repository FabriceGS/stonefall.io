//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Wall.h>
#include <Map/GridBlock.h>

Wall::~Wall() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Wall::getBlock() {
    return block;
}

int Wall::getReward() {
    return 0;
}
