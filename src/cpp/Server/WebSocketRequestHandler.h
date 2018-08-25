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
    // this is a weak pointer to avoid the cyclic reference
    // http://www.acodersjourney.com/2016/05/top-10-dumb-mistakes-avoid-c-11-smart-pointers/
    weak_ptr<Game> game;
public:
    WebSocketRequestHandler() = default;
    explicit WebSocketRequestHandler(const shared_ptr<Game>& newGame) {
        game = newGame;
    }
    void sendMessage(char const * msg, int n, int flags, WebSocket ws);
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
    void sendUpdate(const GameState& gameState);
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
