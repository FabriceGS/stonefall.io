//
// Created by David Oyeka on 8/12/18.
//

#ifndef STONEFALL_SCAFFOLD_H
#define STONEFALL_SCAFFOLD_H


#include "AbstractClasses/Killable.h"

class Scaffold : public Killable {
    private:

    public:
        Scaffold(GridBlock &block, int hp) : Killable(block, hp) { }
};


#endif //STONEFALL_SCAFFOLD_H
