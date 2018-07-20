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
#include <unordered_set>


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::WebSocket;

class WebSocketRequestHandler: public HTTPRequestHandler {
    private:
        std::unordered_set<std::string> players;
        Game& game;
    public:
        void sendMessage(char buffer[], int n, int flags, WebSocket ws);
        void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override;
        explicit WebSocketRequestHandler(Game& newGame) : game(newGame) { }
};

namespace WebSockets{
    void sendMessage(char buffer[], int n, int flags, WebSocket ws);

};

enum class MESSAGE {
    CONNECT, UPDATE, ATTACK, CREATE, INITIALIZE, SELL, ERROR, GAMEOVER
};

enum class OBJECT_TYPE {
    WALL, TURRET, ATTACKER, MINE, SCAFFOLD
};

#endif //STONEFALL_WEBSOCKETS_H
