//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_KILLABLE_H
#define STONEFALL_KILLABLE_H

#include "GridEntity.h"

class Killable : public GridEntity {
    private:
        double hp;

    public:
        Killable(GridBlock& block, double hp) : GridEntity(block), hp(hp) {}
        const double getHealth() {return hp;};
        void setHealth(double newHp) {hp = newHp;};
        const bool isDead() {return hp <= 0;};
        virtual int getReward() = 0;
};

#endif // STONEFALL_KILLABLE_H