#pragma once

#include "Wt/Auth/AuthService.h"
#include "Wt/Auth/OAuthService.h"
#include "Wt/Auth/PasswordService.h"
#include <Wt/WServer.h>

namespace bce {

class Server : public Wt::WServer {
public:
    Server(const char* appname);

    const Wt::Auth::AuthService& Auth()
    {
        return AuthService;
    }

    const Wt::Auth::PasswordService& PasswordAuth()
    {
        return PasswordService;
    }

    const std::vector<const Wt::Auth::OAuthService*>& OAuth()
    {
        return OAuthServicePtrs;
    }


private:
    Wt::Auth::AuthService AuthService;
    Wt::Auth::PasswordService PasswordService;
    std::vector<std::unique_ptr<Wt::Auth::OAuthService>> OAuthServices;
    std::vector<const Wt::Auth::OAuthService*> OAuthServicePtrs;
};

} // namespace bce
