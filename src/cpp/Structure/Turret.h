//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_TURRET_H
#define STONEFALL_TURRET_H


#include "../GridBlock.h"
#include "../Interfaces/Killable.h"

class Turret : public Killable {
    private:

    public:
        Turret(GridBlock& startingBlock);
};


#endif //STONEFALL_TURRET_H
