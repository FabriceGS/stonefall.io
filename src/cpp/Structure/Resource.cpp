//
// Created by David Oyeka on 6/25/18.
//

#include "Resource.h"
#include "../Constants.h"

Resource::Resource(GridBlock &startingBlock) {
    this->setHealth(RESOURCE_HP);
    this->setBlock(startingBlock);
}
