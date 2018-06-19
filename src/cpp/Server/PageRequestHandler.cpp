//
// Created by Mac McCann on 6/18/18.
//

#include "PageRequestHandler.h"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;

void PageRequestHandler::handleRequest(HTTPServerRequest &request, HTTPServerResponse &response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    std::ostream& ostr = response.send();
    ostr << "<html>";
    ostr << "<head>";
    ostr << "<title>WebSocketServer</title>";
    ostr << "<script type=\"text/javascript\">";
    ostr << "function WebSocketTest()";
    ostr << "{";
    ostr << "  if (\"WebSocket\" in window)";
    ostr << "  {";
    ostr << "    var ws = new WebSocket(\"ws://" << request.serverAddress().toString() << "/ws\");";
    ostr << "    ws.onopen = function()";
    ostr << "      {";
    ostr << "        ws.send(\"Hello, world!\");";
    ostr << "      };";
    ostr << "    ws.onmessage = function(evt)";
    ostr << "      { ";
    ostr << "        var msg = evt.data;";
    ostr << "        alert(\"Message received: \" + msg);";
    ostr << "        ws.close();";
    ostr << "      };";
    ostr << "    ws.onclose = function()";
    ostr << "      { ";
    ostr << "        alert(\"WebSocket closed.\");";
    ostr << "      };";
    ostr << "  }";
    ostr << "  else";
    ostr << "  {";
    ostr << "     alert(\"This browser does not support WebSockets.\");";
    ostr << "  }";
    ostr << "}";
    ostr << "</script>";
    ostr << "</head>";
    ostr << "<body>";
    ostr << "  <h1>WebSocket Server</h1>";
    ostr << "  <p><a href=\"javascript:WebSocketTest()\">Run WebSocket Script</a></p>";
    ostr << "</body>";
    ostr << "</html>";
}
