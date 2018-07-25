//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <Structure/Resource.h>
#include "Player.h"
#include "unordered_set"
#include "unordered_map"

class Game {
    private:
        std::unordered_map<std::string, Player> players;
        std::unordered_map<std::string, Resource> resources;
        int resourceIdNum;
        int resSpawnCounter;
        int resCollectCounter;

    public:
        static bool playerExists(std::string);

        Player addPlayer();

        static bool validateCreation(int x, int y, std::string basic_string);

        Player getPlayer(std::string id);

        bool attackCommand(Player& player, std::unordered_set<std::string> attackerIdSet);
};


#endif //STONEFALL_GAME_H
