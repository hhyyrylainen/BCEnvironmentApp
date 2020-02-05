#include "Configuration.h"
#include "Session.h"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    std::string action;
    std::string configPath;

    po::options_description desc("Options");

    // clang-format off
    desc.add_options()
        ("help,h", "Print this help message") 
        ("action,a", po::value<std::string>(&action)->required(), "Action to perform") 
        ("config,c", po::value<std::string>(&configPath), 
            "Path to the BCEnvironmentApp json config file");
    // clang-format on

    po::positional_options_description positionalOptions;
    positionalOptions.add("config", 1);
    positionalOptions.add("action", 1);

    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv)
                      .options(desc)
                      .positional(positionalOptions)
                      .run(),
            vm);

        if(vm.count("help")) {
            std::cout << "Usage: " << desc << "\n";
            return 0;
        }

        po::notify(vm);
    } catch(boost::program_options::error& e) {
        std::cout << "ERROR: " << e.what() << "\n";
        return 1;
    }

    // Load configuration
    std::shared_ptr<bce::Configuration> config;

    try {
        config = std::make_shared<bce::Configuration>(configPath);
    } catch(const std::exception& e) {
        std::cout << "Error loading config file(" << configPath << "): " << e.what() << "\n";
        return 2;
    }

    std::unique_ptr<bce::Session> session;

    try {
        session = std::make_unique<bce::Session>(*config);
    } catch(const std::exception& e) {
        std::cout << "Error connecting to database: " << e.what() << "\n";
        return 2;
    }

    if(action == "tables") {

        session->PrintSQLForTables();

    } else if(action == "create-tables") {

        std::cout << "Attempting to create all needed tables:\n";

        try {
            session->createTables();
        } catch(const std::exception& e) {
            std::cout << "ERROR: " << e.what() << "\n";
            return 2;
        }

        std::cout << "Done.\n";

    } else {
        std::cout << "ERROR: unknown action: " << action << "\n";
        return 1;
    }

    return 0;
}
