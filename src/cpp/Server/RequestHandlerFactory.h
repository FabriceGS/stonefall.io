//
// Created by Mac McCann on 7/5/18.
//

#ifndef STONEFALL_REQUESTHANDLERFACTORY_H
#define STONEFALL_REQUESTHANDLERFACTORY_H

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"

using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;

class RequestHandlerFactory: public HTTPRequestHandlerFactory {
public:
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);
};


#endif //STONEFALL_REQUESTHANDLERFACTORY_H
