//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <memory>
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
    bool playerExists(string id);
    Player addPlayer(string name);
    bool validateCreation(int x, int y, string playerId, int creationType);
    Player getPlayer(string id);
    bool attackCommand(string playerId, unordered_set<string> attackerIdSet);
    bool sellCommand(string playerId, unordered_set<string> toSellIdSet);
    void spawnAttacker(string playerId, int x, int y);
    void spawnWall(string playerId, int x, int y);
    void spawnMine(string playerId, int x, int y);
    void spawnTurret(string playerId, int x, int y);
};

#endif //STONEFALL_GAME_H
