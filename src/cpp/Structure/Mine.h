//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_MINE_H
#define STONEFALL_MINE_H


#include "Map/GridBlock.h"
#include "AbstractClasses/Killable.h"
#include "Resource.h"

class Mine : public Killable {
    private:

    public:
        explicit Mine(GridBlock &block) : Killable(block, Constants::MINE_HP) { }
        ~Mine();
        GridBlock& getBlock() override;
        int getReward() override;
        void collect(Resource& resource);
};


#endif //STONEFALL_MINE_H
