//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game/Game.h"
#include <Map/Grid.h>
#include "Config/Utility.h"

using namespace std;

Game::Game() {
    // Set players map to size MAX_PLAYERS to prevent rehashing. We'll have to manage not allowing more than
    // MAX_PLAYERS in a game.
    players.reserve(Constants::MAX_PLAYERS);
    bases.reserve(Constants::MAX_PLAYERS);
}

// NOTE: These methods can ignore thread safety, as only the Timer thread will ever have access
// to them, and they'll all be called sequentially.
void Game::onTimer(Poco::Timer& timer) {
    updateResources();
}

void Game::addSocketHandler(HTTPRequestHandler *newWebSocketRequestHandler)  {
    webSocketRequestHandler = newWebSocketRequestHandler;
}

shared_ptr<Player> Game::addPlayer(string name) {
    // Adding the player.
    // TODO: Randomly generate playerId.
    string playerId = Crypto::id();
    shared_ptr<Player> newPlayer = make_shared<Player>(std::move(name), playerId);
    players.insert(make_pair(playerId, newPlayer));

    // Adding their base.
    Poco::Random random;
    int x = random.next(Constants::BOARD_WIDTH);
    int y = random.next(Constants::BOARD_LENGTH);

    while (!Grid::validateCoordinates(x, y)) {
        x = random.next(Constants::BOARD_WIDTH);
        y = random.next(Constants::BOARD_LENGTH);
    }

    shared_ptr<Base> newBase = make_shared<Base>(*(Grid::getGridBlock(x, y)->get()));
    bases.insert(make_pair(playerId, newBase));
    return newPlayer;
}

shared_ptr<Player> Game::getPlayer(string playerId) {
    return players.at(playerId);
}

void Game::removePlayer(string playerId) {
    players.erase(playerId);
    bases.erase(playerId);
    mines.erase(playerId);
    turrets.erase(playerId);
    walls.erase(playerId);
    scaffolds.erase(playerId);
    // attackers.erase(playerId);
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


bool Game::validateCreation(string playerId, int x, int y, int spawnType) {
    // TODO: validate that the player has enough resources for the spawn type
    if (Grid::validateCoordinates(x, y)) {
        auto prospectBlock = *(Grid::getGridBlock(x, y)->get());
         if (Grid::isWithinNBlocks(3, bases[playerId]->getBlock(), prospectBlock)) {
             return true;
         }

         for (const auto &wallMapping : walls[playerId]) {
             if (Grid::isWithinNBlocks(3, wallMapping.second->getBlock(), prospectBlock)) {
                 return true;
             }
         }

         for (const auto &mineMapping : mines[playerId]) {
             if (Grid::isWithinNBlocks(3, mineMapping.second->getBlock(), prospectBlock)) {
                 return true;
             }
         }

         for (const auto &turretMapping : turrets[playerId]) {
             if (Grid::isWithinNBlocks(3, turretMapping.second->getBlock(), prospectBlock)) {
                 return true;
             }
         }
    }
    return false;
}

void Game::spawnResource() {
    Poco::Random random;
    int x = random.next(Constants::BOARD_WIDTH);
    int y = random.next(Constants::BOARD_LENGTH);

    while (!Grid::validateCoordinates(x, y)) {
        x = random.next(Constants::BOARD_WIDTH);
        y = random.next(Constants::BOARD_LENGTH);
    }

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
    auto const &playerMapping = players.find(playerId);
    if (playerMapping != players.end()) {
        int adjustedCost;

        switch (scaffoldType) {
            case STRUCTURE_TYPE::MINE: {
                adjustedCost = util::multiplyByScoreLogistically(Constants::MINE_COST, playerMapping->second->getScore());
                break;
            }

            case STRUCTURE_TYPE::TURRET: {
                adjustedCost = util::multiplyByScoreLogistically(Constants::TURRET_COST, playerMapping->second->getScore());
                break;
            }

            case STRUCTURE_TYPE::WALL: {
                adjustedCost = util::multiplyByScoreLogistically(Constants::WALL_COST, playerMapping->second->getScore());
                break;
            }
            default:
                return;
        }

        if (playerMapping->second->getResourceCount() >= adjustedCost) {
            if (validateCreation(playerId, x, y, scaffoldType)) {
                playerMapping->second->decrementResourceCount(adjustedCost);
                // Critical Section for incrementing scaffoldIdNum and storing the scaffold.
                // NOTE: Any lag with scaffold spawning will come from here.
                {
                    std::unique_lock<std::shared_timed_mutex> writeLock(scaffoldsMutex);
                    string scaffoldId = "/f/" + to_string(scaffoldIdNum);
                    scaffoldIdNum++;

                    shared_ptr<Scaffold> scaffold =
                            std::make_shared<Scaffold>(*(Grid::getGridBlock(x, y)->get()),
                                                       scaffoldType, scaffoldId);

                    Grid::getGridBlock(x, y)->get()->populate(scaffold);

                    const auto &playerScaffolds = scaffolds.find(playerId);
                    if (playerScaffolds != scaffolds.end()) {
                        playerScaffolds->second.insert(std::make_pair(scaffoldId, scaffold));
                    }
                    writeLock.unlock();
                }
            }
        }
    }
}

void Game::spawnWall(string playerId, int x, int y) {
    if (Grid::validateCoordinates(x, y)) {
        shared_ptr<Wall> wall = make_shared<Wall>(*(Grid::getGridBlock(x, y)->get()));

        {
            std::unique_lock<std::shared_timed_mutex> writeLock(wallsMutex);
            string wallId = "/s/" + to_string(structureIdNum);
            structureIdNum++;

            const auto &playerWalls = walls.find(playerId);
            if (playerWalls != walls.end()) {
                playerWalls->second.insert(std::make_pair(wallId, wall));
            }
            writeLock.unlock();
        }

        // TODO: Adjust score info..
    }
}

void Game::spawnMine(string playerId, int x, int y) {
    if (Grid::validateCoordinates(x, y)) {
        shared_ptr<Mine> mine = make_shared<Mine>(*(Grid::getGridBlock(x, y)->get()));

        {
            std::unique_lock<std::shared_timed_mutex> writeLock(minesMutex);
            string mineId = "/s/" + to_string(structureIdNum);
            structureIdNum++;

            const auto &playerMines = mines.find(playerId);
            if (playerMines != mines.end()) {
                playerMines->second.insert(std::make_pair(mineId, mine));
            }
            writeLock.unlock();
        }

        // TODO: Adjust score info..
    }
}

void Game::spawnTurret(string playerId, int x, int y) {
    if (Grid::validateCoordinates(x, y)) {
        shared_ptr<Turret> turret = make_shared<Turret>(*(Grid::getGridBlock(x, y)->get()));

        {
            std::unique_lock<std::shared_timed_mutex> writeLock(turretsMutex);
            string turretId = "/s/" + to_string(structureIdNum);
            structureIdNum++;

            const auto &playerTurrets = turrets.find(playerId);
            if (playerTurrets != turrets.end()) {
                playerTurrets->second.insert(std::make_pair(turretId, turret));
            }
            writeLock.unlock();
        }

        // TODO: Adjust score info..
    }
}

// No need for thread safety as only one thread will execute this code.
void Game::updateResources() {
    resCollectCounter++;
    std::forward_list<std::string> resourcesToDelete;

    if (resCollectCounter == Constants::RESOURCE_COLLECT_TIME) {
        for (auto &playerMapping : players) {
            playerMapping.second->incrementResourceCount(2);
            for (auto &resourceMapping : resources) {
                std::shared_lock<std::shared_timed_mutex> mineReadLock(minesMutex);
                for (auto &mineMapping : mines) {
                    for (auto &playerMineMapping : mineMapping.second) {
                        if (Grid::isWithinNBlocks(1, playerMineMapping.second->getBlock(), resourceMapping.second->getBlock())) {
                            playerMineMapping.second->collect(*(resourceMapping.second));
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
                mineReadLock.unlock();
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

void Game::updateBases() {
    for (auto &baseMapping : bases) {
        if (baseMapping.second->isDead()) {
            // TODO: Call equivalent of Websockets.gameover(baseMapping.first);
            removePlayer(baseMapping.first);
        }
    }
}

void Game::updateScaffolds() {
    for (auto &playerScaffolds : scaffolds) {
        std::forward_list<string> scaffoldsToUpgrade;

        for (auto &scaffoldMapping : playerScaffolds.second) {
            scaffoldMapping.second->update();
            if (scaffoldMapping.second->readyToUpgrade()) {
                scaffoldsToUpgrade.push_front(scaffoldMapping.first);
            }
        }

        if (!scaffoldsToUpgrade.empty()) {
            upgradeScaffolds(playerScaffolds.first, scaffoldsToUpgrade);
        }
    }
}

// NOTE: Any lag with scaffold upgrading will come from here.
void Game::upgradeScaffolds(string playerId, std::forward_list<string> scaffoldsToUpgrade) {
    for (auto &scaffoldId : scaffoldsToUpgrade) {
        auto playerScaffolds = scaffolds.find(playerId);
        if (playerScaffolds != scaffolds.end()) {
            // Creating the new structure.
            const auto &scaffoldRef = playerScaffolds->second[scaffoldId];
            int structureType = scaffoldRef->getType();
            int x = scaffoldRef->getBlock().getX();
            int y = scaffoldRef->getBlock().getY();

            // Removing old scaffold.
            std::unique_lock<std::shared_timed_mutex> readLock(scaffoldsMutex);
            playerScaffolds->second.erase(scaffoldId);
            readLock.unlock();

            // Spawning new structure.
            if (structureType == STRUCTURE_TYPE::MINE) {
                spawnMine(playerId, x, y);
            } else if (structureType == STRUCTURE_TYPE::TURRET) {
                spawnTurret(playerId, x, y);
            } else if (structureType == STRUCTURE_TYPE::WALL) {
                spawnWall(playerId, x, y);
            }
        }
    }
}

