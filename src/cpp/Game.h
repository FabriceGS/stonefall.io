//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include "Player.h"
#include "unordered_set"


class Game {

public:
    static bool
    playerExists(std::string);

    static Player *
    addPlayer(std::string);

    static bool validateCreation(int x, int y, std::string basic_string);

    Player * getPlayer(std::string basic_string);

    bool attackCommand(Player *player, std::unordered_set<std::string> attackerIdSet);
};


#endif //STONEFALL_GAME_H
