//
// Created by Mac McCann on 8/7/18.
//

#include "GameManager.h"

HTTPRequestHandler *GameManager::createWebSocketRequestHandler() {
    HTTPRequestHandler *newRequestHandler = new WebSocketRequestHandler(game);
    return newRequestHandler;
}
