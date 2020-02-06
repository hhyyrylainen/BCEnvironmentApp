#pragma once

#include "User.h"

#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Auth/Login.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>

namespace bce {

class Configuration;

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

//! \brief Customized DB session for BCE
class Session : public Wt::Dbo::Session {
public:
    Session(const Configuration& config);

    void PrintSQLForTables();

    UserDatabase& GetUsers()
    {
        return *Users;
    }

    Wt::Auth::Login& GetLogin()
    {
        return Login;
    }

private:
    std::unique_ptr<UserDatabase> Users;
    Wt::Auth::Login Login;
};

} // namespace bce
