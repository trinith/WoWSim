#pragma once

#include <Simulation/IAction.h>
#include <Simulation/Simulation.h>

namespace actions
{

    class ActionBase : public sim::IAction
    {
    public:
        void Execute(sim::Simulation& simulation) override
        {
            OnExecute(simulation);
        }

        virtual std::string ToString() const
        {
            return "{...}";
        }

    protected:
        virtual void OnExecute(sim::Simulation& sim) {}
    };

}