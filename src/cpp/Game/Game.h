//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#ifndef STONEFALL_GAME_H
#define STONEFALL_GAME_H

#include <iostream>
#include <memory>
#include <forward_list>
#include <shared_mutex>
#include <unordered_set>
#include <unordered_map>

#include <Structure/Mine.h>
#include <Structure/Turret.h>
#include <Structure/Wall.h>
#include <Structure/Scaffold.h>
#include <Structure/Base.h>
#include <Structure/Resource.h>
#include <Game/Player.h>
#include <Game/GameState.h>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Runnable.h"
#include "Poco/Timer.h"
#include "Poco/Random.h"

using Poco::Net::HTTPRequestHandler;

using namespace std;

class Game {
    private:
        // NOTE: I'm just going to build these maps with mutexes for now, but there are some
        // pretty cool & tested concurrent map libraries out there that we can import in later.
        unordered_map<string, shared_ptr<Player>> players;

        unordered_map<string, shared_ptr<Resource>> resources;
        unordered_map<string, shared_ptr<Base>> bases;

        std::shared_mutex minesMutex;
        unordered_map<string, unordered_map<string, shared_ptr<Mine>>> mines;

        std::shared_mutex turretsMutex;
        unordered_map<string, unordered_map<string, shared_ptr<Turret>>> turrets;

        std::shared_mutex wallsMutex;
        unordered_map<string, unordered_map<string, shared_ptr<Wall>>> walls;

        std::shared_mutex scaffoldsMutex;
        unordered_map<string, unordered_map<string, shared_ptr<Scaffold>>> scaffolds;

        int resourceIdNum{};
        int resSpawnCounter{};
        int resCollectCounter{};
        atomic_int scaffoldIdNum{};
        atomic_int structureIdNum{};

        HTTPRequestHandler *webSocketRequestHandler{};
        void spawnResource();
        void updateResources();
        void updateBases();
        void updateScaffolds();
        void upgradeScaffolds(string playerId, std::forward_list<string> scaffoldsToUpgrade);

    public:
        Game();
        void onTimer(Poco::Timer& timer);
        void setSocketHandler(HTTPRequestHandler *newWebSocketRequestHandler);
        weak_ptr<Player> addPlayer(string name);
        weak_ptr<Player> getPlayer(string playerId);
        void removePlayer(string playerId);
        bool playerExists(string playerId);
        bool validateCreation(string playerId, int x, int y);
        bool attackCommand(string playerId, unordered_set<string> attackerIdSet);
        bool sellCommand(string playerId, unordered_set<string> toSellIdSet);
        void spawnAttacker(string playerId, int x, int y);
        void spawnScaffold(string playerId, int x, int y, int structureType);
        void spawnWall(string playerId, int x, int y);
        void spawnMine(string playerId, int x, int y);
        void spawnTurret(string playerId, int x, int y);
};

#endif //STONEFALL_GAME_H
