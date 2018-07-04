//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Game.h"
#include "Player.h"
#include <iostream>

Player * Game::getPlayer(std::string basic_string){
    Player * newPlayer = new Player();
    return newPlayer;
}

bool Game::playerExists(std::string basic_string) {
    return false;
}

Player * Game::addPlayer(std::string basic_string) {
    Player * newPlayer = new Player();
    return newPlayer;
}

bool Game::validateCreation(int x, int y, std::string basic_string) {
    return false;
}
