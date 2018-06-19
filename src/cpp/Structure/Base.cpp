//
// Created by Theodore Tsivranidis on 6/13/18.
//

#include "Base.h"


Base::Base(GridBlock startingBlock) {
    this->setHealth(500);
    this->setBlock(startingBlock);
}