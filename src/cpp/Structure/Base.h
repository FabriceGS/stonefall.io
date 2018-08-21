#include <utility>

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
        explicit Base(std::shared_ptr<GridBlock> block) :
            Killable(std::move(block), Constants::BASE_HP) {}
        ~Base();
        std::weak_ptr<GridBlock> getBlock() override;
        int getReward() override;
};

#endif // STONEFALL_BASE_H