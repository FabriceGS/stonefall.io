//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game.h"
#include "Player.h"
#include <iostream>
#include "unordered_set"

Player * Game::getPlayer(std::string basic_string){
    Player * newPlayer = new Player();
    return newPlayer;
}

bool Game::attackCommand(Player *player, std::unordered_set<std::string> attackerIdSet) {
    std::cout << "attack command" << std::endl;
    for(auto f : attackerIdSet) {
        std::cout << f << std::endl;
    }
    return false;
}

bool Game::playerExists(std::string basic_string) {
    std::cout<< "player exists command" << std::endl;
    return false;
}

Player * Game::addPlayer(std::string basic_string) {
    std::cout<< "add player command" << std::endl;
    std::cout<< basic_string << std::endl;
    Player * newPlayer = new Player();
    return newPlayer;
}

bool Game::validateCreation(int x, int y, std::string basic_string) {
    std::cout<< "validate creation command" << std::endl;
    return false;
}
