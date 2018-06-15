//
// Created by Theodore Tsivranidis on 6/13/18.
//

#include "../Killable.h"


class Base : public Killable {
    private:
        double hp;
        GridBlock block;

    public:
        Base(GridBlock startingBlock);

};
