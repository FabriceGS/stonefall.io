//
// Created by Theodore Tsivranidis on 6/13/18.
//
#include <Structure/Base.h>
#include <Map/GridBlock.h>

Base::~Base() {
    block.depopulate();
    cout << string("block (") << block.getX() << string(",") << block.getY() << string(") depopulated");
}

GridBlock& Base::getBlock() {
    return block;
}

int Base::getReward() {
    return 0;
}