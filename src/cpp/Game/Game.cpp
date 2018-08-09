#include <utility>

//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game/Game.h"
#include "Player.h"
#include <iostream>
#include <Map/Grid.h>
#include "unordered_set"
#include "Game.h"
#include "Config/ReleaseConstants.h"

using namespace std;

void Game::onTimer(Poco::Timer& timer) {
    updateResources();
}

weak_ptr<Player> Game::addPlayer(string name) {
    // TODO: generate a random id for the player here
    string playerId = "q";
    shared_ptr<Player> newPlayer = make_shared<Player>(std::move(name), playerId);
    // TODO: Surround critical section with thread safe mechanism as insertions (players map) invalidate iterators.
    players.insert(make_pair(playerId, newPlayer));
    return weak_ptr<Player>(newPlayer);
}

weak_ptr<Player> Game::getPlayer(string id) {
    return weak_ptr<Player>(players.at(id));
}

bool Game::playerExists(string playerId) {
    return players.find(playerId) != players.end();
}

bool Game::attackCommand(string playerId, unordered_set<string> attackerIdSet) {
    cout << "attack command" << endl;
    for(auto f : attackerIdSet) {
        cout << f << endl;
    }
    return false;
}

bool Game::sellCommand(string playerId, unordered_set<string> toSellIdSet) {
    // TODO: Surround section with thread safe mechanism as deletions (resources map) invalidate iterators.
    cout << "sell command" << endl;
    for (auto id : toSellIdSet) {
        cout << id << endl;
    }
    return false;
}


bool Game::validateCreation(int x, int y, string basic_string, int creationType) {
    cout<< "validate creation command" << endl;
    return false;
}

void Game::spawnAttacker(string playerId, int x, int y) {
    // TODO: Surround with thread safe mechanism as insertions (attackers map) invalidate iterators.
    cout << "spawn attacker command" << endl;
}

void Game::spawnWall(string playerId, int x, int y) {
    // TODO: Surround with thread safe mechanism as insertions (walls map) invalidate iterators.
    cout << "spawn command" << endl;
}

void Game::spawnMine(string playerId, int x, int y) {
    // TODO: Surround with thread safe mechanism as insertions (mines map) invalidate iterators.
    cout << "spawn command" << endl;
}

void Game::spawnTurret(string playerId, int x, int y) {
    // TODO: Surround with thread safe mechanism as insertions (turrets map) invalidate iterators.
    cout << "spawn command" << endl;
}

void Game::updateResources() {
    // TODO: Surround with thread safe mechanism as deletions (resources map) invalidate iterators.
    resCollectCounter++;

    if (resCollectCounter == RESOURCE_COLLECT_FREQ) {
        for (auto &playerMapping : players) {
            playerMapping.second->incrementResourceCount(2);
            for (auto &resourceMapping : resources) {
                for (auto &mineMapping : mines) {
                    if (Grid::isWithinNBlocks(1, mineMapping.second.getBlock(), resourceMapping.second.getBlock())) {
                        playerMapping.second->incrementResourceCount(2);
                    }
                }
            }
        }
    }
}
