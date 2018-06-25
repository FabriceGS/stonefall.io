//
// Created by David Oyeka on 6/25/18.
//

#include "Mine.h"
#include "../Constants.h"

Mine::Mine(GridBlock &startingBlock) {
    this->setHealth(MINE_HP);
    this->setBlock(startingBlock);
}