#pragma once

#include <Actions/ActionBase.h>

namespace actions
{

    class SimulationEndAction : public actions::ActionBase
    {
    public:
        SimulationEndAction()
        {
        }

        std::string ToString() const override
        {
            return "{SimulationEndAction}";
        }

    protected:
        void OnExecute(sim::Simulation& simulation) override
        {
            std::cout << "[" << simulation.CurrentTime() << "] SIMULATON END" << std::endl;
            simulation.Stop();
        }

    private:
    };

}