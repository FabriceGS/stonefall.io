//
// Created by Theodore Tsivranidis on 6/13/18.
//

#ifndef STONEFALL_BASE_H
#define STONEFALL_BASE_H

#include "../Interfaces/Killable.h"

class Base : public Killable {
    private:

    public:
        Base(GridBlock& startingBlock);

};

#endif // STONEFALL_BASE_H