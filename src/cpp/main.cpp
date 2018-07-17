#include "Server/PageRequestHandler.h"
#include "Server/Websockets.h"

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
#include <iostream>
#include "Server/Websockets.h"

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


class WebSocketServer: public Poco::Util::ServerApplication
    /// The main application class.
    ///
    /// This class handles command-line arguments and
    /// configuration files.
    /// Start the WebSocketServer executable with the help
    /// option (/help on Windows, --help on Unix) for
    /// the available command line options.
    ///
    /// To use the sample configuration file (WebSocketServer.properties),
    /// copy the file to the directory where the WebSocketServer executable
    /// resides. If you start the debug version of the WebSocketServer
    /// (WebSocketServerd[.exe]), you must also create a copy of the configuration
    /// file named WebSocketServerd.properties. In the configuration file, you
    /// can specify the port on which the server is listening (default
    /// 9980) and the format of the date/time string sent back to the client.
    ///
    /// To test the WebSocketServer you can use any web browser (http://localhost:9980/).
{
public:
    WebSocketServer(): _helpRequested(false)
    {
        std::cout << "websocket server created" << std::endl;

    }

    ~WebSocketServer()
    {
    }

protected:
    void initialize(Application& self)
    {
        std::cout << "method called: initialize(); of class WebSocketServer" << std::endl;

        loadConfiguration(); // load default configuration files, if present
        ServerApplication::initialize(self);
    }

    void uninitialize()
    {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options)
    {
        std::cout << "method called: defineOptions(); of class WebSocketServer" << std::endl;

        ServerApplication::defineOptions(options);

        options.addOption(
                Option("help", "h", "display help information on command line arguments")
                        .required(false)
                        .repeatable(false));
    }

    void handleOption(const std::string& name, const std::string& value)
    {
        std::cout << "method called: handleOption(); of class WebSocketServer" << std::endl;

        ServerApplication::handleOption(name, value);

        if (name == "help")
            _helpRequested = true;
    }

    void displayHelp()
    {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A sample HTTP server supporting the WebSocket protocol.");
        helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args)
    {
        if (_helpRequested)
        {
            displayHelp();
        }
        else
        {
            // get parameters from configuration file
            unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 4567);

            // set-up a server socket
            ServerSocket svs(port);
            // set-up a HTTPServer instance
            HTTPServer srv(new RequestHandlerFactory, svs, new HTTPServerParams);
            // start the HTTPServer
            srv.start();
            // wait for CTRL-C or kill
            waitForTerminationRequest();
            // Stop the HTTPServer
            srv.stop();
        }
        return Application::EXIT_OK;
    }

private:
    bool _helpRequested;
};


// POCO_SERVER_MAIN(WebSocketServer);