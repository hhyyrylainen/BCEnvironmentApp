#pragma once

#include "Session.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Dbo/Session.h>
#include <Wt/WApplication.h>
#include <Wt/WFileUpload.h>
#include <Wt/WLineEdit.h>
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

private:
    Server& _Server;
    std::shared_ptr<const Configuration> Config;
    Session _Session;
};

} // namespace bce
