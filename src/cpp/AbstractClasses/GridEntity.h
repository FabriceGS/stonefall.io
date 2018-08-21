//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDENTITY_H
#define STONEFALL_GRIDENTITY_H

#include <memory>

class GridBlock;

class GridEntity {
    protected:
        std::weak_ptr<GridBlock> block;

    public:
        // Marked explicit to prevent splicing during function calls on GridEntity values.
        explicit GridEntity(const std::shared_ptr<GridBlock> &block) : block(block) { }
        void setBlock(std::shared_ptr<GridBlock> block) {block = block;}
        virtual std::weak_ptr<GridBlock> getBlock() = 0;
};

#endif // STONEFALL_GRIDENTITY_H