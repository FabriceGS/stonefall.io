#include <utility>

//
// Created by Fabrice Guyot-Sionnest on 7/2/18.
//

#include "Player.h"

Player::Player(string name, string id) : name(std::move(name)), id(std::move(id)) {
    resourceCount = 0;
    score = 0;
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
    resourceCount.store(newCount);
}

void Player::incrementResourceCount(int amount) {
    resourceCount.store(resourceCount + amount);
}

void Player::decrementResourceCount(int amount) {
    resourceCount.store(resourceCount - amount);
}

int Player::getScore() {
    return score;
}
