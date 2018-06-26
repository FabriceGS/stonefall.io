//
// Created by David Oyeka on 6/25/18.
//

#include "Wall.h"
#include "../Constants.h"

Wall::Wall(GridBlock &startingBlock) {
    this->setHealth(WALL_HP);
    this->setBlock(startingBlock);
}
