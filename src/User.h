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
    }


    bool Admin;
};
} // namespace bce

DBO_EXTERN_TEMPLATES(bce::User);
