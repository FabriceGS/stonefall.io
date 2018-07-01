//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDENTITY_H
#define STONEFALL_GRIDENTITY_H

class GridBlock;

class GridEntity {
    private:
        GridBlock& block;
    public:
        explicit GridEntity(GridBlock &block) : block(block) { }
        virtual GridBlock getBlock() = 0;
};

#endif // STONEFALL_GRIDENTITY_H