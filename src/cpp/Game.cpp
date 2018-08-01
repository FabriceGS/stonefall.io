//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game.h"
#include "Player.h"
#include <iostream>
#include "unordered_set"

using namespace std;

Player Game::getPlayer(string id) {
    return players.at(id);
}

bool Game::attackCommand(string playerId, unordered_set<string> attackerIdSet) {
    cout << "attack command" << endl;
    for(auto f : attackerIdSet) {
        cout << f << endl;
    }
    return false;
}

bool Game::sellCommand(string playerId, unordered_set<string> toSellIdSet) {
    cout << "sell command" << endl;
    for (auto id : toSellIdSet) {
        cout << id << endl;
    }
    return false;
}

bool Game::playerExists(string playerId) {
    return players.find(playerId) != players.end();
}

Player Game::addPlayer(string name) {
    // TODO: generate a random id for the player here
    cout<< "add player command" << endl;
    return Player();
}

bool Game::validateCreation(int x, int y, string basic_string, int creationType) {
    cout<< "validate creation command" << endl;
    return false;
}

void Game::spawnAttacker(string playerId, int x, int y) {
    cout << "spawn attacker command" << endl;
}

void Game::spawnWall(string playerId, int x, int y) {
    cout << "spawn command" << endl;
}

void Game::spawnMine(string playerId, int x, int y) {
    cout << "spawn command" << endl;
}

void Game::spawnTurret(string playerId, int x, int y) {
    cout << "spawn command" << endl;
}
