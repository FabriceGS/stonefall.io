#include "Server/PageRequestHandler.h"
#include "Server/WebSocketRequestHandler.h"
#include "Server/WebSocketRequestHandler.h"
#include "Server/RequestHandlerFactory.h"

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
#include "Poco/Thread.h"
#include "Poco/ThreadPool.h"
#include "Poco/Timer.h"

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
    WebSocketServer(): _helpRequested(false) {}

    ~WebSocketServer() {}

protected:
    void initialize(Application& self) override {
        loadConfiguration(); // load default configuration files, if present
        ServerApplication::initialize(self);
    }

    void uninitialize() override {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options) override {

        ServerApplication::defineOptions(options);

        options.addOption(
                Option("help", "h", "display help information on command line arguments")
                        .required(false)
                        .repeatable(false));
    }

    void handleOption(const std::string& name, const std::string& value) override {
        std::cout << "method called: handleOption(); of class WebSocketServer" << std::endl;

        ServerApplication::handleOption(name, value);

        if (name == "help")
            _helpRequested = true;
    }

    void displayHelp() {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A sample HTTP server supporting the WebSocket protocol.");
        helpFormatter.format(std::cout);
    }

    int main(const std::vector<std::string>& args) override {
        if (_helpRequested) {
            displayHelp();
        } else {
            if (sodium_init() == 1) {
                return 1;
            }
            shared_ptr<GameManager> gameManager = make_shared<GameManager>();
            // get parameters from configuration file
            unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 4567);
            // set-up a server socket
            ServerSocket svs(port);
            // set-up a HTTPServer instance
            HTTPServer srv(new RequestHandlerFactory(gameManager), svs, new HTTPServerParams);
            // start the HTTPServer
            srv.start();
            cout << "----------------------------------------------" << endl;
            cout << "         __                   ____      ____" << endl;
            cout << "   _____/ /_____  ____  ___  / __/___ _/ / /" << endl;
            cout << "  / ___/ __/ __ \\/ __ \\/ _ \\/ /_/ __ `/ / /" << endl;
            cout << " (__  ) /_/ /_/ / / / /  __/ __/ /_/ / / /" << endl;
            cout << "/____/\\__/\\____/_/ /_/\\___/_/  \\__,_/_/_/" << endl;
            cout << "______________________________________________" << endl;
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

POCO_SERVER_MAIN(WebSocketServer);
