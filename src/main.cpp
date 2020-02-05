#include "Application.h"

#include <Wt/WServer.h>

#include <iostream>
#include <unistd.h>
#include <signal.h>


int main(int argc, char** argv)
{
    try {
        Wt::WServer server(argv[0]);

        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(
            Wt::EntryPointType::Application, [](const Wt::WEnvironment& env) {
                return std::make_unique<bce::Application>(env);
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
