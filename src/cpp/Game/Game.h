//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <memory>
#include <Structure/Mine.h>
#include <Structure/Turret.h>
#include <Structure/Wall.h>
#include <Structure/Scaffold.h>
#include <Structure/Base.h>
#include "unordered_set"
#include "unordered_map"
#include "Player.h"
#include "Game/GameState.h"
#include "Structure/Resource.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Runnable.h"
#include "Poco/Timer.h"
#include "Poco/Random.h"

using Poco::Net::HTTPRequestHandler;

using namespace std;

class Game {
    private:
    // TODO: May change structure maps to pointers..
        unordered_map<string, shared_ptr<Player>> players;
        unordered_map<string, shared_ptr<Resource>> resources;
        unordered_map<string, shared_ptr<Base>> bases;
        unordered_map<string, unordered_map<string, shared_ptr<Mine>>> mines;
        unordered_map<string, unordered_map<string, shared_ptr<Turret>>> turrets;
        unordered_map<string, unordered_map<string, shared_ptr<Wall>>> walls;
        unordered_map<string, unordered_map<string, shared_ptr<Scaffold>>> scaffolds;
        // attackers

        int resourceIdNum{};
        int resSpawnCounter{};
        int resCollectCounter{};
        atomic_int scaffoldIdNum{};
        HTTPRequestHandler *webSocketRequestHandler{};
        void updateResources();
        void spawnResource();

    public:
        Game() = default;
        void onTimer(Poco::Timer& timer);
        weak_ptr<Player> addPlayer(string name);
        weak_ptr<Player> getPlayer(string id);
        void removePlayer(string id);
        bool playerExists(string id);
        bool validateCreation(string playerId, int x, int y);
        bool attackCommand(string playerId, unordered_set<string> attackerIdSet);
        bool sellCommand(string playerId, unordered_set<string> toSellIdSet);
        void spawnAttacker(string playerId, int x, int y);
        void spawnScaffold(string playerId, int x, int y, int structureType);
        void spawnWall(string playerId, int x, int y);
        void spawnMine(string playerId, int x, int y);
        void spawnTurret(string playerId, int x, int y);
        void setSocketHandler(HTTPRequestHandler *newWebSocketRequestHandler) {
            webSocketRequestHandler = newWebSocketRequestHandler;
        }
        int multiplyByScoreLogistically(int cost, int score);
};

#endif //STONEFALL_GAME_H
