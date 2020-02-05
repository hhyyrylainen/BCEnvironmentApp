#include "Application.h"

#include "Configuration.h"

#include <Wt/WServer.h>



#include <iostream>
#include <signal.h>
#include <unistd.h>


void PrintUsage(char** argv)
{
    std::cout << "Usage: " << argv[0]
              << " PATH_TO_BCEnvironmentApp_CONFIG_FILE [Wt options]\n";
}

int main(int argc, char** argv)
{
    if(argc < 1)
        return 2;

    if(argc < 2) {
        PrintUsage(argv);
        return 2;
    }

    std::shared_ptr<bce::Configuration> config;

    try {
        config = std::make_shared<bce::Configuration>(argv[1]);
    } catch(const std::exception& e) {

        std::cout << "exception: " << e.what() << "\n";
        PrintUsage(argv);
        return 2;
    }

    try {
        Wt::WServer server(argv[0]);

        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(
            Wt::EntryPointType::Application, [config](const Wt::WEnvironment& env) {
                return std::make_unique<bce::Application>(env, config);
            });

        if(server.start()) {
            int signal = Wt::WServer::waitForShutdown();

            std::cerr << "Shutdown (signal = " << signal << ")" << std::endl;

            server.stop();

            if(signal == SIGHUP)
                Wt::WServer::restart(argc, argv, environ);
        }
    } catch(const std::exception& e) {
        std::cout << "Fatal application error: " << e.what() << "\n";
        return 1;
    }
}
