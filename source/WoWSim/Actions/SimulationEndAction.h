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
            const sim::SimulationConsoleLog& log = simulation.GetConsoleLog();
            log.WriteLine("SIMULATION END");
            simulation.Stop();
        }

    private:
    };

}