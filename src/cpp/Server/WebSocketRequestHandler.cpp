//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#include "WebSocketRequestHandler.h"
#include "PageRequestHandler.h"
#include "../Game.h"
#include "../Player.h"
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

            //get player id
            Var varPlayerId = extractedPayload->get("playerId");
//            std::string playerId = varPlayerId.convert<std::string>();

            //get the player object
//            Player player = Game::getPlayer(playerId);

            MESSAGE enumId = static_cast<MESSAGE>(id);
            switch(enumId){
                case MESSAGE::CONNECT: {
                    //get name
                    Var varName = extractedPayload->get("name");
                    std::string name = varName.convert<std::string>();
                    std::cout << "name is" + name << std::endl;

                    //add player to game if doesn't already exist
//                    if(player == NULL){
//                        player = Game::addPlayer(playerId);
//                        players.insert(playerId);
//                    }
                    break;
                }

                case MESSAGE::ATTACK:{

                    break;
                }
                case MESSAGE::CREATE:{
                    //get x and y coords of creation
                    int x = extractedPayload->get("x").convert<int>();
                    int y = extractedPayload->get("y").convert<int>();

//                    if(!Game::validateCreation(x,y,playerId)){
                        //send an error message
                        //return out of statement
//                    }

                    //get creation type enum
                    int creationType = extractedPayload->get("objectType").convert<int>();
                    OBJECT_TYPE enumMessageType = static_cast<OBJECT_TYPE>(creationType);

                    switch(enumMessageType){
                        case OBJECT_TYPE::ATTACKER:
//                            player.spawnAttacker();
                            break;
                        case OBJECT_TYPE::WALL:
//                            player.spawnWall();
                            break;
                        case OBJECT_TYPE::TURRET:
//                            player.spawnTurret();
                            break;
                        case OBJECT_TYPE::MINE:
//                            player.spawnMine();
                            break;
                        default:
                            break;
                    }
//
//                    // Communication protocol for creation types
//                    // 1: worker
//                    // 2: attacker
//                    // 3: turret
//                    // 4: wall
//                    int creationType = payload.get("objectType").getAsInt();
//                    switch (creationType) {
//                        case 1:
//                            creationType = 1;
//                            thisPlayer.spawnWorker();
//                            break;
//                        case 2:
//                            creationType = 2;
//                            thisPlayer.spawnMeleeAttacker();
//                            break;
//                        case 3:
//                            creationType = 3;
//                            thisPlayer.spawnTurret(x1, y1);
//                            break;
//                        case 4:
//                            creationType = 4;
//                            thisPlayer.spawnWall(x1, y1);
//                            break;
//                    }
                    break;
                }
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
