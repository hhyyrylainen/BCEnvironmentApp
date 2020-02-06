#pragma once

#include "Session.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Dbo/Session.h>
#include <Wt/WApplication.h>
#include <Wt/WFileUpload.h>
#include <Wt/WLineEdit.h>
#include <Wt/WMenuItem.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WPanel.h>
#include <Wt/WText.h>

namespace bce {

class Configuration;
class Server;
class DailyTasks;

//! \brief Main class for a single client connected session
class Application : public Wt::WApplication {
public:
    Application(const Wt::WEnvironment& env, Server& server,
        const std::shared_ptr<const Configuration>& config);

    void finalize() override;

    void AuthEvent();
    void HandlePathChanged();

private:
    void SetupTheme();
    void SetupCallbacks();
    void SetupWidgets();
    void SetupMainContent();
    void TriggerInitialStatus();

    void UpdateLoggedInWidgets();

private:
    // Configuration and other resources
    Server& _Server;
    std::shared_ptr<const Configuration> Config;
    Session _Session;
    Wt::Dbo::ptr<User> LoggedInUser;

    // Widgets
    Wt::WStackedWidget* ContentLevelStack;
    Wt::WMenu* MainNavigationMenu;
    Wt::WMenu* SideNavigationMenu;
    Wt::WNavigationBar* Navigation;

    Wt::WMenuItem* HomeMenuItem;
    Wt::WContainerWidget* HomeContent;
    //! This is used to check if all widgets have been created yet
    Wt::WContainerWidget* HomeContentLoggedIn = nullptr;
    Wt::WContainerWidget* HomeContentAnon;
    DailyTasks* Tasks;

    Wt::WMenuItem* LeaderboardsMenuItem;
    Wt::WContainerWidget* LeaderboardsContent;

    Wt::WMenuItem* BadgesMenuItem;
    Wt::WContainerWidget* BadgesContent;

    Wt::WMenuItem* AboutMenuItem;
    Wt::WContainerWidget* AboutContent;
};

} // namespace bce
