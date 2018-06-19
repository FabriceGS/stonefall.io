//
// Created by Mac McCann on 6/18/18.
//

#ifndef STONEFALL_PAGEREQUESTHANDLER_H
#define STONEFALL_PAGEREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;


class PageRequestHandler: public HTTPRequestHandler
    /// Return a HTML document with some JavaScript creating
    /// a WebSocket connection.
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


#endif //STONEFALL_PAGEREQUESTHANDLER_H
