//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include "Player.h"


class Game {

public:
    static bool
    playerExists(std::string);

    static void
    addPlayer(std::string);

    static bool validateCreation(int x, int y, std::string basic_string);

    Player getPlayer(std::string basic_string);
};


#endif //STONEFALL_GAME_H
