// ------------------------------------ //
#include "Application.h"

#include "Configuration.h"

#include <Wt/WBootstrapTheme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WPushButton.h>

using namespace bce;
// ------------------------------------ //
Application::Application(
    const Wt::WEnvironment& env, const std::shared_ptr<const Configuration>& config) :
    Wt::WApplication(env),
    Config(config)
{
    session.setConnection(std::move(Config->CreateDatabaseConnection()));
    // session.

    setTitle("Behaviour Change Environment App");
    setTheme(std::make_shared<Wt::WBootstrapTheme>());
    // useStyleSheet(const WLink &link)

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
