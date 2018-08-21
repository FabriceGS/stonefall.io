//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Mine.h>
#include <Map/GridBlock.h>
#include <Config/ReleaseConstants.h>
#include "Mine.h"

Mine::~Mine() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Mine::getBlock() {
    return block;
}

int Mine::getReward() {
    return 0;
}

void Mine::collect(Resource &resource) {
    resource.decrementHealth(Constants::MINE_COLLECT_RATE);
}
