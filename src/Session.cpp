// ------------------------------------ //
#include "Session.h"

#include "Configuration.h"
#include "Task.h"

#include <iostream>
using namespace bce;
// ------------------------------------ //
Session::Session(const Configuration& config)
{
    // TODO: proper use here would use a connection pool
    setConnection(std::move(config.CreateDatabaseConnection()));

    // Auth stuff
    mapClass<User>("user");
    mapClass<AuthInfo>("auth_info");
    mapClass<AuthInfo::AuthIdentityType>("auth_identity");
    mapClass<AuthInfo::AuthTokenType>("auth_token");

    // Other stuff
    mapClass<Task>("task");

    Users = std::make_unique<UserDatabase>(*this);
}

// ------------------------------------ //
void Session::PrintSQLForTables()
{
    std::cout << "Full table SQL: \n";
    std::cout << tableCreationSql() << "\nEnd of table SQL\n";
}
