//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_TURRET_H
#define STONEFALL_TURRET_H


#include "Map/GridBlock.h"
#include "AbstractClasses/Killable.h"

class Turret : public Killable {
    private:

    public:
        Turret(GridBlock &block, double hp) : Killable(block, hp) { }
        GridBlock getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_TURRET_H
