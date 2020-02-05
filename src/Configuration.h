#pragma once

#include <Wt/Dbo/SqlConnection.h>

#include <string>

namespace bce {

//! \brief Configuration params for the app
class Configuration {
public:
    //! \brief Creates from file
    //! \exception std::runtime_error if there is a problem
    Configuration(const std::string& file);

    std::unique_ptr<Wt::Dbo::SqlConnection> CreateDatabaseConnection() const;

private:
    std::string DBHost;
    std::string DBPort;
    std::string DBUsername;
    std::string DBPassword;
    std::string DBDatabaseName;
};

} // namespace bce
