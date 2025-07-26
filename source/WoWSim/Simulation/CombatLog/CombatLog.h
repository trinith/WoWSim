#pragma once

#include <Simulation/CombatLog/CombatLogEventTypes.h>
#include <Util/EventHandler.h>

namespace sim
{
	
    class CombatLog
    {
    public:
        struct EventInfo
        {
            const EventType& eventType;
            const EventData& eventData;
        };

        using CombatLogEventHandler = util::EventHandler<const CombatLog, const EventInfo>;

        CombatLogEventHandler CombatEventLogged{};

        void LogEvent(EventType eventType, const EventData& eventData) const
        {
            if (CombatEventLogged)
                CombatEventLogged(*this, EventInfo{ eventType, eventData });
        }

    private:

    };

}