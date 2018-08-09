#include <utility>

#include <utility>

#include <utility>

//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Player.h"

Player::Player(string name, string id) : name(std::move(name)), id(std::move(id)) {

}

void Player::spawnAttacker() {

}

void Player::spawnWall() {

}

void Player::spawnTurret() {

}

void Player::spawnMine() {

}

string Player::getId() {
    return id;
}

void Player::setId(string id) {
    this->id = std::move(id);
}

int Player::getResourceCount() {
    return resourceCount;
}

void Player::setResourceCount(int newCount) {
    resourceCount = newCount;
}

void Player::incrementResourceCount(int amount) {
    resourceCount += amount;
}
