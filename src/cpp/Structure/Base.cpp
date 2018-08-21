//
// Created by Theodore Tsivranidis on 6/13/18.
//
#include <Structure/Base.h>
#include <Map/GridBlock.h>
#include <vector>
#include <algorithm>

Base::~Base() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Base::getBlock() {
    return block;
}

int Base::getReward() {
    return 0;
}