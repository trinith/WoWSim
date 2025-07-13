#include "Attributes.h"

namespace sim
{

    std::ostream& operator<<(std::ostream& os, const PrimaryAttributes& a)
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

    PrimaryAttributes operator+(PrimaryAttributes lhs, const PrimaryAttributes& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    PrimaryAttributes& operator+=(PrimaryAttributes& lhs, const PrimaryAttributes& other)
    {
        lhs.strength += other.strength;
        lhs.agility += other.agility;
        lhs.stamina += other.stamina;
        lhs.intellect += other.intellect;
        lhs.spirit += other.spirit;

        return lhs;
    }

}