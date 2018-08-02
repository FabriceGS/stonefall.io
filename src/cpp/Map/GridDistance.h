//
// Created by David Oyeka on 8/2/18.
//

#ifndef STONEFALL_DISTANCE_H
#define STONEFALL_DISTANCE_H

#include <math.h>
#include "GridBlock.h"

double getSquareDistance(GridBlock const& src, GridBlock const& dest) {
    return pow(dest.getX() - src.getX(), 2) + pow(dest.getY() - src.getY(), 2);
}

#endif //STONEFALL_DISTANCE_H
