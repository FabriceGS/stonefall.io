//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDENTITY_H
#define STONEFALL_GRIDENTITY_H

#include "GridBlock.h"

class GridEntity {
    private:
        GridBlock& block;

    public:
        virtual ~GridEntity() {};

        GridBlock getBlock() {return block;}    ;

        void setBlock(GridBlock& toSet) {block = toSet;};
};

#endif // STONEFALL_GRIDENTITY_H