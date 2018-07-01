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


using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::WebSocket;




class RequestHandlerFactory: public HTTPRequestHandlerFactory {
    public:
        HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);

};

class WebSocketRequestHandler: public HTTPRequestHandler {
    public:
        void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};

namespace WebSockets{
    void sendMessage(char buffer[], int n, int flags, WebSocket ws);

};

enum class MESSAGE {
    CONNECT, UPDATE, ATTACK, CREATE, INITIALIZE, SELL, ERROR, GAMEOVER
};

#endif //STONEFALL_WEBSOCKETS_H
