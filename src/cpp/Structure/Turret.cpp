//
// Created by David Oyeka on 6/25/18.
//

#include "Turret.h"
#include "../Constants.h"

Turret::Turret(GridBlock &startingBlock) {
    this->setHealth(TURRET_HP);
    this->setBlock(startingBlock);
}
