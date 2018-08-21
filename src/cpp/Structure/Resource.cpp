//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Resource.h>
#include <Map/GridBlock.h>

Resource::~Resource() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Resource::getBlock() {
    return block;
}

int Resource::getReward() {
    return 0;
}
