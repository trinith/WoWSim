#pragma once

#include <iostream>

namespace sim
{
    class Simulation;

    struct IAction
    {
        virtual void Execute(Simulation& simulation) = 0;
        virtual std::string ToString() const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IAction& obj)
        {
            os << obj.ToString();
            return os;
        }
    };

}