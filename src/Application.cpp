// ------------------------------------ //
#include "Application.h"

#include "Configuration.h"
#include "Server.h"
#include "Task.h"

#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WPushButton.h>
#include <Wt/WServer.h>

using namespace bce;
// ------------------------------------ //
Application::Application(const Wt::WEnvironment& env, Server& server,
    const std::shared_ptr<const Configuration>& config) :
    Wt::WApplication(env),
    _Server(server), Config(config), _Session(*config)
{
    _Session.GetLogin().changed().connect(this, &Application::AuthEvent);

    setTitle("Behaviour Change Environment App");
    useStyleSheet("css/style.css");
    setTheme(std::make_shared<Wt::WBootstrapTheme>());

    root()->addStyleClass("container");

    std::unique_ptr<Wt::Auth::AuthWidget> authWidget = std::make_unique<Wt::Auth::AuthWidget>(
        _Server.Auth(), _Session.GetUsers(), _Session.GetLogin());

    authWidget->model()->addPasswordAuth(&_Server.PasswordAuth());
    authWidget->model()->addOAuth(_Server.OAuth());
    authWidget->setRegistrationEnabled(true);

    authWidget->processEnvironment();

    root()->addWidget(std::move(authWidget));

    root()->addWidget(std::make_unique<Wt::WBreak>());

    root()->addWidget(
        std::make_unique<Wt::WText>("<h1>Environmental Behaviour Change as a web app</h1>"));

    root()->addWidget(std::make_unique<Wt::WBreak>());

    root()->addWidget(
        std::make_unique<Wt::WText>("<p>Description of this web service goes here.</p>"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
}
// ------------------------------------ //
void Application::finalize() {}
// ------------------------------------ //
void Application::AuthEvent()
{
    if(_Session.GetLogin().loggedIn()) {
        const Wt::Auth::User& user = _Session.GetLogin().user();
        log("notice") << "User " << user.id() << " ("
                      << user.identity(Wt::Auth::Identity::LoginName) << ")"
                      << " logged in";
    } else {
        log("notice") << "User logged out";
    }
}
