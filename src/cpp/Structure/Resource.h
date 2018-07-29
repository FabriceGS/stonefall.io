//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_RESOURCE_H
#define STONEFALL_RESOURCE_H


#include "../AbstractClasses/Killable.h"

class Resource : public Killable {
    public:
        Resource(GridBlock &block, double hp) : Killable(block, hp) { }
        GridBlock getBlock() override;
        int getReward() override;

};


#endif //STONEFALL_RESOURCE_H
