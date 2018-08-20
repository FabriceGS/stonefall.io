//
// Created by Mac McCann on 8/7/18.
//

#ifndef STONEFALL_GAMEMANAGER_H
#define STONEFALL_GAMEMANAGER_H

#include <Game/Game.h>
#include "Server/WebSocketRequestHandler.h"

class GameManager {
private:
    std::shared_ptr<Game> game;
public:
    GameManager() { game = std::make_shared<Game>(); }
    HTTPRequestHandler *createWebSocketRequestHandler();
};

#endif //STONEFALL_GAMEMANAGER_H
