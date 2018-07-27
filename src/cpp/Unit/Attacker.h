//
// Created by Theodore Tsivranidis on 6/26/18.
//

#ifndef STONEFALL_ATTACKER_H
#define STONEFALL_ATTACKER_H


#include "../Map/GridBlock.h"
#include "../AbstractClasses/Killable.h"

class Attacker : Killable {
    private:

    public:
        Attacker(GridBlock &block, double hp) : Killable(block, hp) { }
};


#endif //STONEFALL_ATTACKER_H
