#include <utility>

//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_TURRET_H
#define STONEFALL_TURRET_H


#include <Config/ReleaseConstants.h>
#include "Map/GridBlock.h"
#include "AbstractClasses/Killable.h"

class Turret : public Killable {
    public:
        explicit Turret(std::shared_ptr<GridBlock> block) :
            Killable(std::move(block), Constants::TURRET_HP) { }
        ~Turret();
        std::weak_ptr<GridBlock> getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_TURRET_H
