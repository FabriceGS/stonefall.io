//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_KILLABLE_H
#define STONEFALL_KILLABLE_H

#include <atomic>
#include "GridEntity.h"

class Killable : public GridEntity {
    protected:
        std::atomic_int hp;

    public:
        Killable(GridBlock& block, int hp) : GridEntity(block), hp(hp) {}
        double getHealth() const {return hp;};
        void setHealth(int newHp) {hp = newHp;};
        void incrementHealth(int amount) {hp += amount;};
        void decrementHealth(int amount) {hp -= amount;};

        virtual bool isDead() const {return hp <= 0;};
        virtual int getReward() = 0;
};

#endif // STONEFALL_KILLABLE_H