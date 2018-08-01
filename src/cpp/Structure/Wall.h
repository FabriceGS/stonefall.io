//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_WALL_H
#define STONEFALL_WALL_H


#include "../Map/GridBlock.h"
#include "../AbstractClasses/Killable.h"

class Wall : public Killable {
    public:

    private:
        Wall(GridBlock &block, double hp) : Killable(block, hp) { }
        GridBlock getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_WALL_H
