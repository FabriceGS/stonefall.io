//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Turret.h>
#include <Map/GridBlock.h>

Turret::~Turret() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Turret::getBlock() {
    return block;
}

int Turret::getReward() {
    return 0;
}
