//
// Created by Mac McCann on 6/18/18.
//

#include "Server/PageRequestHandler.h"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/URI.h"

#include <fstream>
#include <iostream>

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTMLForm;
using Poco::URI;
using namespace std;

bool PageRequestHandler::routesMatch(URI uri, string route) {
    return route.compare(uri.getPath()) == 0;
}

void PageRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
    // check for paths
    URI uri = URI(request.getURI());
    if ((routesMatch(uri, "/") || routesMatch(uri, "/index") || routesMatch(uri, "/index.html"))
        && request.getMethod().compare("GET") == 0) {
        serveFile("/index.html", response);
    } else if ((routesMatch(uri, "/") || routesMatch(uri, "/index") || routesMatch(uri, "/index.html"))
        && request.getMethod().compare("POST") == 0) {
        // handle the initial POST request
        // get the name from the form
        HTMLForm form(request, request.stream());
        string name = form["name"];
        ostream& ostr = response.send();
        ostr << "Your name was " << name << endl;
    } else {
        // otherwise, serve statically from url
        serveFile(uri.getPath(), response);
    }
}

void PageRequestHandler::serveFile(string filename, HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    if (filename.find("css", 0) != string::npos) {
        response.setContentType("text/css");
    } else if (filename.find("js", 0) != string::npos) {
        response.setContentType("application/javascript");
    } else {
        response.setContentType("text/html");
    }
    ifstream inFile;
    inFile.open(WEB_DIRECTORY_PREFIX + filename);
    if (!inFile) {
        // send a 404
        response.setStatus(HTTPServerResponse::HTTP_NOT_FOUND);
        response.setReason("Resource not found");
        ostream& ostr = response.send();
        ostr << "<b>404 Error:</b> Resource not found\n";
    } else {
        ostream& ostr = response.send();
        fileToOStream(inFile, ostr);
    }
}

void PageRequestHandler::fileToOStream(ifstream &inFile, ostream &ostr) {
    // get size of file
    inFile.seekg(0,inFile.end);
    long size = inFile.tellg();
    inFile.seekg(0);
    // allocate memory for file content
    auto * buffer = new char[size];
    // read content of inFile
    inFile.read(buffer, size);
    // write to outfile
    ostr.write(buffer, size);
    inFile.close();
    delete[] buffer;
}