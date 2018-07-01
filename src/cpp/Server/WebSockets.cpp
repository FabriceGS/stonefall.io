//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#include "WebSockets.h"
#include "PageRequestHandler.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Format.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Array.h"
#include "Poco/Dynamic/Var.h"
#include <iostream>

using Poco::Net::ServerSocket;
using Poco::Net::WebSocket;
using Poco::Net::WebSocketException;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::JSON::Parser;
using Poco::JSON::Object;
using Poco::JSON::Array;

using Poco::Dynamic::Var;

void WebSockets::sendMessage(char buffer[], int n, int flags, WebSocket ws){
    std::cout << "sendMessage called" << std::endl;
    std::cout << buffer << std::endl;
    std::cout << n << std::endl;
    std::cout << flags << std::endl;
    //send the JSON object
    ws.sendFrame(buffer, n, flags);
}

void WebSocketRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    std::cout << "method called: handleRequest()" << std::endl;

    Application& app = Application::instance();
    try
    {
        WebSocket ws(request, response);
        app.logger().information("WebSocket connection established.");
        char buffer[1024];
        int flags;
        int n;
        do
        {
            //receive the buffer object
            n = ws.receiveFrame(buffer, sizeof(buffer), flags);

            //log the receipt
            app.logger().information(Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));

            //convert char array buffer into string
            std::string JSON(buffer);

            //parse the received JSON object
            Parser parser;
            Var result = parser.parse(JSON);
            Object::Ptr received = result.extract<Object::Ptr>();

            //get id
            Var idVar = received->get("id");;
            int id = idVar.convert<int>();

            //get the payload
            Var payload = received->get("payload");
            Object::Ptr extractedPayload = payload.extract<Object::Ptr>();

            //get name
            Var varName = extractedPayload->get("name");
            std::string name = varName.convert<std::string>();
            std::cout << name << std::endl;

            MESSAGE enumId = static_cast<MESSAGE>(id);
            switch(enumId){
                case MESSAGE::CONNECT:

//                    "{\"id\" : \"1234\", \"payload\" : {\"name\" : \"John\"}}"

//                    // update set of coordinates by parsing coordinates message
//                    String name = payload.get("name").getAsString();
//
//                    // Add the player to the game if doesn't already exist
//                    if (thisPlayer == null) {
//                        thisPlayer = new Player(name, playerId);
//                        game.addPlayer(thisPlayer);
//                    }
//
//                    // call update session and tell the backend to update everything
//                    updateSession(curId);
                    break;
                case MESSAGE::ATTACK:
                    break;
                case MESSAGE::CREATE:
                    break;
                default:
                    break;
            }


            std::cout << id << std::endl;

            //get an array
//            std::string json = "[ {\"test\" : 0}, { \"test1\" : [1, 2, 3], \"test2\" : 4 } ]";

//            Array::Ptr arr = result.extract<Array::Ptr>();
//            Object::Ptr aObject = arr->getObject(0);//
////            assert (aObject->getValue<int>("test") == 0);
//            aObject = arr->getObject(1);
//            arr = aObject->getArray("test1");
//            result = arr->get(0);
//            assert (result == 1);

            WebSockets::sendMessage(buffer, n, flags, ws);




        }
        while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
        app.logger().information("WebSocket connection closed.");
    }
    catch (WebSocketException& exc)
    {
        std::cout << "welp that happened" << std::endl;
        app.logger().log(exc);
        switch (exc.code())
        {
            case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
                response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
                // fallthrough
            case WebSocket::WS_ERR_NO_HANDSHAKE:
            case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
            case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
                response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
                response.setContentLength(0);
                response.send();
                break;
        }
    }
};


HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    std::cout << "method called: createRequestHandler(); of class: RequestHandlerFactory" << std::endl;
    Application& app = Application::instance();
    app.logger().information("Request from "
                             + request.clientAddress().toString()
                             + ": "
                             + request.getMethod()
                             + " "
                             + request.getURI()
                             + " "
                             + request.getVersion());

    for (HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
    {
        app.logger().information(it->first + ": " + it->second);
    }

    if(request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0)
        return new WebSocketRequestHandler;
    else
        return new PageRequestHandler;
};
