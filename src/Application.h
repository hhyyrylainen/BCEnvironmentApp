#pragma once

#include <Wt/WApplication.h>
#include <Wt/WFileUpload.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPanel.h>
#include <Wt/WText.h>

namespace bce {

class StackWalkRunner;
class ResultWidget;

class Application : public Wt::WApplication {
public:
    Application(const Wt::WEnvironment& env);

    void finalize() override;

private:

};

} // namespace sws
