// ------------------------------------ //
#include "Application.h"

#include "Configuration.h"
#include "Server.h"
#include "Task.h"

#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WMenu.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WServer.h>
#include <Wt/WStackedWidget.h>

using namespace bce;
// ------------------------------------ //
Application::Application(const Wt::WEnvironment& env, Server& server,
    const std::shared_ptr<const Configuration>& config) :
    Wt::WApplication(env),
    _Server(server), Config(config), _Session(*config)
{
    SetupCallbacks();

    setTitle("Behaviour Change Environment App");

    SetupTheme();
    SetupWidgets();
    TriggerInitialStatus();
}
// ------------------------------------ //
void Application::SetupTheme()
{
    useStyleSheet("css/style.css");
    auto theme = std::make_shared<Wt::WBootstrapTheme>();
    theme->setVersion(Wt::BootstrapVersion::v3);
    theme->setResponsive(true);
    theme->setFormControlStyleEnabled(true);
    setTheme(theme);

    root()->addStyleClass("container");
}

void Application::SetupCallbacks()
{
    _Session.GetLogin().changed().connect(this, &Application::AuthEvent);
    internalPathChanged().connect(this, &Application::HandlePathChanged);
}

void Application::SetupWidgets()
{
    const auto onGithub =
        std::string("This app's code is on <a "
                    "href=\"https://github.com/hhyyrylainen/BCEnvironmentApp\">Github</a>");
    // Navigation bar
    Navigation = root()->addNew<Wt::WNavigationBar>();
    Navigation->setTitle("Environmental BC App", "/");
    Navigation->setResponsive(true);

    // Auth
    auto authWidget = std::make_unique<Wt::Auth::AuthWidget>(
        _Server.Auth(), _Session.GetUsers(), _Session.GetLogin());

    authWidget->model()->addPasswordAuth(&_Server.PasswordAuth());
    authWidget->model()->addOAuth(_Server.OAuth());
    authWidget->setRegistrationEnabled(true);

    authWidget->processEnvironment();

    root()->addWidget(std::move(authWidget));

    root()->addWidget(std::make_unique<Wt::WBreak>());

    // End of auth, begin content

    Wt::WStackedWidget* contentsStack = root()->addNew<Wt::WStackedWidget>();
    contentsStack->addStyleClass("contents");

    // Navigation menu setup
    // Setup a Left-aligned menu.
    auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
    auto leftMenu_ = Navigation->addMenu(std::move(leftMenu));
    leftMenu_->setInternalPathEnabled("/");

    leftMenu_
        ->addItem("Home", Wt::cpp14::make_unique<Wt::WText>(
                              "<p>Description of this web service goes here.</p>"))
        ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));
    leftMenu_
        ->addItem("Leaderboards", Wt::cpp14::make_unique<Wt::WText>("Leaderboards contents"))
        ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/leaderboards"));
    leftMenu_->addItem("Badges", Wt::cpp14::make_unique<Wt::WText>("Badges content"))
        ->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/badges_stuff"));

    // Right side menu
    auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();
    auto rightMenu_ = Navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);

    auto about = rightMenu_->addItem("About");
    about->setSelectable(false);
    about->clicked().connect([=]() {
        auto messageBox = rightMenu_->addChild(Wt::cpp14::make_unique<Wt::WMessageBox>("About",
            Wt::WString(
                "<p>This is a Behaviour Changing Gamified web App made by Henri "
                "Hyyryläinen for the persuasive design course.</p>"
                "<p>This site uses cookies for keeping track of logins. User login and other "
                "data is collected in order to show how many other users there are on the "
                "site and how well they are doing in the leaderboards</p>" +
                onGithub),
            Wt::Icon::Information, Wt::StandardButton::Ok));

        messageBox->buttonClicked().connect([=] { rightMenu_->removeChild(messageBox); });

        messageBox->show();
    });

    // Footer
    root()->addWidget(std::make_unique<Wt::WBreak>());

    root()->addWidget(
        std::make_unique<Wt::WText>("<span>Environment Behaviour Change app made by Henri "
                                    "Hyyryläinen for the PSD course. " +
                                    onGithub + "</span>"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
}

void Application::TriggerInitialStatus()
{
    internalPathChanged().emit(internalPath());
    // HandlePathChanged();
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
// ------------------------------------ //
void Application::HandlePathChanged()
{
    if(internalPath() == "/leaderboard") {

    } else if(internalPath() == "/navigation/eat") {

    } else {
    }
}
