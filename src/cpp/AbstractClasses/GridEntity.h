//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDENTITY_H
#define STONEFALL_GRIDENTITY_H

class GridBlock;

class GridEntity {
    protected:
        GridBlock& block;

    public:
        // Marked explicit to prevent splicing during function calls on GridEntity values.
        explicit GridEntity(GridBlock& block) : block(block) { }
        virtual GridBlock getBlock() = 0;
};

#endif // STONEFALL_GRIDENTITY_H