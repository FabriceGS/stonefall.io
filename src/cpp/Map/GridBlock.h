//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDBLOCK_H
#define STONEFALL_GRIDBLOCK_H

#include <memory>
#include "../AbstractClasses/GridEntity.h"

using namespace std;

class GridBlock {

    private:
        shared_ptr<GridEntity> entity;
        const int x;
        const int y;

    public:
        GridBlock(int x, int y);

        int getX() const {return x;};
        int getY() const {return y;};

        void populate(shared_ptr<GridEntity> ent) {entity = ent;};
        void depopulate() {entity = nullptr;};

        const shared_ptr<GridEntity> getEntity() {return entity;};
        const bool isFull() {return entity != nullptr;};
};


#endif // STONEFALL_GRIDBLOCK_H
