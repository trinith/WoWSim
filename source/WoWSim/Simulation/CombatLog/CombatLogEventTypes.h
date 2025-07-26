#pragma once

#include <Simulation/DamageType.h>
#include <string>

namespace sim
{

    enum class MissType
    {
        Miss,
        Dodge,
        Parry,
        Resist,
    };

    enum class EventType
    {
        Info,
        Damage,
        Miss,
    };

    struct EventData
    {
        uint32_t eventTime;
    };

    struct InfoEventData : public EventData
    {
        std::string message;
    };

    struct DamageEventData : public EventData
    {
        uint64_t sourceId;
        uint64_t targetId;
        float damageAmount;
        DamageType damageType;
        bool isCritical;
    };

    struct MissEventData : public EventData
    {
        uint64_t targetId;
        uint64_t sourceId;
        MissType missType;
    };

}