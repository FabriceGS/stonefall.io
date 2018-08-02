//
// Created by Mac McCann on 7/5/18.
//

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "RequestHandlerFactory.h"
#include "Game/Game.h"
#include "Game/Player.h"
#include "Server/WebSocketRequestHandler.h"
#include "Server/PageRequestHandler.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Net::HTTPServerRequest;

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    Application& app = Application::instance();
    for (HTTPServerRequest::ConstIterator it = request.begin(); it != request.end(); ++it)
    {
    }

    if (request.find("Upgrade") != request.end() && Poco::icompare(request["Upgrade"], "websocket") == 0) {
        shared_ptr<Game> newGame = make_shared<Game>();
        return new WebSocketRequestHandler(newGame);
    } else {
        return new PageRequestHandler;
    }
};
