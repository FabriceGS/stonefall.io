//
// Created by David Oyeka on 8/12/18.
//

#include "Scaffold.h"
#include <utility>
#include <Map/GridBlock.h>

Scaffold::Scaffold(std::shared_ptr<GridBlock> block, int type, std::string id)
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

Scaffold::~Scaffold() {
    if (auto sharedBlock = block.lock()) {
        sharedBlock->depopulate();
    }
}

std::weak_ptr<GridBlock> Scaffold::getBlock() {
    return block;
}

int Scaffold::getReward() {
    return 0;
}

int Scaffold::getType() {
    return type;
}

void Scaffold::update() {
    if (hp >= 0) {
        hp += Constants::SCAFFOLD_GENERATION_RATE;
    }
}

bool Scaffold::readyToUpgrade() const {
    if (hp >= maxHp) {
        return true;
    }
    return false;
}

bool Scaffold::isDead() const {
    return hp < 0;
}