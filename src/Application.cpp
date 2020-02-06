// ------------------------------------ //
#include "Application.h"

#include "Configuration.h"
#include "DailyTasks.h"
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

#include <ctime>

using namespace bce;
// ------------------------------------ //
const auto ON_GITHUB =
    std::string("This app's code is on <a "
                "href=\"https://github.com/hhyyrylainen/BCEnvironmentApp\">Github</a>");
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

    ContentLevelStack = root()->addNew<Wt::WStackedWidget>();
    ContentLevelStack->addStyleClass("contents");

    SetupMainContent();

    // Navigation menu setup
    MainNavigationMenu = Navigation->addMenu(std::make_unique<Wt::WMenu>());
    HomeMenuItem = MainNavigationMenu->addItem("Home");
    HomeMenuItem->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));

    LeaderboardsMenuItem = MainNavigationMenu->addItem("Leaderboards");
    LeaderboardsMenuItem->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/leaderboards"));

    BadgesMenuItem = MainNavigationMenu->addItem("Badges");
    BadgesMenuItem->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/badges"));

    // Right side menu
    SideNavigationMenu =
        Navigation->addMenu(std::make_unique<Wt::WMenu>(), Wt::AlignmentFlag::Right);

    AboutMenuItem = SideNavigationMenu->addItem("About");
    AboutMenuItem->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/about"));

    // Footer
    root()->addWidget(std::make_unique<Wt::WBreak>());

    root()->addWidget(
        std::make_unique<Wt::WText>("<span>Environment Behaviour Change app made by Henri "
                                    "Hyyryläinen for the PSD course. " +
                                    ON_GITHUB + "</span>"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
}

void Application::SetupMainContent()
{
    HomeContent = ContentLevelStack->addWidget(std::make_unique<Wt::WContainerWidget>());

    HomeContentLoggedIn = HomeContent->addWidget(std::make_unique<Wt::WContainerWidget>());
    HomeContentLoggedIn->setHidden(true);

    // TODO: refresh this some times
    const auto timeNow = std::time(nullptr);

    const auto oneDayAgo = timeNow - (24 * 60 * 60);

    const auto loggedInCount = _Session.query<int>("SELECT COUNT(*) FROM user")
                                   .where("last_login > ?")
                                   .bind(oneDayAgo);

    HomeContentLoggedIn->addWidget(std::make_unique<Wt::WText>(Wt::WString(
        "<p>Welcome to your home screen. Here you can see your daily tasks and status. There "
        "are currently {1} visitors on this site. {2} users have logged in today.</p>")
                                                                   .arg(_Server.sessions()
                                                                            .size())
                                                                   .arg(loggedInCount)));

    Tasks = HomeContentLoggedIn->addWidget(std::make_unique<DailyTasks>());

    HomeContentAnon = HomeContent->addWidget(std::make_unique<Wt::WContainerWidget>());

    HomeContentAnon->addWidget(
        std::make_unique<Wt::WText>("<p>Description of this web service goes here.</p>"));

    LeaderboardsContent =
        ContentLevelStack->addWidget(std::make_unique<Wt::WContainerWidget>());
    LeaderboardsContent->addWidget(
        std::make_unique<Wt::WText>("<p>Leaderboards content.</p>"));

    BadgesContent = ContentLevelStack->addWidget(std::make_unique<Wt::WContainerWidget>());
    BadgesContent->addWidget(std::make_unique<Wt::WText>("<p>Badges content.</p>"));

    AboutContent = ContentLevelStack->addWidget(std::make_unique<Wt::WContainerWidget>());
    AboutContent->addWidget(std::make_unique<Wt::WText>(Wt::WString(
        "<p>This is a Behaviour Changing Gamified web App made by Henri "
        "Hyyryläinen for the persuasive design course.</p>"
        "<p>This site uses cookies for keeping track of logins. User login and other "
        "data is collected in order to show how many other users there are on the "
        "site and how well they are doing in the leaderboards</p>" +
        ON_GITHUB)));
}

void Application::TriggerInitialStatus()
{
    HandlePathChanged();
    UpdateLoggedInWidgets();
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

        // user.

        _Session.GetUsers().find(user);

        // Wt::Dbo::Transaction transaction{_Session};

        // // TODO: this is a mess
        // LoggedInUser = _Session.find<User>().where("email = ?").bind(user.email());

        // // Create user object if missing
        // if(!LoggedInUser) {
        //     log("notice") << "First time this user has logged in, creating their profile";

        //     std::unique_ptr<User> newUser{new User()};
        //     newUser->Email = user.email();
        //     newUser->UpdateLastLoggedIn();

        //     LoggedInUser = _Session.add(std::move(newUser));
        // } else {

        //     // Trigger last login update
        //     LoggedInUser.modify()->UpdateLastLoggedIn();
        // }
    } else {
        log("notice") << "User logged out";
        LoggedInUser = nullptr;
    }

    UpdateLoggedInWidgets();
}
// ------------------------------------ //
void Application::HandlePathChanged()
{
    if(internalPath() == "/leaderboards") {
        ContentLevelStack->setCurrentWidget(LeaderboardsContent);
        MainNavigationMenu->select(LeaderboardsMenuItem);
        SideNavigationMenu->select(nullptr);
    } else if(internalPath() == "/badges") {
        ContentLevelStack->setCurrentWidget(BadgesContent);
        MainNavigationMenu->select(BadgesMenuItem);
        SideNavigationMenu->select(nullptr);
    } else if(internalPath() == "/about") {
        ContentLevelStack->setCurrentWidget(AboutContent);
        MainNavigationMenu->select(nullptr);
        SideNavigationMenu->select(AboutMenuItem);
    } else {
        ContentLevelStack->setCurrentWidget(HomeContent);
        MainNavigationMenu->select(HomeMenuItem);
        SideNavigationMenu->select(nullptr);
    }
}

void Application::UpdateLoggedInWidgets()
{
    // Cancel if not created yet. This happens if user logs in with cookies
    if(!HomeContentLoggedIn)
        return;

    const auto logged = LoggedInUser.operator bool();

    HomeContentLoggedIn->setHidden(!logged);
    HomeContentAnon->setHidden(logged);
}
