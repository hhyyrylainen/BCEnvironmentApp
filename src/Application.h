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

private:
    // Configuration and other resources
    Server& _Server;
    std::shared_ptr<const Configuration> Config;
    Session _Session;

    // Widgets
    Wt::WStackedWidget* ContentLevelStack;
    Wt::WMenu* MainNavigationMenu;
    Wt::WMenu* SideNavigationMenu;
    Wt::WNavigationBar* Navigation;

    Wt::WMenuItem* HomeMenuItem;
    Wt::WContainerWidget* HomeContent;

    Wt::WMenuItem* LeaderboardsMenuItem;
    Wt::WContainerWidget* LeaderboardsContent;

    Wt::WMenuItem* BadgesMenuItem;
    Wt::WContainerWidget* BadgesContent;

    Wt::WMenuItem* AboutMenuItem;
    Wt::WContainerWidget* AboutContent;
};

} // namespace bce
