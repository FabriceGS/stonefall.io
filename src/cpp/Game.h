//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <memory>
#include "Player.h"
#include "unordered_set"


class Game {

public:
    static bool
    playerExists(std::string);

    Player addPlayer();

    static bool validateCreation(int x, int y, std::string basic_string, int creationType);

    Player getPlayer(std::string id);

    bool attackCommand(shared_ptr<Player> player, std::unordered_set<std::string> attackerIdSet);

    bool sellCommand(shared_ptr<Player> player, std::unordered_set<std::string> toSellIdSet);
};


#endif //STONEFALL_GAME_H
