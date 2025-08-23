#pragma once

#include <Data/WeaponTypes.h>

#include <cstdint>
#include <ostream>
#include <unordered_map>

namespace sim
{

    struct PrimaryAttributes
    {
        int32_t strength = 0;
        int32_t agility = 0;
        int32_t stamina = 0;
        int32_t intellect = 0;
        int32_t spirit = 0;
    };

    struct CombatAttributes
    {
        float hit = 0.f;
        float crit = 0.f;
        float attackSpeed = 0.f;
        float attackPower = 0.f;
    };

    struct DefenseAttributes
    {
        uint32_t armor = 0;
        uint32_t defense = 0;
        float dodge = 0.05f;
        float parry = 0.05f;
        float block = 0.f;
    };

    struct Attributes
    {
        PrimaryAttributes primaryAttributes{};
        CombatAttributes combatAttributes{};
        DefenseAttributes defenseAttributes{};

        Attributes() {}

        Attributes(PrimaryAttributes attributesIn)
            : primaryAttributes{ attributesIn }
        {
        }
    };

    std::ostream& operator<<(std::ostream& os, const PrimaryAttributes& a);
    PrimaryAttributes operator+(PrimaryAttributes lhs, const PrimaryAttributes& rhs);
    PrimaryAttributes& operator+=(PrimaryAttributes& lhs, const PrimaryAttributes& other);

}