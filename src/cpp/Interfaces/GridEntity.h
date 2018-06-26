//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDENTITY_H
#define STONEFALL_GRIDENTITY_H

#include "../GridBlock.h"

class GridEntity {
    private:
        GridBlock& block;

    public:
        virtual ~GridEntity() {};

        void setBlock(GridBlock& toSet) {block = toSet;};

        GridBlock getBlock() {return block;};

        int getX() {return block.getX();};
        int getY() {return block.getY();};

};

#endif // STONEFALL_GRIDENTITY_H