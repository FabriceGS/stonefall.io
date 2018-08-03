//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <memory>
#include "unordered_set"
#include "unordered_map"
#include "Player.h"
#include "Game/GameState.h"
#include "Structure/Resource.h"
#include "Poco/Net/HTTPRequestHandler.h"

using Poco::Net::HTTPRequestHandler;

using namespace std;

class Game {
private:
    unordered_map<string, Player> players;
    unordered_map<string, Resource> resources;
    GameState gameState;
    int resourceIdNum;
    int resSpawnCounter;
    int resCollectCounter;
    HTTPRequestHandler *webSocketRequestHandler;
public:
    Game() = default;
    Player addPlayer(string name);
    bool playerExists(string id);
    Player getPlayer(string id);
    bool validateCreation(int x, int y, string playerId, int creationType);
    bool attackCommand(string playerId, unordered_set<string> attackerIdSet);
    bool sellCommand(string playerId, unordered_set<string> toSellIdSet);
    void spawnAttacker(string playerId, int x, int y);
    void spawnWall(string playerId, int x, int y);
    void spawnMine(string playerId, int x, int y);
    void spawnTurret(string playerId, int x, int y);
    void setSocketHandler(HTTPRequestHandler *newWebSocketRequestHandler) {
        webSocketRequestHandler = newWebSocketRequestHandler;
    }
};

#endif //STONEFALL_GAME_H
