// ------------------------------------ //
#include "Configuration.h"

#include <Wt/Dbo/backend/Postgres.h>

#include <json/json.h>

#include <fstream>
using namespace bce;
// ------------------------------------ //
Configuration::Configuration(const std::string& file)
{
    std::ifstream reader(file);

    if(!reader.good())
        throw std::runtime_error("cannot read json configuration file");

    Json::Value root;
    reader >> root;

    const auto db = root["database"];

    if(db["type"] != "postgres")
        throw std::runtime_error("only postgres database type is supported");

    DBHost = db["host"].asString();
    DBPort = db["port"].asString();
    DBUsername = db["username"].asString();
    DBPassword = db["password"].asString();
    DBDatabaseName = db["database"].asString();
}
// ------------------------------------ //
std::unique_ptr<Wt::Dbo::SqlConnection> Configuration::CreateDatabaseConnection() const
{
    std::stringstream sstream;
    sstream << "host=" << DBHost << " port=" << DBPort << " dbname=" << DBDatabaseName
            << " user=" << DBUsername << " password=" << DBPassword << " connect_timeout=10"
            << " application_name=bcenvironmentapp";

    return std::make_unique<Wt::Dbo::backend::Postgres>(sstream.str());
}
