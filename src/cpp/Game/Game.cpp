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
#include <forward_list>

using namespace std;

// NOTE: These methods can ignore thread safety, as only the Timer thread will ever have access
// to them, and they'll all be called sequentially.
void Game::onTimer(Poco::Timer& timer) {
    updateResources();
}

weak_ptr<Player> Game::addPlayer(string name) {
    string playerId = "q";
    shared_ptr<Player> newPlayer = make_shared<Player>(std::move(name), playerId);
    // TODO: Surround critical section with thread safe mechanism as insertions (players map) invalidate iterators.
    players.insert(make_pair(playerId, newPlayer));
    return weak_ptr<Player>(newPlayer);
}

weak_ptr<Player> Game::getPlayer(string id) {
    return weak_ptr<Player>(players.at(id));
}

void Game::removePlayer(string id) {
    // TODO: See try_once flag of C++ to ensure a player is only removed once.
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


bool Game::validateCreation(int x, int y, string playerId, int creationType) {
    if (Grid::validateCoordinates(x, y)) {
        auto player = players.find(playerId);
        if (player != players.end()) {
            // if (Grid::isWithinNBlocks(3, ))
        }
        return true;
    }
    return false;
}

//public synchronized boolean validateSpawn(int x, int y) {
//  if (Grid.isWithinNBlocks(3, base.getBlock(),
//      Grid.getGridBlock(x, y).get())) {
//    return true;
//  }
//
//  for (Wall wall : walls.values()) {
//    if (Grid.isWithinNBlocks(3, wall.getBlock(),
//        Grid.getGridBlock(x, y).get())) {
//      return true;
//    }
//  }
//  for (Mine mine : mines.values()) {
//    if (Grid.isWithinNBlocks(3, mine.getBlock(),
//        Grid.getGridBlock(x, y).get())) {
//      return true;
//    }
//  }
//  for (Turret turret : turrets.values()) {
//    if (Grid.isWithinNBlocks(3, turret.getBlock(),
//        Grid.getGridBlock(x, y).get())) {
//      return true;
//    }
//  }
//
//  return false;
//}

void Game::spawnResource() {
    Poco::Random random;
    int x = random.next(Constants::BOARD_WIDTH);
    int y = random.next(Constants::BOARD_LENGTH);

    shared_ptr<Resource> resource = std::make_shared<Resource>(*(Grid::getGridBlock(x, y)->get()));
    Grid::getGridBlock(x, y)->get()->populate(resource);

    string resourceId = "/r/" + to_string(resourceIdNum);
    resources.insert(make_pair(std::move(resourceId), resource));
    resourceIdNum++;
}

void Game::spawnAttacker(string playerId, int x, int y) {
    // TODO: Surround with thread safe mechanism as insertions (attackers map) invalidate iterators.
    cout << "spawn attacker command" << endl;
}

void Game::spawnScaffold(string playerId, int x, int y, int scaffoldType) {
    if (validateCreation(x, y, playerId, scaffoldType))
}

//public synchronized void spawnScaffold(int x, int y, int scaffoldType) {
//  if (Grid.validateCoordinates(x, y)) {
//    String scaffoldId = "/f/" + scaffoldIdNum;
//    Scaffold scaffold = new Scaffold(Grid.getGridBlock(x, y).get(), this,
//        scaffoldType, scaffoldId);
//
//    if (scaffoldType == Constants.OBJECT_TYPE.MINE.ordinal()
//        && resourceCount >= multiplyByScoreLogistically(
//            Constants.MINE_COST)) {
//      resourceCount -= multiplyByScoreLogistically(Constants.MINE_COST);
//    } else if (scaffoldType == Constants.OBJECT_TYPE.TURRET.ordinal()
//        && resourceCount >= multiplyByScoreLogistically(
//            Constants.TURRET_COST)) {
//      resourceCount -= multiplyByScoreLogistically(Constants.TURRET_COST);
//    } else if (scaffoldType == Constants.OBJECT_TYPE.WALL.ordinal()
//        && resourceCount >= multiplyByScoreLogistically(
//            Constants.WALL_COST)) {
//      resourceCount -= multiplyByScoreLogistically(Constants.WALL_COST);
//    }
//
//    scaffolds.put(scaffoldId, scaffold);
//    scaffoldIdNum++;
//  }
//}

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

// Could be paralleled.
void Game::updateResources() {
    resCollectCounter++;
    std::forward_list<std::string> resourcesToDelete;

    if (resCollectCounter == Constants::RESOURCE_COLLECT_TIME) {
        for (auto &playerMapping : players) {
            playerMapping.second->incrementResourceCount(2);
            for (auto &resourceMapping : resources) {
                for (auto &mineMapping : mines) {
                    for (auto &mineSetElement : mineMapping.second) {
                        if (Grid::isWithinNBlocks(1, mineSetElement->getBlock(), resourceMapping.second->getBlock())) {
                            mineSetElement->collect(*(resourceMapping.second));
                            playerMapping.second->incrementResourceCount(2);

                            // Marking the resource as dead.
                            if (resourceMapping.second->getHealth() <= 0) {
                                Grid::getGridBlock(
                                        resourceMapping.second->getBlock().getX(),
                                        resourceMapping.second->getBlock().getY())->get()->depopulate();
                                resourcesToDelete.push_front(resourceMapping.first);
                            }
                        }
                    }
                }
            }
        }

        resCollectCounter = 0;
        // Safely deleting resources.
        for (auto &resourceId : resourcesToDelete) {
            resources.erase(resourceId);
        }
    }

    resSpawnCounter++;
    if (resSpawnCounter == Constants::RESOURCE_SPAWN_TIME) {
        if (resources.size() <= Constants::RESOURCE_MAX) {
            spawnResource();
        }
        resSpawnCounter = 0;
    }
}
