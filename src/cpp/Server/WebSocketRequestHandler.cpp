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
#include "Poco/Message.h"
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

void WebSocketRequestHandler::sendMessage(char const *msg, int n, int flags, WebSocket ws)
{
    // send the JSON object
    ws.sendFrame(msg, n, flags);
}

// a method to be called by the game, once the user command queue for a given tick
// has been emptied (i.e. each task has been completed). Thus, a complete gameState
// is ready to be passed to the players and displayed for each user.
// gameState is a gamestate for which one command queue has been completed.
void WebSocketRequestHandler::sendUpdates(const GameState& gameState)
{
    // TODO: process the entire gamestate into a JSON object here
    const char *jsonState = "you've been updated by a smooth criminal";

    // then interpret the game state for each player and update 'em
    for (auto& session: sessions) {
        updateSession(session.first, jsonState);
    }
}

// a method to update a given player's session, given a gameState (represented by a JSON obj) and player id
void WebSocketRequestHandler::updateSession(string playerId, const char *jsonState)
{
    // get session
    shared_ptr<WebSocket> session = sessions.at(playerId);
    int flags;
    int n;

    // send the buffer
    sendMessage(jsonState, n, flags, *session);
}

void WebSocketRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    try {
        shared_ptr<WebSocket> ws = make_shared<WebSocket>(request, response);
        // this is a hack: https://stackoverflow.com/questions/16182814/how-to-keep-websocket-connect-until-either-side-close
        ws->setReceiveTimeout(Poco::Timespan(10, 0, 0, 0, 0));

        char buffer[1024];
        int flags;
        int n;

        do {
            // receive the buffer object
            n = ws->receiveFrame(buffer, sizeof(buffer), flags);

            // convert char array buffer into string
            string JSON(buffer);

            // parse the received JSON object
            Parser parser;
            Var result = parser.parse(JSON);
            Object::Ptr received = result.extract<Object::Ptr>();

            // get type
            Var typeVar = received->get("type");;
            auto type = typeVar.convert<int>();
            auto typeEnum = static_cast<MESSAGE>(type);

            // break out if message type is negative
            if (type < 0) {
                break;
            }

            // get the payload
            Var payload = received->get("payload");
            Object::Ptr extractedPayload = payload.extract<Object::Ptr>();

            // the current player, either to be added or found from the id
            string playerId;

            switch (typeEnum) {

                case MESSAGE::INITIALIZE: {
                    // get name
                    Var nameVar = extractedPayload->get("name");
                    string name = nameVar.convert<string>();

                    // add a new player to the game
                    Player player = game->addPlayer(name);
                    sessions.insert(make_pair(player.getId(), ws));

                    break;
                }

                case MESSAGE::ATTACK: {
                    // get coordinates of objective
                    int x = extractedPayload->get("x").convert<int>();
                    int y = extractedPayload->get("y").convert<int>();
                    // get playerId
                    playerId = extractedPayload->get("id").convert<string>();
                    // set of attacker ids
                    Array::Ptr attackerIds;
                    extractedPayload->get("attackers").convert<Array::Ptr>(attackerIds);
                    

                    // iterate over and add to hashset
                    unordered_set<string> attackerIdSet;
                    for(auto iter = attackerIds->begin(); iter != attackerIds->end(); iter++) {
                        attackerIdSet.insert(iter->first);
                    }

                    // send the attacker ids to the game
                    game->attackCommand(playerId, attackerIdSet);

                    break;
                }

                case MESSAGE::CREATE: {
                    // get x and y coords of creation
                    auto x = extractedPayload->get("x").convert<int>();
                    auto y = extractedPayload->get("y").convert<int>();
                    // get creation type enum
                    auto creationType = extractedPayload->get("objectType").convert<int>();
                    // get id of player
                    playerId = extractedPayload->get("id").convert<string>();

                    if (!game->validateCreation(x, y, playerId, creationType)) {
                        // we don't need to send an error message here, just return
                        break;
                    }

                    OBJECT_TYPE creationTypeEnum = static_cast<OBJECT_TYPE>(creationType);

                    switch(creationTypeEnum){
                        case OBJECT_TYPE::ATTACKER:
                            game->spawnAttacker(playerId, x, y);
                            break;
                        case OBJECT_TYPE::WALL:
                            game->spawnWall(playerId, x, y);
                            break;
                        case OBJECT_TYPE::TURRET:
                            game->spawnTurret(playerId, x, y);
                            break;
                        case OBJECT_TYPE::MINE:
                            game->spawnMine(playerId, x, y);
                            break;
                        default:
                            break;
                    }
                    break;
                }

                case MESSAGE::SELL: {
                    // get id of player
                    auto id = extractedPayload->get("id").convert<string>();
                    // get set of ids to sell
                    Object::Ptr toSellIds = extractedPayload->getObject("toSellIds");

                    // iterate over ids to sell and add to hashset
                    unordered_set<string> toSellIdSet;
                    for(auto iter = toSellIds->begin(); iter != toSellIds->end(); iter++) {
                        toSellIdSet.insert(iter->first);
                    }

                    // send the ids to sell to the game
                    game->sellCommand(playerId, toSellIdSet);
                    break;
                };

                case MESSAGE::ERROR: {
                    auto message = extractedPayload->get("message").convert<string>();
                    app.logger().log(Poco::Message("", message, Poco::Message::Priority::PRIO_ERROR));
                    break;
                };

                case MESSAGE::GAMEOVER: {
                    app.logger().log(Poco::Message("", "A client sent a GAMEOVER message to us", Poco::Message::Priority::PRIO_WARNING));
                    break;
                };

                case MESSAGE::TEST: {
                    auto message = extractedPayload->get("message").convert<string>();
                    app.logger().log(Poco::Message("", message, Poco::Message::Priority::PRIO_DEBUG));
                }

                default: {
                    app.logger().log(Poco::Message("", "An unrecognized message type was sent", Poco::Message::Priority::PRIO_WARNING));
                };
            }
        } while (n > 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);
    }
    catch (WebSocketException& exc) {
        cout << "exception" << endl;
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

