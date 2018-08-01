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
#include "Game.h"
#include "GameState.h"
#include "unordered_map"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::WebSocket;

class WebSocketRequestHandler: public HTTPRequestHandler {
    private:
        std::unordered_map<std::string, shared_ptr<WebSocket>> sessions;
        std::shared_ptr<Game> game;
    public:
        void sendMessage(char const * msg, int n, int flags, WebSocket ws);
        void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
        void sendUpdates(const GameState& gameState);
        void updateSession(std::string playerId, const char* jsonState);
        WebSocketRequestHandler(std::shared_ptr<Game> newGame) : game(newGame) {}
        std::unordered_set<std::string> players;
};

namespace WebSockets{
    void sendMessage(char buffer[], int n, int flags, WebSocket ws);

};

enum class MESSAGE {
    INITIALIZE, UPDATE, ATTACK, SPAWN, SELL, ERROR, GAMEOVER, TEST
};

enum class OBJECT_TYPE {
    WALL, TURRET, ATTACKER, MINE, SCAFFOLD
};

#endif //STONEFALL_WEBSOCKETS_H
