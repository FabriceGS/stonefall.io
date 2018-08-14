//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_RESOURCE_H
#define STONEFALL_RESOURCE_H


#include <Config/ReleaseConstants.h>
#include "AbstractClasses/Killable.h"

class Resource : public Killable {
    public:
        explicit Resource(GridBlock &block) : Killable(block, Constants::RESOURCE_HP) { }
        ~Resource();
        GridBlock& getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_RESOURCE_H
