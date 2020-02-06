#pragma once

#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

namespace bce {
class User;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;

class User {
public:
    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, Admin, "is_admin");
        Wt::Dbo::field(a, DisplayName, "display_name");
        Wt::Dbo::field(a, TotalPoints, "total_points");
        Wt::Dbo::field(a, LastLogin, "last_login");
    }

    void UpdateLastLoggedIn();

    bool Admin = false;
    std::string DisplayName;
    float TotalPoints = 0.f;

    //! Unix timestamp of last login or -1 if never logged in
    int64_t LastLogin = -1;
};
} // namespace bce

DBO_EXTERN_TEMPLATES(bce::User);
