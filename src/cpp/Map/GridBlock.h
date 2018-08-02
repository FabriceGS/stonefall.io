//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_GRIDBLOCK_H
#define STONEFALL_GRIDBLOCK_H

#include <memory>
#include <array>
#include <iostream>
#include "../AbstractClasses/GridEntity.h"

using namespace std;

class GridBlock {

    private:
        static int stat;
        shared_ptr<GridEntity> entity;
        array<weak_ptr<GridBlock>, 8> neighbors;
        const int x;
        const int y;

    public:
        GridBlock(int x, int y);
        ~GridBlock();

        void setNeighbors(const array<weak_ptr<GridBlock>, 8> &neighbors);
        array<weak_ptr<GridBlock>, 8> &getNeighbors();

        int getX() const {return x;};
        int getY() const {return y;};

        void populate(shared_ptr<GridEntity> ent) {entity = ent;};
        void depopulate() {entity = nullptr;};

        const shared_ptr<GridEntity> getEntity() {return entity;};
        const bool isFull() {return entity != nullptr;};

        bool operator==(GridBlock const& other) {
            return x == other.getX() && y == other.getY();
        }
};


#endif // STONEFALL_GRIDBLOCK_H
