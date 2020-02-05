// ------------------------------------ //
#include "Server.h"

#include "Wt/Auth/FacebookService.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"

using namespace bce;
// ------------------------------------ //
Server::Server(const char* appname) :
    Wt::WServer(appname), AuthService(), PasswordService(AuthService)
{
    // Configure authentication
    AuthService.setAuthTokensEnabled(true, "logincookie");
    AuthService.setEmailVerificationEnabled(true);
    AuthService.setEmailVerificationRequired(true);

    std::unique_ptr<Wt::Auth::PasswordVerifier> verifier =
        std::make_unique<Wt::Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(9));
    PasswordService.setVerifier(std::move(verifier));
    PasswordService.setAttemptThrottlingEnabled(true);
    PasswordService.setStrengthValidator(
        std::make_unique<Wt::Auth::PasswordStrengthValidator>());

    // These spam logs and I'm in no hurry to implement these...
    // if(Wt::Auth::GoogleService::configured())
    //     OAuthServices.push_back(std::make_unique<Wt::Auth::GoogleService>(AuthService));

    // if(Wt::Auth::FacebookService::configured())
    //     OAuthServices.push_back(std::make_unique<Wt::Auth::FacebookService>(AuthService));

    for(auto& service : OAuthServices) {
        service->generateRedirectEndpoint();
        OAuthServicePtrs.push_back(service.get());
    }
}
// ------------------------------------ //
