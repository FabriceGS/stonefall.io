//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#ifndef STONEFALL_WEBSOCKETS_H
#define STONEFALL_WEBSOCKETS_H

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPRequestHandlerFactory;


class RequestHandlerFactory: public HTTPRequestHandlerFactory {
    public:
        HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);

};

class WebSocketRequestHandler: public HTTPRequestHandler {
    public:
        void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


#endif //STONEFALL_WEBSOCKETS_H
