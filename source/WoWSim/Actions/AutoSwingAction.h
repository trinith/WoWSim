#pragma once

#include <Actions/ActionBase.h>
#include <Simulation/Simulation.h>

namespace actions
{

    class AutoSwingAction : public actions::ActionBase
    {
    public:
        AutoSwingAction()
        {
        }

        std::string ToString() const override
        {
            return "{AutoSwingAction}";
        }

    protected:
        void OnExecute(sim::Simulation& simulation) override
        {
            std::cout << "[" << simulation.CurrentTime() << "] Swing!" << std::endl;

            constexpr sim::Simulation::TimeType swingTime = 3800;
            simulation.QueueAction<AutoSwingAction>(swingTime);
        }

    private:
    };

}