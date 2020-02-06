// ------------------------------------ //
#include "User.h"

#include <Wt/Auth/Dbo/AuthInfo.h>
#include <Wt/Dbo/Impl.h>

#include <ctime>
using namespace bce;
// ------------------------------------ //
DBO_INSTANTIATE_TEMPLATES(bce::User);
// ------------------------------------ //
void User::UpdateLastLoggedIn()
{
    LastLogin = std::time(nullptr);
}
