//
// Created by Mac McCann on 6/18/18.
//

#ifndef STONEFALL_PAGEREQUESTHANDLER_H
#define STONEFALL_PAGEREQUESTHANDLER_H

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::URI;
using namespace std;

class PageRequestHandler: public HTTPRequestHandler
    /// Return a HTML document with some JavaScript creating
    /// a WebSocket connection.
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
private:
    const string WEB_DIRECTORY_PREFIX = "src/web";
    bool routesMatch(URI uri, string route);
    void serveFile(string filename, HTTPServerResponse &response);
    void fileToOStream(string filename, ostream &ostr);
};


#endif //STONEFALL_PAGEREQUESTHANDLER_H
