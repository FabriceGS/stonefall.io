//
// Created by Theodore Tsivranidis on 6/13/18.
//
#pragma once

#include "GridBlock.h"

class GridEntity {
    private:
        GridBlock block;

    public:
        virtual ~GridEntity() {};

        GridBlock getBlock() {return block;}    ;

        void setBlock(GridBlock toSet) {block = toSet;};
};
