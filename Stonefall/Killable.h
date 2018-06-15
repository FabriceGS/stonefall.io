//
// Created by Theodore Tsivranidis on 6/13/18.
//

#pragma once

#include "GridEntity.h"

class Killable : public GridEntity {

    private:
        double hp;

    public:
        virtual ~Killable() {};

        double getHealth() {return hp;};
        void setHealth(double newHp) {hp = newHp;};

        bool isDead() {return hp <= 0;};
        virtual int getReward() {};
};
