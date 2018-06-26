//
// Created by Theodore Tsivranidis on 6/26/18.
//

#include "Attacker.h"
#include "../Constants.h"

Attacker::Attacker(GridBlock &startingBlock) {
    this->setHealth(ATTACKER_HP);
    this->setBlock(startingBlock);
}