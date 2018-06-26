//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDBLOCK_H
#define STONEFALL_GRIDBLOCK_H

#include "Interfaces/GridEntity.h"

class GridBlock {

    private:
        GridEntity entity;
        int& x;
        int& y;

    public:
        GridBlock(int& x, int& y);

        int getX() {return x;};
        int getY() {return y;};

        void populate(GridEntity ent) {entity = ent};
        void depopulate() {entity = nullptr;};

        GridEntity getEntity() {return entity;};
        bool isFull() {return entity != nullptr;};
};


#endif // STONEFALL_GRIDBLOCK_H
