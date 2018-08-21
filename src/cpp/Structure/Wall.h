#include <utility>

//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_WALL_H
#define STONEFALL_WALL_H

#include <Config/ReleaseConstants.h>
#include "Map/GridBlock.h"
#include "AbstractClasses/Killable.h"

class Wall : public Killable {
    public:
        Wall(std::shared_ptr<GridBlock> block) :
            Killable(std::move(block), Constants::WALL_HP) { }
        ~Wall();
        std::weak_ptr<GridBlock> getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_WALL_H
