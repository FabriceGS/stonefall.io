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

    Player addPlayer();

    static bool validateCreation(int x, int y, std::string basic_string);

    Player getPlayer(std::string id);

    bool attackCommand(shared_ptr<Player> player, std::unordered_set<std::string> attackerIdSet);
};


#endif //STONEFALL_GAME_H
