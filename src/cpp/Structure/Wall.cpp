//
// Created by David Oyeka on 6/25/18.
//
#include <Structure/Wall.h>
#include <Map/GridBlock.h>

GridBlock& Wall::getBlock() {
    return block;
}

int Wall::getReward() {
    return 0;
}
