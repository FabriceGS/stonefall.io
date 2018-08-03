//
// Created by Fabrice Guyot-Sionnest on 6/23/18.
//

#include "WebSocketRequestHandler.h"
#include "PageRequestHandler.h"
#include "Game/Game.h"
#include "Game/GameState.h"
#include "Game/Player.h"
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
    for (auto session : sessions) {
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
        memset(buffer, 0, sizeof(buffer));
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

            // acquire the game shared_ptr
            if (auto lockedGame = game.lock()) {
                switch (typeEnum) {
                    case MESSAGE::INITIALIZE: {
                        // get name
                        Var nameVar = extractedPayload->get("name");
                        string name = nameVar.convert<string>();

                        // add a new player to the game
                        Player player = lockedGame->addPlayer(name);
                        sessions.insert(make_pair(player.getId(), ws));

                        break;
                    }

                    case MESSAGE::ATTACK: {
                        // get coordinates of objective
                        int x = extractedPayload->get("x").convert<int>();
                        int y = extractedPayload->get("y").convert<int>();
                        // get playerId
                        playerId = extractedPayload->get("id").convert<string>();
                        // get set of attacker ids
                        Var attackerIdsVar = extractedPayload->get("attackers");
                        Array::Ptr attackerIds = attackerIdsVar.extract<Array::Ptr>();
                        unordered_set<string> attackerIdSet;
                        for (int i = 0; i < attackerIds->size(); i++) {
                            string attackerId = attackerIds->getElement<string>(i);
                            attackerIdSet.insert(attackerId);
                        }

                        // send the attacker ids to the game
                        lockedGame->attackCommand(playerId, attackerIdSet);

                        break;
                    }

                    case MESSAGE::SPAWN: {
                        // get coordinates of creation
                        auto x = extractedPayload->get("x").convert<int>();
                        auto y = extractedPayload->get("y").convert<int>();
                        // get creation type enum
                        auto spawnType = extractedPayload->get("objectType").convert<int>();
                        // get id of player
                        playerId = extractedPayload->get("id").convert<string>();

                        if (!lockedGame->validateCreation(x, y, playerId, spawnType)) {
                            // we don't need to send an error message here, just return
                            break;
                        }

                        OBJECT_TYPE spawnTypeEnum = static_cast<OBJECT_TYPE>(spawnType);

                        switch (spawnTypeEnum) {
                            case OBJECT_TYPE::ATTACKER:
                                lockedGame->spawnAttacker(playerId, x, y);
                                break;
                            case OBJECT_TYPE::WALL:
                                lockedGame->spawnWall(playerId, x, y);
                                break;
                            case OBJECT_TYPE::TURRET:
                                lockedGame->spawnTurret(playerId, x, y);
                                break;
                            case OBJECT_TYPE::MINE:
                                lockedGame->spawnMine(playerId, x, y);
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
                        Var toSellIdsVar = extractedPayload->get("toSellIds");
                        Array::Ptr toSellIds = toSellIdsVar.extract<Array::Ptr>();
                        unordered_set<string> toSellIdSet;
                        for (int i = 0; i < toSellIds->size(); i++) {
                            auto toSellId = toSellIds->getElement<string>(i);
                            toSellIdSet.insert(toSellId);
                        }
                        // it might not be necessary to get the type of the object to sell
                        auto toSellType = extractedPayload->get("objectType").convert<int>();
                        OBJECT_TYPE toSellTypeEnum = static_cast<OBJECT_TYPE>(toSellType);

                        // send the ids to sell to the game
                        lockedGame->sellCommand(playerId, toSellIdSet);
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
            } else {
                app.logger().log(Poco::Message("", "The game pointer has expired", Poco::Message::Priority::PRIO_CRITICAL));
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

