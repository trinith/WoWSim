#pragma once

#include <cstdint>
#include <ostream>

namespace sim
{

    struct Attributes
    {
        int32_t strength = 0;
        int32_t agility = 0;
        int32_t stamina = 0;
        int32_t intellect = 0;
        int32_t spirit = 0;

        friend Attributes operator+(Attributes lhs, const Attributes& rhs)
        {
            lhs += rhs;
            return lhs;
        }

        Attributes& operator+=(const Attributes& other)
        {
            strength += other.strength;
            agility += other.agility;
            stamina += other.stamina;
            intellect += other.intellect;
            spirit += other.spirit;

            return *this;
        }

        static Attributes GetBaseAttributeSet()
        {
            return Attributes{ 20, 20, 20, 20, 20 };
        }

        friend std::ostream& operator<<(std::ostream& os, const Attributes& a)
        {
            os << "{";
            os << "str=" << a.strength << ", ";
            os << "agi=" << a.agility << ", ";
            os << "sta=" << a.stamina << ", ";
            os << "int=" << a.intellect << ", ";
            os << "spr=" << a.spirit;
            os << "}";
            return os;
        }
    };

}