//
// Created by David Oyeka on 6/25/18.
//

#ifndef STONEFALL_MINE_H
#define STONEFALL_MINE_H


#include "../GridBlock.h"
#include "../Killable.h"

class Mine : public Killable {
    private:

    public:
        Mine(GridBlock& startingBlock);

};


#endif //STONEFALL_MINE_H
