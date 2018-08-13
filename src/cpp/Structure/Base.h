//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_BASE_H
#define STONEFALL_BASE_H

#include <Config/ReleaseConstants.h>
#include "AbstractClasses/Killable.h"

class Base : public Killable {
    private:
    public:
        Base(GridBlock &block) : Killable(block, Constants::BASE_HP) {}
        GridBlock& getBlock() override;
        int getReward() override;
};

#endif // STONEFALL_BASE_H