//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#ifndef STONEFALL_WEBSOCKETS_H
#define STONEFALL_WEBSOCKETS_H

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/WebSocket.h"
#include "../Game/Game.h"
#include "Game/GameState.h"
#include "unordered_map"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::WebSocket;

using namespace std;

class Game;

class WebSocketRequestHandler: public HTTPRequestHandler {
private:
    unordered_map<string, shared_ptr<WebSocket>> sessions;
    shared_ptr<Game> game;
public:
    WebSocketRequestHandler() {}
    WebSocketRequestHandler(shared_ptr<Game> newGame) {
        game = newGame;
        game->setSocketHandler(this);
    }
    void sendMessage(char const * msg, int n, int flags, WebSocket ws);
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
    void sendUpdates(const GameState& gameState);
    void updateSession(string playerId, const char* jsonState);
    unordered_set<string> players;
};

namespace WebSockets {
    void sendMessage(char buffer[], int n, int flags, WebSocket ws);
};

enum class MESSAGE {
    INITIALIZE, UPDATE, ATTACK, SPAWN, SELL, ERROR, GAMEOVER, TEST
};

enum class OBJECT_TYPE {
    WALL, TURRET, ATTACKER, MINE, SCAFFOLD
};

#endif //STONEFALL_WEBSOCKETS_H
