//
// Created by Mac McCann on 6/18/18.
//

#include "PageRequestHandler.h"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"

#include <fstream>
#include <iostream>

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::URI;
using namespace std;

bool PageRequestHandler::routesMatch(URI uri, string route) {
    return route.compare(uri.getPath()) == 0;
}

void PageRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
    // check for paths
    URI uri = URI(request.getURI());
    if (routesMatch(uri, "/") || routesMatch(uri, "/index") || routesMatch(uri, "/index.html")) {
        serveFile("/index.html", response);
    } else {
        // otherwise, serve statically from url
        serveFile(uri.getPath(), response);
    }
}

void PageRequestHandler::serveFile(string filename, HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    ifstream inFile;
    inFile.open(WEB_DIRECTORY_PREFIX + filename);
    if (!inFile) {
        // send a 404
        response.setStatus(HTTPServerResponse::HTTP_NOT_FOUND);
        response.setReason("Resource not found");
        ostream& ostr = response.send();
        ostr << "Resource not found\n";
    } else {
        ostream& ostr = response.send();
        fileToOStream(inFile, ostr);
    }
}

void PageRequestHandler::fileToOStream(ifstream &inFile, ostream &ostr) {
    // get size of file
    inFile.seekg (0,inFile.end);
    long size = inFile.tellg();
    inFile.seekg (0);
    // allocate memory for file content
    char* buffer = new char[size];
    // read content of inFile
    inFile.read (buffer,size);
    // write to outfile
    ostr.write (buffer,size);
    inFile.close();
}
