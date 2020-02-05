#pragma once

#include <Wt/Dbo/Session.h>
#include <Wt/WApplication.h>
#include <Wt/WFileUpload.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPanel.h>
#include <Wt/WText.h>

namespace bce {

class Configuration;

class Application : public Wt::WApplication {
public:
    Application(
        const Wt::WEnvironment& env, const std::shared_ptr<const Configuration>& config);

    void finalize() override;

private:
    std::shared_ptr<const Configuration> Config;

    Wt::Dbo::Session session;
};

} // namespace bce
