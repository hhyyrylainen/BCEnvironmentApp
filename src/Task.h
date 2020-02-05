#pragma once

#include <Wt/Dbo/Dbo.h>

namespace bce {

//! \brief Represents a task definition existing in the app
class Task {
public:
    template<class Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, Name, "name");
        Wt::Dbo::field(a, Description, "description");
        Wt::Dbo::field(a, Difficulty, "difficulty");
        Wt::Dbo::field(a, RewardPoints, "reward_points");
    }

    std::string Name;
    std::string Description;
    float Difficulty;
    float RewardPoints;

    // TODO: restrictions or other labels for what this task needs
};

} // namespace bce
