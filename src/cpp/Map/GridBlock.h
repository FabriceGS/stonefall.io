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
        weak_ptr<GridEntity> entity;
        array<weak_ptr<GridBlock>, 8> neighbors;
        const int x;
        const int y;

    public:
        GridBlock(int x, int y);
        ~GridBlock();

        void setNeighbors(const array<weak_ptr<GridBlock>, 8> &neighbors);
        const array<weak_ptr<GridBlock>, 8> & getNeighbors() const;

        int getX() const {return x;};
        int getY() const {return y;};

        double getDistance(GridBlock const& dest);

        void populate(const shared_ptr<GridEntity> &ent) {entity = ent;};
        void depopulate() { entity.reset();};

        weak_ptr<GridEntity> getEntity() {return entity; };
        bool isFull() const {return !entity.expired();};

        // Equals operator overload.
        bool operator==(GridBlock const& other) const {
            return x == other.getX() && y == other.getY();
        }

        bool operator!=(GridBlock const& other) const {
            return !(*this == other);
        }

};

// hash function for GridBlock.
namespace std
{
    template <>
    struct hash<GridBlock>
    {
        size_t operator()(GridBlock const& block) const
        {
            return ((hash<int>()(block.getY())) ^ (hash<int>()(block.getY()) << 1) >> 1);
        }
    };
}


#endif // STONEFALL_GRIDBLOCK_H
