//
// Created by Theodore Tsivranidis on 6/13/18.
//

#include "Base.h"
#include "../Constants.h"

Base::Base(GridBlock& startingBlock) {
    this->setHealth(BASE_HP);
    this->setBlock(startingBlock);
}