//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game.h"
#include "Player.h"
#include <iostream>
#include "unordered_set"

using namespace std;

Player Game::getPlayer(string id){
    Player newPlayer = Player();
    return newPlayer;
}

bool Game::attackCommand(shared_ptr<Player> player, unordered_set<string> attackerIdSet) {
    cout << "attack command" << endl;
    for(auto f : attackerIdSet) {
        cout << f << endl;
    }
    return false;
}

bool Game::sellCommand(shared_ptr<Player> player, unordered_set<string> toSellIdSet) {
    cout << "sell command" << endl;
    for (auto id : toSellIdSet) {
        cout << id << endl;
    }
    return false;
}

bool Game::playerExists(string basic_string) {
    cout<< "player exists command" << endl;
    return false;
}

Player Game::addPlayer() {
    // TODO: generate a random id for the player here
    cout<< "add player command" << endl;
    return Player();
}

bool Game::validateCreation(int x, int y, string basic_string, int creationType) {
    cout<< "validate creation command" << endl;
    return false;
}
