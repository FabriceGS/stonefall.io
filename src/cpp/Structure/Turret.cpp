//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Turret.h>
#include <Map/GridBlock.h>

Turret::~Turret() {
    block.depopulate();
}

GridBlock& Turret::getBlock() {
    return block;
}

int Turret::getReward() {
    return 0;
}
