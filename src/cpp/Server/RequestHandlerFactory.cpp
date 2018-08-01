//
// Created by Mac McCann on 7/5/18.
//

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "RequestHandlerFactory.h"
#include "Game.h"
#include "Player.h"
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
        return new WebSocketRequestHandler(std::make_shared<Game>());
    } else {
        return new PageRequestHandler;
    }
};
