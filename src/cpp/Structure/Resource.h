#include <utility>

//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_RESOURCE_H
#define STONEFALL_RESOURCE_H


#include <Config/ReleaseConstants.h>
#include "AbstractClasses/Killable.h"

class Resource : public Killable {
    public:
        explicit Resource(std::shared_ptr<GridBlock> block) :
            Killable(std::move(block), Constants::RESOURCE_HP) { }
        ~Resource();
        std::weak_ptr<GridBlock> getBlock() override;
        int getReward() override;
};


#endif //STONEFALL_RESOURCE_H
