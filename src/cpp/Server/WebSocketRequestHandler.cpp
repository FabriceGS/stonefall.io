//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#include "WebSocketRequestHandler.h"
#include "PageRequestHandler.h"
#include "Game.h"
#include "GameState.h"
#include "Player.h"
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
#include "Poco/HashMap.h"
#include <iostream>
#include <memory>

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
using Poco::HashMap;
using namespace std;

void WebSocketRequestHandler::sendMessage(char const *msg, int n, int flags, WebSocket ws){
    cout << "sendMessage called " << endl;
    cout << msg << endl;
    cout << n << endl;
    cout << flags << endl;
    //send the JSON object
    ws.sendFrame(msg, n, flags);
}

// a method to be called by the game, once the user command queue for a given tick
// has been emptied (i.e. each task has been completed). Thus, a complete gameState
// is ready to be passed to the players and displayed for each user.
// gameState is a gamestate for which one command queue has been completed.
void WebSocketRequestHandler::sendUpdates(GameState& gameState){
    //TODO process the entire gamestate into a JSON object here
    const char * jsonState = "you've been updated by a smooth criminal";

    // then interpret the game state for each player and update 'em
    for (auto& session: sessions) {
        updateSession(session.first, jsonState);
    }
}

// a method to update a given player's session, given a gameState (represented by a JSON obj) and player id
void WebSocketRequestHandler::updateSession(std::string playerId, const char* jsonState){

    //get session
    WebSocket session = sessions.at(playerId);
    int flags;
    int n;

    //send the buffer
    sendMessage(jsonState, n, flags, session);
}

void WebSocketRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    try {
        //TODO this websocket is created and then tossed out right away, seems like it would cause many problems but I can't think of a workaround rn
        WebSocket ws(request, response);
        char* buffer;
        int flags;
        int n;

        do {
            // receive the buffer object
            n = ws.receiveFrame(buffer, sizeof(buffer), flags);

            // convert char array buffer into string
            string JSON(buffer);

            // parse the received JSON object
            Parser parser;
            Var result = parser.parse(JSON);
            Object::Ptr received = result.extract<Object::Ptr>();

            // get type
            Var typeVar = received->get("type");;
            int type = typeVar.convert<int>();
            MESSAGE typeEnum = static_cast<MESSAGE>(type);

            //get the payload
            Var payload = received->get("payload");
            Object::Ptr extractedPayload = payload.extract<Object::Ptr>();

            //get the playerId
            Var idVar = extractedPayload->get("id");
            string playerId = idVar.convert<string>();

            //get player
            shared_ptr<Player> player = std::make_unique<Player>(game.getPlayer(playerId));

            switch(typeEnum){
                case MESSAGE::INITIALIZE: {
                    // get name
                    Var nameVar = extractedPayload->get("name");
                    string name = nameVar.convert<string>();

                    // add player to game if doesn't already exist (it shouldn't)
                    if(player == NULL){
                        player = std::make_unique<Player>(game.addPlayer());
                        sessions.insert(std::make_pair(player->getId(), ws));
                    } else {
                        std::cout << "this case shouldn't have occurred" << std::endl;
                    }

                    break;
                }

                case MESSAGE::ATTACK: {

                    // communicate attacking instructions to game

                    // get coordinates of objective
                    int x = extractedPayload->get("x").convert<int>();
                    int y = extractedPayload->get("y").convert<int>();

                    // set of attacker ids
                    Object::Ptr attackerIds = extractedPayload->getObject("attackers");

                    // iterate over and add to hashset
                    unordered_set<string> attackerIdSet;
                    Object::Iterator iter;
                    for(iter = attackerIds->begin(); iter != attackerIds->end(); iter++) {
                        attackerIdSet.insert(iter->first);
                    }

                    //send the attacker ids to the game
                    game.attackCommand(std::move(player), attackerIdSet);

                    break;
                }

                case MESSAGE::CREATE: {

                    // get x and y coords of creation
                    int x = extractedPayload->get("x").convert<int>();
                    int y = extractedPayload->get("y").convert<int>();

                    if (!game.validateCreation(x, y, playerId)) {
//                        TODO send an error message
//                        return out of statement
                    }

                    //get creation type enum
                    int creationType = extractedPayload->get("objectType").convert<int>();
                    OBJECT_TYPE creationTypeEnum = static_cast<OBJECT_TYPE>(creationType);

                    switch(creationTypeEnum){
                        case OBJECT_TYPE::ATTACKER:
                            player->spawnAttacker();
                            break;
                        case OBJECT_TYPE::WALL:
                            player->spawnWall();
                            break;
                        case OBJECT_TYPE::TURRET:
                            player->spawnTurret();
                            break;
                        case OBJECT_TYPE::MINE:
                            player->spawnMine();
                            break;
                        default:
                            break;
                    }
                    break;
                }

                case MESSAGE::SELL:break;
                case MESSAGE::ERROR:break;
                case MESSAGE::GAMEOVER:break;
                default:break;
            }


            cout << "type: " << type << endl;

            sendMessage(buffer, n, flags, ws);
        } while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
    } catch (WebSocketException& exc) {
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

