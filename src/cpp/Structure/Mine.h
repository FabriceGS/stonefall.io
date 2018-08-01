//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_MINE_H
#define STONEFALL_MINE_H


#include "../Map/GridBlock.h"
#include "../AbstractClasses/Killable.h"

class Mine : public Killable {
    private:

    public:
        Mine(GridBlock &block, double hp) : Killable(block, hp) { }
        GridBlock getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_MINE_H
