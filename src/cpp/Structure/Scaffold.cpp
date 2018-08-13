//
// Created by David Oyeka on 8/12/18.
//

#include "Scaffold.h"
#include <utility>

Scaffold::Scaffold(GridBlock &block, int type, std::string id)
: Killable(block, 0), type(type), id(std::move(id)) {
    switch (type) {
        case STRUCTURE_TYPE::MINE: {
            maxHp = 2 * Constants::MINE_HP;
            break;
        }
        case STRUCTURE_TYPE::TURRET: {
            maxHp = 2 * Constants::TURRET_HP;
            break;
        }
        case STRUCTURE_TYPE::WALL: {
            maxHp = 2 * Constants::WALL_HP;
            break;
        }
        default:
            break;
    }
}

GridBlock& Scaffold::getBlock() {
    return block;
}

int Scaffold::getReward() {
    return 0;
}

void Scaffold::update() {
    if (hp >= 0) {
        hp += Constants::SCAFFOLD_GENERATION_RATE;
    }
}

bool Scaffold::readyToUpgrade() {
    if (hp >= maxHp) {
        return true;
    }
    return false;
}